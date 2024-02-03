#include "modules/light.h"


Light::Light(const uint8_t pin) :
    m_pin(pin)
{
    m_permission = Permission::WRITE;
    m_packetSize = __LIGHT_PACKET_SIZE__;
}


void Light::setup() const 
{
    pinMode(m_pin, OUTPUT);
}


void Light::update(Packet& packet)
{
    analogWrite(m_pin, packet.data()[m_packetIndex]);
}
