#include <Arduino.h>
#include "modules/clock.h"
#include "modules/modules.h"


#define BUTTON_PIN 5
#define LIGHT_PIN 3


class App
{
public:
    App();
    void setup();
    void run();

    enum class Module
    {
        BUTTON = 0,
        CLOCK = 1,
        LIGHT = 2
    };

private:
    Modules m_modules;
    uint16_t i;

};
