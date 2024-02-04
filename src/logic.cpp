#include "logic.h"


Logic::Logic() :
    m_buttonTimer(0), 
    m_buttonSwitch(0), 
    m_buttonState(0), 
    m_currentControlState(ControlStates::AUTO), 
    m_lightValue(0), 
    m_prevLightManualState(LightStates::OFF),
    m_currentLightState(LightStates::OFF)
{
}


void Logic::loadModules(Modules* modules)
{
    m_modules = modules;
}


void Logic::implementation(uint64_t time)
{
    m_modules->read(ModuleID::CLOCK, m_time);

    if (m_currentControlState == ControlStates::AUTO)
        this->autoControl();

    m_modules->read(ModuleID::BUTTON, &m_buttonState);

    if (m_buttonState == 0 && m_buttonSwitch == false)
    {
        m_buttonTimer = time;
        m_buttonSwitch = true;
    }
    else if (m_buttonState == 1 && m_buttonSwitch == true)
    {
        uint64_t period = time - m_buttonTimer;
        this->buttonPress(period);
        m_buttonSwitch = false;
    }

    m_modules->write(ModuleID::LIGHT, (uint16_t)m_lightValue);
}


void Logic::autoControl()
{
    m_currentLightState = getLightState();

    switch(m_currentLightState)
    {
        case LightStates::OFF:
            m_lightValue = LIGHT_OFF;
            break;
        case LightStates::ON:
            m_lightValue = LIGHT_ON;
            break;
        case LightStates::FADE_UP:
            m_lightValue = this->fadeUp();
            break;
        case LightStates::FADE_DOWN:
            m_lightValue = this->fadeDown();
            break;
    }
}


uint32_t Logic::getTimeAsSec(const uint16_t& hours, const uint16_t& minutes, const uint16_t& seconds) const
{
    return (uint32_t)hours * 3600 + (uint32_t)minutes * 60 + (uint32_t)seconds;
}


LightStates Logic::getLightState() const
{
    uint32_t timeNow = this->getTimeAsSec(m_time[0], m_time[1], m_time[2]);
    if (timeNow >= this->getTimeAsSec(SUNRISE_TIME_HH, 0, 0) and timeNow < this->getTimeAsSec(SUNRISE_TIME_HH, FADE_TIME_MM, 0))
        return LightStates::FADE_UP;
    else if (timeNow >= this->getTimeAsSec(SUNRISE_TIME_HH, FADE_TIME_MM, 0) and timeNow < this->getTimeAsSec(SUNSET_TIME_HH, 0, 0))
        return LightStates::ON;
    else if (timeNow >= this->getTimeAsSec(SUNSET_TIME_HH, 0, 0) and timeNow < this->getTimeAsSec(SUNSET_TIME_HH, FADE_TIME_MM, 0))
        return LightStates::FADE_DOWN;
    else
        return LightStates::OFF;
}


uint8_t Logic::fadeUp()
{
    uint32_t timeNow = this->getTimeAsSec(m_time[0], m_time[1], m_time[2]);
    return (uint8_t)(LIGHT_ON * (timeNow - this->getTimeAsSec(SUNRISE_TIME_HH, 0, 0)) / (this->getTimeAsSec(0, FADE_TIME_MM, 0)));
}


uint8_t Logic::fadeDown()
{
    uint32_t timeNow = this->getTimeAsSec(m_time[0], m_time[1], m_time[2]);
    return (uint8_t)(LIGHT_ON - LIGHT_ON * (timeNow - this->getTimeAsSec(SUNSET_TIME_HH, 0, 0)) / (this->getTimeAsSec(0, FADE_TIME_MM, 0)));
}


void Logic::buttonPress(const uint64_t& period)
{
    switch (m_currentControlState)
    {
        case ControlStates::AUTO:
            if ((uint16_t)period > TRANSITION_TIME)
            {
                m_currentControlState = ControlStates::MANUAL;
                m_lightValue = (m_prevLightManualState == LightStates::ON) ? LIGHT_ON : LIGHT_OFF;
            }
            break;
        case ControlStates::MANUAL:
            if ((uint16_t)period > TRANSITION_TIME)
            {
                m_currentControlState = ControlStates::AUTO;
            }
            else
            {
                m_prevLightManualState = (m_prevLightManualState == LightStates::OFF) ? LightStates::ON : LightStates::OFF;
                m_lightValue = (m_prevLightManualState == LightStates::ON) ? LIGHT_ON : LIGHT_OFF;
            }
            break;
    }
}
