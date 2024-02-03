#ifndef MODULE_INCLUDED
#define MODULE_INCLUDED


#include <Arduino.h>
#include "packet.h"


class Module
{
public:
    Module();
    virtual void setup() const;
    virtual void update(Packet& packet) = 0;
    uint16_t packetSize() const;
    void setPacketIndex(const uint16_t index);

protected:
    uint16_t m_packetSize; 
    uint8_t m_packetIndex;

};


#endif
