//
// Created by Vadim on 11.11.2022.
//

#ifndef _UART_DEBUG_H
#define _UART_DEBUG_H

#include "main.h"
#include <stdlib.h>
#include "usart.h"
#include <string.h>
#include "dma.h"

#include <stdbool.h>

#define UART__    huart3
#define BUFF_RECEIVE_SIZE   100 // размер буфера для приема

enum{
    No,
    Yes
};

extern uint8_t BuffReceive[BUFF_RECEIVE_SIZE];
extern DMA_HandleTypeDef hdma_usart3_tx;
extern DMA_HandleTypeDef hdma_usart3_rx;

void clear_BuffReceive(void);
void uint_uart_transmit(char mark[], uint32_t number);
void int_uart_transmit(char mark[], uint8_t length_mark, int32_t number);
void uart_init_receive(void);
uint8_t uart_receive(void);
void transmit_error(void);
bool string_to_data(uint8_t *cnt, char end_symbol, uint8_t *buf,uint16_t *data, uint8_t max_length_data);
void send_sensorERROR(uint8_t numberSensor);
void send_FIRE(void);
#endif //_UART_DEBUG_H
