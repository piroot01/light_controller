#ifndef BUTTON_INCLUDED
#define BUTTON_INCLUDED


#include <Arduino.h>
#include "module.h"


#define __BUTTON_PACKET_SIZE__ 1


class Button : public Module
{
public:
    Button(const uint8_t pin);
    void setup() const override;
    void update(Packet& packet) override;

private:
    uint8_t m_pin;
    bool m_currentState;
    uint32_t m_stateTime;

};


#endif
