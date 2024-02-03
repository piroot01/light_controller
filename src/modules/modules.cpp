#include "modules.h"
#include <Arduino.h>


Modules::Modules() :
    m_moduleIndex(0), m_packet(0)
{
}


void Modules::add(Module& module)
{
    module.setPacketIndex(m_packet.size());
    m_modules[m_moduleIndex] = &module;
    m_moduleIndex++;
    m_packet.resize(m_packet.size() + module.packetSize());
}


void Modules::setup()
{
    for (int i = 0; i < __MODULE_SIZE__; ++i)
        m_modules[i]->setup();
}

void Modules::update()
{
    for (int i = 0; i < __MODULE_SIZE__; ++i)
        m_modules[i]->update(m_packet);
}


void Modules::printPacket()
{
    for (int i = 0; i < m_packet.size(); ++i)
        Serial.print(m_packet.data()[i]);
    Serial.println("\n---");
}
