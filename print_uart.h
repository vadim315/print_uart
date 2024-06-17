//
// Created by Vadim on 14.06.2024.
//

#ifndef DFP_PRINT_UART_H
#define DFP_PRINT_UART_H

#define PRECISION_SET   1

#include "main.h"
#include "usart.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void print_UART(char *format, ...);

#endif //DFP_PRINT_UART_H
