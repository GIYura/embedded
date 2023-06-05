#include <string.h>
#include "buffer.h"

typedef struct 
{
    int head;
    int tail;
    int count;
    int itemSize;
    int* buffer;
} Ring_t;

static Ring_t m_ring;

void RingInit(void* buff, int itemSize, int count)
{
    m_ring.head = 0;
    m_ring.tail = 0; 
    m_ring.count = count;
    m_ring.itemSize = itemSize;
    m_ring.buffer = buff;
}

void RingDeinit(void)
{
    m_ring.head = 0;
    m_ring.tail = 0; 
}

bool RingEnqueue(void* item, int size)
{
    /* verify buffer full */
    if (((m_ring.head + 1) % m_ring.count) == m_ring.tail)
    {
        return false;
    }

    /* put the item */
    memcpy(&m_ring.buffer[m_ring.head], item, m_ring.itemSize);

    /* advance head */
    m_ring.head = m_ring.head + m_ring.itemSize;

    return true;
}

bool RingDequeue(void* item, int size)
{
    /* verify buffer empty */
    if (m_ring.head == m_ring.tail)
    {
        return false;
    }

    /* retreive item */
    memcpy(item, &m_ring.buffer[m_ring.tail], m_ring.itemSize);

    /* advance tail */
    m_ring.tail = m_ring.tail + m_ring.itemSize;

    return true;
}

