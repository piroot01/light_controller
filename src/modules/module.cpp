#include "module.h"


Module::Module() :
    m_packetSize(0)
{
}


void Module::setup() const
{
}


uint16_t Module::packetSize() const
{
    return m_packetSize;
}


void Module::setPacketIndex(const uint16_t index)
{
    m_packetIndex = index;
}
