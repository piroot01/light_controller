#ifndef LOGIC_INCLUDED
#define LOGIC_INCLUDED


#include <Arduino.h>
#include "modules/packet.h"
#include "modules/modules.h"
#include "module_id.h"


#define TRANSITION_TIME 1000


#define SUNRISE_TIME_HH 13
#define SUNSET_TIME_HH 20
#define FADE_TIME_MM 45


#define LIGHT_ON 255
#define LIGHT_OFF 0


enum ControlStates
{
    AUTO = 0,
    MANUAL = 1

};


enum LightStates
{
    OFF = 0,
    ON = 1,
    FADE_UP = 2,
    FADE_DOWN = 3

};


class Logic
{
public:
    Logic();
    void loadModules(Modules* modules);
    void implementation(uint64_t time);

private:
    void buttonPress(const uint64_t& period);
    void autoControl();
    uint8_t fadeUp();
    uint8_t fadeDown();
    bool isDay() const;
    uint32_t getTimeAsSec(const uint16_t& hours, const uint16_t& minutes, const uint16_t& seconds) const;
    LightStates getLightState() const;

private:
    Modules* m_modules;

    uint64_t m_buttonTimer;
    bool m_buttonSwitch;
    uint16_t m_buttonState;

    ControlStates m_currentControlState;

    uint8_t m_lightValue;

    LightStates m_prevLightManualState;
    LightStates m_currentLightState;
    uint16_t m_time[3];

};


#endif
