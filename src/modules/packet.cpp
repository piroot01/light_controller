#include "packet.h"
#include <stdlib.h>


Packet::Packet(const uint16_t size)
{
    m_size = size;
    m_data = (uint16_t*)malloc(size);
}


uint16_t Packet::size() const
{
    return m_size;
}


uint16_t* Packet::data()
{
    return m_data;
}

bool Packet::resize(const uint16_t newSize)
{
    uint16_t* newData = (uint16_t*)realloc(m_data, newSize * sizeof(uint16_t));
    if (newData == NULL)
        return false;
    m_data = newData;
    m_size = newSize;
    return true;
}
