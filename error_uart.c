/**
 *
 * File Name: error_uart.c
 * Title    : UART library error messages source
 * Project  : libuart
 * Author   : Copyright (C) 2018 krjdev@gmail.com
 * Created  : 2018-05-21
 * Modified : 2018-05-23
 * Revised  : 
 * Version  : 0.1.0.0
 * License  : BSD-3-Clause (see file LICENSE.txt)
 *
 * NOTE: This code is currently below version 1.0, and therefore is considered
 * to be lacking in some functionality or documentation, or may not be fully
 * tested. Nonetheless, you can expect most functions to work.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "error.h"

void printerr_uart_type_invalid(void)
{
    printerr();
    fprintf(stderr, "invalid uart_type (uart_t)\n");
}

void printerr_uart_dev_too_long(void)
{
    printerr();    
    fprintf(stderr, "device/file name too long\n");
}

void printerr_uart_opt_invalid(const char *err_msg)
{
    printerr();
    
    if (err_msg == NULL)
        fprintf(stderr, "invalid option\n");
    else
        fprintf(stderr, "invalid option (%s)\n", err_msg);
}

void printerr_uart_baud_invalid(void)
{
    printerr();
    fprintf(stderr, "invalid baud rate\n");
}

void printerr_uart_data_invalid(void)
{
    printerr();
    fprintf(stderr, "invalid data bits\n");
}

void printerr_uart_parity_invalid(void)
{
    printerr();
    fprintf(stderr, "invalid parity\n");
}

void printerr_uart_stop_invalid(void)
{
    printerr();
    fprintf(stderr, "invalid stop bits\n");
}

void printerr_uart_flow_invalid(void)
{
    printerr();
    fprintf(stderr, "invalid flow control\n");
}

void printerr_uart_pin_invalid(void)
{
    printerr();
    fprintf(stderr, "invalid control pin\n");
}
