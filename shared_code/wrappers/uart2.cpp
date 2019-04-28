/*
 * uart2.cpp
 *
 *  Created on: Apr 21, 2019
 *      Author: lenovo
 */
#include "uart2.h"
#include "uart2.hpp"

// Assuming UART2 is already initialized
// You may want to also add uart2_init() in C

bool uart2_getchar(char *byte, uint32_t timeout_ms) {
    Uart2::getInstance().getChar(byte, timeout_ms);
    return true;
}

bool uart_init(unsigned int baudrate, int rxQSize, int txQSize ){
    Uart2::getInstance().init(baudrate,rxQSize,txQSize);
    return true;
}

bool uart2_putchar(char sendbyte, unsigned int timeout){
    Uart2::getInstance().putChar(sendbyte,timeout);
    return true;
}



