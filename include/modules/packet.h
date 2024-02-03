#ifndef PACKET_INCLUDED
#define PACKET_INCLUDED


#include <Arduino.h>


class Packet
{
public:
    Packet(const uint16_t packetSize);
    uint16_t* data();
    uint16_t* data() const;
    uint16_t size() const;
    bool resize(const uint16_t newSize);

private:
    uint16_t* m_data;
    uint16_t m_size;

};


#endif
