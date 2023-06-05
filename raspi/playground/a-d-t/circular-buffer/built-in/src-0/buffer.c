#include <string.h>
#include <stdio.h>

#include "buffer.h"

#define BUFF_SIZE   10

typedef struct 
{
    int head;
    int tail;
    int size;
    int buffer[BUFF_SIZE];
} Ring_t;

static Ring_t m_ring;

void RingInit(void)
{
    m_ring.head = 0;
    m_ring.tail = 0; 
    m_ring.size = BUFF_SIZE;
    memset(m_ring.buffer, 0, sizeof(m_ring.buffer));
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

