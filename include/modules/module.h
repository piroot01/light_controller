#ifndef MODULE_INCLUDED
#define MODULE_INCLUDED


#include <Arduino.h>
#include "packet.h"


enum class Permission
{
    READ,
    WRITE,
    READWRITE
};


class Module
{
public:
    Module();
    virtual void setup() const;
    virtual void update(Packet& packet) = 0;
    uint16_t packetSize() const;
    uint16_t packetIndex() const;
    void setPacketIndex(const uint16_t index);
    Permission permission() const;

protected:
    uint16_t m_packetSize; 
    uint16_t m_packetIndex;
    Permission m_permission;

};


#endif
