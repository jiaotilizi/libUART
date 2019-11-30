/**
 *
 * File Name: uart.c
 * Title    : libUART
 * Project  : libUART
 * Author   : Copyright (C) 2018-1019 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2018-05-21
 * Modified : 2019-11-30
 * Revised  : 
 * Version  : 0.5.0.1
 * License  : ISC (see file LICENSE.txt)
 *
 * NOTE: This code is currently below version 1.0, and therefore is considered
 * to be lacking in some functionality or documentation, or may not be fully
 * tested. Nonetheless, you can expect most functions to work.
 *
 */

#include <stdlib.h>
#include <string.h>

#ifdef __unix__
#include "unix/uart.h"
#include "unix/error.h"
#elif _WIN32
#include <Windows.h>
#include "win32/uart.h"
#include "win32/error.h"
#endif

#include "version.h"
#include "libUART.h"

static int parse_option(uart_t *uart, const char *opt)
{
    int i = 0;
    
    while (opt[i] != '\0') {
        /* parse data bits */
        switch (opt[i]) {
        case '5':
            uart->data_bits = 5;
            break;
        case '6':
            uart->data_bits = 6;
            break;
        case '7':
            uart->data_bits = 7;
            break;
        case '8':
            uart->data_bits = 8;
            break;
        default:
            error("invalid Data Bits", 0);
            return -1;
        }
        
        i++;
        
        /* parse parity */
        switch (opt[i]) {
        case 'N':
            uart->parity = UART_PARITY_NO;
            break;
        case 'O':
            uart->parity = UART_PARITY_ODD;
            break;
        case 'E':
            uart->parity = UART_PARITY_EVEN;
            break;
        default:
            error("invalid Parity", 0);
            return -1;
        }
        
        i++;
        
        /* parse stop bits */
        switch (opt[i]) {
        case '1':
            uart->stop_bits = 1;
            break;
        case '2':
            uart->stop_bits = 2;
            break;
        default:
            error("invalid Stop Bits", 0);
            return -1;
        }
        
        i++;
        
        /* parse flow control */
        switch (opt[i]) {
        case 'N':
            uart->flow_ctrl = UART_FLOW_NO;
            break;
        case 'S':
            uart->flow_ctrl = UART_FLOW_SOFTWARE;
            break;
        case 'H':
            uart->flow_ctrl = UART_FLOW_HARDWARE;
            break;
        default:
            error("invalid Flow control", 0);
            return -1;
        }
        
        i++;
        
        if (opt[i] != '\0') {
            error("invalid Options", 0);
            return -1;
        }
    }
    
    return 0;
}

uart_t *libUART_open(const char *dev, int baud, const char *opt)
{
    uart_t *p;
    
    p = (uart_t *) malloc(sizeof(uart_t));
    
    if (!p) {
        error("malloc() failed", 1);
        return NULL;
    }
    
    if (strlen(dev) >= DEV_NAME_LEN) {
        error("UART device name too long", 0);
        free(p);
        return NULL;
    }
    
    strcpy(p->dev, dev);
    
    if (parse_option(p, opt) == -1) {
        free(p);
        return NULL;
    }
    
    if (!uart_baud_valid(baud)) {
        free(p);
        return NULL;
    }

    p->baud = baud;
    
    if (uart_open(p) == -1) {
        free(p);
        return NULL;
    }
    
    return p;
}

void libUART_close(uart_t *uart)
{
    if (!uart)
        return;
    
    uart_close(uart);
}

int libUART_send(uart_t *uart, char *send_buf, int len)
{
    if (!uart) {
        error("invalid <uart_t> object", 0);
        return -1;
    }
    
    if (!send_buf)
        return -1;
    
    if (len < 1)
        return -1;
    
    return uart_send(uart, send_buf, len);
}

int libUART_recv(uart_t *uart, char *recv_buf, int len)
{
    if (!uart) {
        error("invalid <uart_t> object", 0);
        return -1;
    }
    
    if (!recv_buf)
        return -1;
    
    if (len < 1)
        return -1;
    
    return uart_recv(uart, recv_buf, len);
}

int libUART_set_baud(uart_t *uart, int baud)
{
    if (!uart) {
        error("invalid <uart_t> object", 0);
        return -1;
    }
    
    uart->baud = baud;
    return uart_init_baud(uart);
}

int libUART_puts(uart_t *uart, char *msg)
{
    if (!uart) {
        error("invalid <uart_t> object", 0);
        return -1;
    }
    
    if (!msg)
        return -1;
    
    return uart_send(uart, msg, strlen(msg));
}

int libUART_getc(uart_t *uart, char *c)
{
    char buf[1];
    int ret;
    
    if (!uart) {
        error("invalid <uart_t> object", 0);
        return -1;
    }
    
    if (!c)
        return -1;
    
    ret = uart_recv(uart, &buf[0], 1);
    (*c) = buf[0];
    return ret;
}

int libUART_get_baud(uart_t *uart, int *baud)
{
    if (!uart) {
        error("invalid <uart_t> object", 0);
        return -1;
    }
    
    if (!baud)
        return -1;
    
    (*baud) = uart->baud;
    return 0;
}

#ifdef __unix__
int libUART_get_fd(uart_t *uart, int *fd)
{
    if (!uart) {
        error("invalid <uart_t> object", 0);
        return -1;
    }
    
    if (!fd)
        return -1;
    
    (*fd) = uart->fd;
    return 0;
}
#elif _WIN32
int libUART_get_handle(uart_t *uart, HANDLE *h)
{
    if (!uart) {
        error("invalid <uart_t> object", 0);
        return -1;
    }
    
    if (!h)
        return -1;
    
    (*h) = uart->h;
    return 0;
}
#endif

int libUART_get_dev(uart_t *uart, char **dev)
{
    if (!uart) {
        error("invalid <uart_t> object", 0);
        return -1;
    }
    
    if (!dev)
        return -1;
    
    (*dev) = uart->dev;
    return 0;
}

int libUART_set_databits(uart_t *uart, int data_bits)
{
    if (!uart) {
        error("invalid <uart_t> object", 0);
        return -1;
    }
    
    uart->data_bits = data_bits;
    return uart_init_databits(uart);
}

int libUART_get_databits(uart_t *uart, int *data_bits)
{
    if (!uart) {
        error("invalid <uart_t> object", 0);
        return -1;
    }
    
    if (!data_bits)
        return -1;
    
    (*data_bits) = uart->data_bits;
    return 0;
}

int libUART_set_parity(uart_t *uart, int parity)
{
    if (!uart) {
        error("invalid <uart_t> object", 0);
        return -1;
    }
    
    uart->parity = parity;
    return uart_init_parity(uart);
}

int libUART_get_parity(uart_t *uart, int *parity)
{
    if (!uart) {
        error("invalid <uart_t> object", 0);
        return -1;
    }
    
    if (!parity)
        return -1;
    
    (*parity) = uart->parity;
    return 0;
}

int libUART_set_stopbits(uart_t *uart, int stop_bits)
{
    if (!uart) {
        error("invalid <uart_t> object", 0);
        return -1;
    }
    
    uart->stop_bits = stop_bits;
    return uart_init_stopbits(uart);
}

int libUART_get_stopbits(uart_t *uart, int *stop_bits)
{
    if (!uart) {
        error("invalid <uart_t> object", 0);
        return -1;
    }
    
    if (!stop_bits)
        return -1;
    
    (*stop_bits) = uart->stop_bits;
    return 0;
}

int libUART_set_flowctrl(uart_t *uart, int flow_ctrl)
{
    if (!uart) {
        error("invalid <uart_t> object", 0);
        return -1;
    }
    
    uart->flow_ctrl = flow_ctrl;
    return uart_init_flow(uart);
}

int libUART_get_flowctrl(uart_t *uart, int *flow_ctrl)
{
    if (!uart) {
        error("invalid <uart_t> object", 0);
        return -1;
    }
    
    if (!flow_ctrl)
        return -1;
    
    (*flow_ctrl) = uart->flow_ctrl;
    return 0;
}

int libUART_set_pin(uart_t *uart, int pin, int state)
{
    if (!uart) {
        error("invalid <uart_t> object", 0);
        return -1;
    }
    
    return uart_set_pin(uart, pin, state);
}

int libUART_get_pin(uart_t *uart, int pin, int *state)
{
    if (!uart) {
        error("invalid <uart_t> object", 0);
        return -1;
    }
    
    if (!state)
        return -1;
    
    return uart_get_pin(uart, pin, state);
}

int libUART_get_bytes_available(uart_t *uart, int *num)
{
    if (!uart) {
        error("invalid <uart_t> object", 0);
        return -1;
    }
    
    if (!num)
        return -1;
    
    return uart_get_bytes(uart, num);
}

void libUART_set_error(int enable)
{
    error_enable(enable);
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
