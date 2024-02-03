#include "logic.h"


Logic::Logic() :
    m_buttonTimer(0), 
    m_buttonSwitch(0), 
    m_buttonState(0), 
    m_currentState(States::AUTO), 
    m_lightState(0), 
    m_prevLightManualState(0),
    m_fadeFlag(0),
    m_dayFlag(0),
    m_fadeStartTime(0)
{
}


void Logic::loadModules(Modules* modules)
{
    m_modules = modules;
}


void Logic::implementation(uint64_t time)
{
    m_modules->read(ModuleID::CLOCK, m_time);

    if (m_currentState == States::AUTO)
        this->timeControl(time);

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
}


void Logic::timeControl(const uint64_t& time)
{
    m_dayFlag = this->isDay(); 

    if (m_time[0] == SUNSET_TIME_HH and m_dayFlag == false)
    {
        m_fadeFlag = true;
        m_fadeStartTime = time;
    }
    else if (m_time[0] == SUNSET_TIME_HH and m_dayFlag == true)
    {
        m_fadeFlag = true;
        m_fadeStartTime = time;
    }

    if (m_fadeFlag == true and m_dayFlag == true)
        m_lightState = this->fadeUp(time);
    else if (m_fadeFlag == true and m_dayFlag == false)
        m_lightState = this->fadeDown(time);
    else if (m_fadeFlag == false and m_dayFlag == true)
        m_lightState = LIGHT_ON;
    else if (m_fadeFlag == false and m_dayFlag == false)
        m_lightState = LIGHT_OFF;

    m_modules->write(ModuleID::LIGHT, m_lightState);
}


bool Logic::isDay() const
{
    uint32_t timeNow = m_time[0] * 3600 + m_time[1] * 60 + m_time[0];
    if (timeNow >= (uint32_t)SUNRISE_TIME_HH * 3600 and timeNow <= (uint32_t)SUNSET_TIME_HH * 3600)
        return true;
    return false;
}


uint8_t Logic::fadeUp(const uint64_t& time)
{
    if (time - m_fadeStartTime > (uint64_t)FADE_TIME_MM * 60 * 1000)
    {
        m_fadeFlag = false;
        return LIGHT_ON;
    }
    return (uint8_t)((time - m_fadeStartTime) / ((uint64_t)FADE_TIME_MM * 60 * 1000) * LIGHT_ON);
}


uint8_t Logic::fadeDown(const uint64_t& time)
{
    if (time - m_fadeStartTime > (uint64_t)FADE_TIME_MM * 60 * 1000)
    {
        m_fadeFlag = false;
        return LIGHT_OFF;
    }
    return LIGHT_ON - (uint8_t)((time - m_fadeStartTime) / ((uint64_t)FADE_TIME_MM * 60 * 1000) * LIGHT_ON);
}


void Logic::buttonPress(const uint64_t& period)
{
    switch (m_currentState)
    {
        case States::AUTO:
            if ((uint16_t)period > TRANSITION_TIME)
            {
                m_currentState = States::MANUAL;
                m_lightState = (m_prevLightManualState == true) ? LIGHT_ON : LIGHT_OFF;
            }
            break;
        case States::MANUAL:
            if ((uint16_t)period > TRANSITION_TIME)
            {
                m_currentState = States::AUTO;
            }
            else
            {
                m_prevLightManualState = !m_prevLightManualState;
                m_lightState = (m_prevLightManualState == true) ? LIGHT_ON : LIGHT_OFF;
            }
            break;
    }
    m_modules->write(ModuleID::LIGHT, m_lightState);
}
