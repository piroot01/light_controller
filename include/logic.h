#ifndef LOGIC_INCLUDED
#define LOGIC_INCLUDED


#include <Arduino.h>
#include "modules/packet.h"
#include "modules/modules.h"
#include "module_id.h"


#define TRANSITION_TIME 1000
#define SUNRISE_TIME_HH 8
#define SUNSET_TIME_HH 20
#define FADE_TIME_MM 30
#define LIGHT_ON 255
#define LIGHT_OFF 0


enum States
{
    AUTO = 0,
    MANUAL = 1
};


class Logic
{
public:
    Logic();
    void loadModules(Modules* modules);
    void implementation(uint64_t time);

private:
    void buttonPress(const uint64_t& period);
    void timeControl(const uint64_t& time);
    uint8_t fadeUp(const uint64_t& time);
    uint8_t fadeDown(const uint64_t& time);
    bool isDay() const;

private:
    Modules* m_modules;

    uint64_t m_buttonTimer;
    bool m_buttonSwitch;
    uint16_t m_buttonState;

    States m_currentState;

    uint8_t m_lightState;
    bool m_prevLightManualState;

    uint16_t m_time[3];
    bool m_fadeFlag;
    bool m_dayFlag;
    uint64_t m_fadeStartTime;
};


#endif
