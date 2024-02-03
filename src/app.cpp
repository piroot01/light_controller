#include "app.h"
#include "modules/button.h"
#include "modules/clock.h"


App::App()
{
}


void App::setup()
{
    Button button(BUTTON_PIN);
    Clock clock;
    m_modules.add(button);
    m_modules.add(clock);
    m_modules.setup();
}


void App::run()
{
    m_modules.update();
    m_modules.printPacket();
}
