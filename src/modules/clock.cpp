#include "clock.h"


Clock::Clock()
{
    m_packetSize = __CLOCK_PACKET_SIZE__;
}


void Clock::update(Packet& packet)
{
    DateTime now = m_rtc.now();
    packet.data()[m_packetIndex] = now.hour();
    packet.data()[m_packetIndex + 1] = now.minute();
    packet.data()[m_packetIndex + 2] = now.second();
}
