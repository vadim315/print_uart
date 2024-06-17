//
// Created by Vadim on 11.11.2022.
//

#include "uart_debug.h"


uint8_t BuffReceive[BUFF_RECEIVE_SIZE];
uint8_t Error_string[] = {0x0D,'E','r','r','o','r',' ','D','a','t','a'};

void transmit_error(void){
    HAL_UART_Transmit_DMA(&UART__,&Error_string[0],11);
}

void clear_BuffReceive(void){
    for (int i = 0; i < BUFF_RECEIVE_SIZE; ++i) {
        BuffReceive[i] = 0;
    }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){

}

/* преобразует number(uint_32) в ASCII,
 mark[] - метку "mark" (не более 20 символа) и отправляет в  UART*/

void uint_uart_transmit(char mark[], uint32_t number){
    char buff[100];

    uint8_t length_mark = strlen(mark);

    buff[0] = 0x0D; // включаем перевод строки

    for (uint8_t i = 1; i <= length_mark; i++) buff[i] = mark[i - 1];

    utoa(number, &buff[length_mark +1], 10);

    length_mark = strlen(buff);


//    HAL_UART_Transmit_DMA(&UART,&buff[0],length_mark);
    HAL_UART_Transmit(&UART__,&buff[0], length_mark,10);
}

/* преобразует number(int_32) в ASCII,
 mark[] - метку("mark") длиной length_mark(не более 40 символа) и отправляет в UART*/

void int_uart_transmit(char mark[], uint8_t length_mark, int32_t number){
    char buff[80];
    uint8_t length_number = 0;
    volatile    int8_t n = 0;

    buff[0] = 0x0D; // включаем перевод строки

    for (int i = 0; i < length_mark; i++) buff[i] = mark[i];

    if (number < 0){
        if (number > -2147483649) length_number = 10;
        if (number > -1000000000) length_number = 9;
        if (number > -100000000) length_number = 8;
        if (number > -10000000) length_number = 7;
        if (number > -1000000) length_number = 6;
        if (number > -100000) length_number = 5;
        if (number > -10000) length_number = 4;
        if (number > -1000) length_number = 3;
        if (number > -100) length_number = 2;
        if (number > -10) length_number = 1;
    }
    if (number >= 0){
        n = 1;
        if (number < 2147483647) length_number = 10;
        if (number < 1000000000) length_number = 9;
        if (number < 100000000) length_number = 8;
        if (number < 10000000) length_number = 7;
        if (number < 1000000) length_number = 6;
        if (number < 100000) length_number = 5;
        if (number < 10000) length_number = 4;
        if (number < 1000) length_number = 3;
        if (number < 100) length_number = 2;
        if (number < 10) length_number = 1;
    }
    itoa(number, &buff[length_mark ], 10);

    buff[length_mark + length_number + 1 - n] = 0x0D; // включаем перевод строки

    HAL_UART_Transmit_DMA(&UART__,&buff[0],length_mark + length_number + 2 - n);
}

/* иницилизация UART на прием */
void uart_init_receive(void){
    BuffReceive[0] = 0;
    HAL_UART_Receive_DMA(&UART__,&BuffReceive[0],BUFF_RECEIVE_SIZE);
}

/* принимает в ASCII кодах, команды command длиной command_length и числа data после команды, по UART
 * пример команды: asd12345 */

uint8_t uart_receive(void){


    if ((UART__.Instance->SR & UART_FLAG_IDLE) == UART_FLAG_IDLE){

        HAL_UART_AbortReceive(&UART__);
        HAL_UART_Receive_DMA(&UART__,&BuffReceive[0],BUFF_RECEIVE_SIZE);
        return Yes;
    }
    return No;
}




/* функция переводит ASCII символы длинной max_length_data, следующие до разделительного символа end_symbol,в uint16_t
 *  пример  12е -> 12 */
bool string_to_data(uint8_t *cnt, char end_symbol, uint8_t *buf,uint16_t *data, uint8_t max_length_data){
    uint8_t tmp_buf[25];
    uint8_t tmp_cnt = 0;

    for(uint8_t i = *cnt; i <= max_length_data + *cnt; i++){

        if(buf[i] >= '0' && buf[i] <= '9'){
            tmp_buf[tmp_cnt] = buf[i];
            tmp_cnt++;
            tmp_buf[tmp_cnt] = 0;
        }
        else{
            if(buf[i] == (uint8_t)end_symbol){
                *data = atoi(&tmp_buf[0]);
                *cnt += tmp_cnt++ + 1;
                return true;
            }
            else  return false;
        }
    }

}
