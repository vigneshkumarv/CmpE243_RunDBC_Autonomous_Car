//Wrapper for the UART

#include "uart_wrapper.h"
#include "uart2.hpp"
#include "uart3.hpp"

Uart2& u2 = Uart2::getInstance();

/////////uart  2 ///////////
bool uart2_init(unsigned int baud, int rx_size, int tx_size)
{
    return u2.init(baud, rx_size, tx_size);
}

bool uart2_putChar(char msg_char, unsigned int timeout)
{
  return u2.putChar(msg_char, timeout);
}

bool uart2_getChar(char* pInputChar, unsigned int timeout)
{
    return u2.getChar(pInputChar, timeout);
}

void uart2_putLine(const char* pBuff, unsigned int timeout)
{
    u2.putline(pBuff, timeout);
}

bool uart2_gets(char* pBuff, int maxLen, unsigned int timeout)
{
    return u2.gets(pBuff, maxLen, timeout);
}

bool uart2_flush(void)
{
    return u2.flush();
}

///////uart 3 /////////////

bool uart3_init(unsigned int baud, int rx_size, int tx_size)
{
    return Uart3::getInstance().init(baud, rx_size, tx_size);
}

bool uart3_putChar(char msg_char, unsigned int timeout_ms)
{
  return Uart3::getInstance().putChar(msg_char, timeout_ms);
}

bool uart3_getChar(char* pInputChar, unsigned int timeout_ms)
{
    return Uart3::getInstance().getChar(pInputChar, timeout_ms);
}

void uart3_putLine(const char* pBuff, unsigned int timeout)
{
   Uart3::getInstance().putline(pBuff, timeout);
}

bool uart3_gets(char* pBuff, int maxLen, unsigned int timeout)
{
    return Uart3::getInstance().gets(pBuff, maxLen);
}


