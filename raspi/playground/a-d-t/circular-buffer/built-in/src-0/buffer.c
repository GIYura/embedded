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
} Buffer_t;

static Buffer_t m_buffer;

void BufferInit(void)
{
    m_buffer.head = 0;
    m_buffer.tail = 0; 
    m_buffer.size = BUFF_SIZE;
    memset(m_buffer.buffer, 0, sizeof(m_buffer.buffer));
}

void BufferDeinit(void)
{
    m_buffer.head = 0;
    m_buffer.tail = 0; 
}

bool BufferPut(int item)
{
    /* verify buffer full */
    if (((m_buffer.head + 1) % m_buffer.size) == m_buffer.tail)
    {
        return false;
    }

    /* put item in the buffer */
    m_buffer.buffer[m_buffer.head] = item;    

    /* advance head */
    m_buffer.head = (m_buffer.head + 1) % m_buffer.size;

    return true;
}

bool BufferGet(int* item)
{
    /* verify buffer empty */
    if (m_buffer.head == m_buffer.tail)
    {
        return false;
    }
    
    /* retreive item  */
    *item = m_buffer.buffer[m_buffer.tail];

    /* advance tail */
    m_buffer.tail = (m_buffer.tail + 1) % m_buffer.size;

    return true;
}

