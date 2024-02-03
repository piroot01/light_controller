#ifndef MODULES_INCLUDED
#define MODULES_INCLUDED


#include "module.h"
#include "packet.h"


#define __MODULE_SIZE__ 3


class Modules
{
public:
    Modules();
    void add(Module& module);
    void update();
    void setup();
    void printPacket();
    bool write(const uint16_t moduleIndex, const uint16_t& data);
    bool read(const uint16_t moduleIndex, uint16_t* data) const;

private:
    Module* m_modules[__MODULE_SIZE__];
    uint16_t m_moduleIndex;
    Packet m_packet;

};


#endif
