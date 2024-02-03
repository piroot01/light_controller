#ifndef LIGHT_INCLUDED
#define LIGHT_INCLUDED


#include "module.h"


#define __LIGHT_PACKET_SIZE__ 1


class Light : public Module
{
public:
    Light(const uint8_t pin);
    void setup() const override;
    void update(Packet& packet) override;

private:
    uint8_t m_pin;

};


#endif
