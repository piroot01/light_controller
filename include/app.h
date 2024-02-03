#include <Arduino.h>
#include "modules/clock.h"
#include "modules/modules.h"


#define BUTTON_PIN 5


class App
{
public:
    App();
    void setup();
    void run();

private:
    Modules m_modules;

};
