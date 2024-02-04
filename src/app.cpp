#include "app.h"
#include "modules/button.h"
#include "modules/clock.h"
#include "modules/light.h"


App::App() :
    time(0)
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
}


void App::run()
{
    time = millis();
    m_modules.update();
    m_modules.printPacket();;
    m_logic.loadModules(&m_modules);
    m_logic.implementation(time);
}
