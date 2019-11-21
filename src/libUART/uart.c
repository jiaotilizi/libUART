/**
 *
 * File Name: uart.c
 * Title    : libUART
 * Project  : libUART
 * Author   : Copyright (C) 2018-1019 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2018-05-21
 * Modified : 2019-11-21
 * Revised  : 
 * Version  : 0.3.0.0
 * License  : ISC (see file LICENSE.txt)
 *
 * NOTE: This code is currently below version 1.0, and therefore is considered
 * to be lacking in some functionality or documentation, or may not be fully
 * tested. Nonetheless, you can expect most functions to work.
 *
 */
 
#ifdef __unix__
#include "unix/uart.h"
#elif _WIN32
#include <Windows.h>
#include "win32/uart.h"
#endif

#include "version.h"
#include "libUART.h"

uart_t *libUART_open(const char *dev, int baud, const char *opt)
{
    return uart_open(dev, baud, opt);
}

void libUART_close(uart_t *uart)
{
    return uart_close(uart);
}

int libUART_send(uart_t *uart, char *send_buf, int len)
{
    return uart_send(uart, send_buf, len);
}

int libUART_recv(uart_t *uart, char *recv_buf, int len)
{
    return uart_recv(uart, recv_buf, len);
}

int libUART_set_baud(uart_t *uart, int baud)
{
    uart->baud = baud;
    return uart_init_baud(uart);
}

int libUART_get_baud(uart_t *uart, int *baud)
{
    (*baud) = uart->baud;
    return 0;
}

int libUART_get_fd(uart_t *uart, int *fd)
{
    (*fd) = uart->fd;
    return 0;
}

int libUART_get_dev(uart_t *uart, char **dev)
{
    (*dev) = uart->dev;
    return 0;
}

int libUART_set_databits(uart_t *uart, int data_bits)
{
    uart->data_bits = data_bits;
    return uart_init_databits(uart);
}

int libUART_get_databits(uart_t *uart, int *data_bits)
{
    (*data_bits) = uart->data_bits;
    return 0;
}

int libUART_set_parity(uart_t *uart, int parity)
{
    uart->parity = parity;
    return uart_init_parity(uart);
}

int libUART_get_parity(uart_t *uart, int *parity)
{
    (*parity) = uart->parity;
    return 0;
}

int libUART_set_stopbits(uart_t *uart, int stop_bits)
{
    uart->stop_bits = stop_bits;
    return uart_init_stopbits(uart);
}

int libUART_get_stopbits(uart_t *uart, int *stop_bits)
{
    (*stop_bits) = uart->stop_bits;
    return 0;
}

int libUART_set_flowctrl(uart_t *uart, int flow_ctrl)
{
    uart->flow_ctrl = flow_ctrl;
    return uart_init_flow(uart);
}

int libUART_get_flowctrl(uart_t *uart, int *flow_ctrl)
{
    (*flow_ctrl) = uart->flow_ctrl;
    return 0;
}

int libUART_set_pin(uart_t *uart, int pin, int state)
{
    return uart_set_pin(uart, pin, state);
}

int libUART_get_pin(uart_t *uart, int pin, int *state)
{
    return uart_get_pin(uart, pin, state);
}

int libUART_get_bytes_available(uart_t *uart, int *num)
{
    return uart_get_bytes(uart, num);
}

char *libUART_get_libname(void)
{
    return LIBUART_NAME;
}

char *libUART_get_libversion(void)
{
    return LIBUART_VERSION;
}

char *libUART_get_libcopyright(void)
{
    return LIBUART_COPYRIGHT;
}
