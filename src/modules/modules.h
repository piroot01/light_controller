#ifndef MODULES_INCLUDED
#define MODULES_INCLUDED


#include "module.h"
#include "packet.h"


#define __MODULE_SIZE__ 2


class Modules
{
public:
    Modules();
    void add(Module& module);
    void update();
    void setup();
    void printPacket();

private:
    Module* m_modules[__MODULE_SIZE__];
    uint16_t m_moduleIndex;
    Packet m_packet;

};


#endif
