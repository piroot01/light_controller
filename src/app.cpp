#include "app.h"
#include "modules/button.h"
#include "modules/clock.h"
#include "modules/light.h"


App::App()
{
}


void App::setup()
{
    Button button(BUTTON_PIN);
    Clock clock;
    Light light(LIGHT_PIN);
    m_modules.add(button);
    m_modules.add(clock);
    m_modules.add(light);
    m_modules.setup();
    i = 0;
}


void App::run()
{
    m_modules.update();
    m_modules.printPacket();
    m_modules.write(2, &i);
    i++;
    if (i > 230)
        i = 0;
}
