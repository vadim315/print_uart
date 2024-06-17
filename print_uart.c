//
// Created by Vadim on 14.06.2024.
//

#include "print_uart.h"

void ftoa_(float f, char *str_num, int precision);

void print_UART(char *format, ...){
    char buff[100];
    char number_str[100];
    for(int w = 0; w < 100; w++) {buff[w] = 0; number_str[w] = 0;}
    uint8_t pos_buff = 0;
    int d;
    float f;
    va_list factor;
    va_start(factor,format);

    for(char *c = format; *c; c++){
        if(*c != '%'){
            buff[pos_buff] = *c;
            pos_buff++;
        } else{
            switch (*++c) {
                case 'd':
                    d = va_arg(factor,int);
                    itoa(d, number_str, 10);
                    break;
                case 'f':
                    f = va_arg(factor, double );
                    ftoa_(f, number_str, PRECISION_SET);
                    break;
            }
            strcat(buff, number_str);
            pos_buff += strlen(number_str);
        }
    }
    va_end(factor);
    HAL_UART_Transmit(&huart3,(uint8_t *)&buff[0], pos_buff,10000);
}

void ftoa_(float f, char *str_num, int precision){
    char str[30];
    char str_[30];
    int num;
    int num_;
    int k_presecion = 1;
    for(int i = 0; i < precision; i++) k_presecion *= 10;

    num = (int) f;
    itoa(num, str, 10);
    strcat(str ,".");

    if(f < 0) {f *= -1; num *= -1;} // если f отрицательно
    num_ = (f - num) * k_presecion;
    itoa(num_,str_, 10);
    strcat(str, str_);

    for(int q = 0; q < strlen(str); q ++){
      *str_num = str[q];
       str_num += 1;
    }
}















