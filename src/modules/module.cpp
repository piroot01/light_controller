#include "modules/module.h"


Module::Module() :
    m_packetSize(0), m_permission(Permission::READ)
{
}


void Module::setup() const
{
}


uint16_t Module::packetSize() const
{
    return m_packetSize;
}


uint16_t Module::packetIndex() const
{
    return m_packetIndex;
}


void Module::setPacketIndex(const uint16_t index)
{
    m_packetIndex = index;
}


Permission Module::permission() const
{
    return m_permission;
}
