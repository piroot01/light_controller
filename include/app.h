#ifndef APP_INCLUDED
#define APP_INCLUDED


#include <Arduino.h>
#include "modules/clock.h"
#include "modules/modules.h"
#include "logic.h"
#include "module_id.h"


#define BUTTON_PIN 5
#define LIGHT_PIN 3

class App
{
public:
    App();
    void setup();
    void run();


private:
    Modules m_modules;
    Logic m_logic;
    uint64_t time;
    uint16_t dummy;

};


#endif
