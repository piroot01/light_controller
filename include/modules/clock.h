#ifndef CLOCK_INCLUDED
#define CLOCK_INCLUDED


#include <DS3231.h>
#include "module.h"


#define __CLOCK_PACKET_SIZE__ 3


class Clock : public Module
{
public:

    Clock();
    void update(Packet& packet) override;

private:
    RTClib m_rtc;

};


#endif
