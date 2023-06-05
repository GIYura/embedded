#include "buffer.h"

typedef struct 
{
    int head;
    int tail;
    int size;
    int* buffer;
} Ring_t;

static Ring_t m_ring;

void RingInit(int* buff, int buffSize)
{
    m_ring.head = 0;
    m_ring.tail = 0; 
    m_ring.size = buffSize;
    m_ring.buffer = buff;
}

void RingDeinit(void)
{
    m_ring.head = 0;
    m_ring.tail = 0; 
}

bool RingEnqueue(int item)
{
    /* verify buffer full */
    if (((m_ring.head + 1) % m_ring.size) == m_ring.tail)
    {
        return false;
    }

    /* put item in the buffer */
    m_ring.buffer[m_ring.head] = item;    

    /* advance head */
    m_ring.head = (m_ring.head + 1) % m_ring.size;

    return true;
}

bool RingDequeue(int* item)
{
    /* verify buffer empty */
    if (m_ring.head == m_ring.tail)
    {
        return false;
    }
    
    /* retreive item  */
    *item = m_ring.buffer[m_ring.tail];

    /* advance tail */
    m_ring.tail = (m_ring.tail + 1) % m_ring.size;

    return true;
}

