// Wrapper for the UART Assignment

#ifndef UART_WRAPPER_H__
#define UART_WRAPPER_H__

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

bool uart2_init(unsigned int baud, int rx_size, int tx_size);
bool uart2_putChar(char msg_char, unsigned int timeout_ms);
bool uart2_getChar(char* pInputChar, unsigned int timeout_ms);
void uart2_putLine(const char* pBuff, unsigned int timeout);
bool uart2_gets(char* pBuff, int maxLen, unsigned int timeout);
bool uart2_flush(void);

bool uart3_init(unsigned int baud, int rx_size, int tx_size);
bool uart3_putChar(char msg_char, unsigned int timeout_ms);
bool uart3_getChar(char* pInputChar, unsigned int timeout_ms);
void uart3_putLine(const char* pBuff, unsigned int timeout);
bool uart3_gets(char* pBuff, int maxLen, unsigned int timeout);

#ifdef __cplusplus
}
#endif
#endif /* UART_WRAPPER_H__ */
