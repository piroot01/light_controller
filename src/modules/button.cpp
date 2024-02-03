#include "modules/button.h"
#include "modules/module.h"


Button::Button(const uint8_t pin) :
    m_pin(pin)
{
    m_packetSize = __BUTTON_PACKET_SIZE__;
}


void Button::setup() const
{
    pinMode(m_pin, INPUT);
}


void Button::update(Packet& packet)
{
    m_currentState = digitalRead(m_pin);
    packet.data()[m_packetIndex] = m_currentState;
}
