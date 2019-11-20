/**
 *
 * File Name: uart.c
 * Title    : libUART
 * Project  : libUART
 * Author   : Copyright (C) 2018-1019 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2018-05-21
 * Modified : 2019-11-20
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

static int is_baud_valid(int value)
{
    int E[] = {
#ifdef __unix__
        UART_BAUD_0,
        UART_BAUD_50,
        UART_BAUD_75,
#endif
        UART_BAUD_110,
#ifdef __unix__
        UART_BAUD_134,
        UART_BAUD_150,
        UART_BAUD_200,
#endif
        UART_BAUD_300,
        UART_BAUD_600,
        UART_BAUD_1200,
#ifdef __unix__
        UART_BAUD_1800,
#endif
        UART_BAUD_2400,
        UART_BAUD_4800,
        UART_BAUD_9600,
#ifdef _WIN32
        UART_BAUD_14400,
#endif
        UART_BAUD_19200,
        UART_BAUD_38400,
        UART_BAUD_57600,
        UART_BAUD_115200,
#ifdef _WIN32
        UART_BAUD_128000,
        UART_BAUD_256000
#elif __unix__
        UART_BAUD_230400,
        UART_BAUD_460800,
        UART_BAUD_500000,
        UART_BAUD_576000,
        UART_BAUD_921600,
        UART_BAUD_1000000,
        UART_BAUD_1152000,
        UART_BAUD_1500000,
        UART_BAUD_2000000,
        UART_BAUD_2500000,
        UART_BAUD_3000000,
        UART_BAUD_3500000,
        UART_BAUD_4000000
#endif /* __unix__ or _WIN32 */
    };
    
    if (enum_contains(E, sizeof(E)/sizeof(E[0]), value))
        return 1;
    
    return 0;
}

static int is_databits_valid(int value)
{
    if ((value > 4) && (value < 9))
        return 1;
    
    return 0;
}

static int is_parity_valid(int value)
{
    int ret = 0;
    
    switch (value) {
    case UART_PARITY_NO:
        ret = 1;
        break;
    case UART_PARITY_ODD:
        ret = 1;
        break;
    case UART_PARITY_EVEN:
        ret = 1;
        break;
    default:
        break;
    }
    
    return ret;
}

static int is_stopbits_valid(int value)
{
    if ((value > 0) && (value < 3))
        return 1;
    
    return 0;
}

static int is_flow_valid(int value)
{
    int ret = 0;
    
    switch (value) {
    case UART_FLOW_NO:
        ret = 1;
        break;
    case UART_FLOW_SOFTWARE:
        ret = 1;
        break;
    case UART_FLOW_HARDWARE:
        ret = 1;
        break;
    default:
        break;
    }
    
    return ret;
}

static int parse_option(uart_t *uart, const char *opt)
{
    int i = 0;
    
    if (!uart) {
        printerr_uart_type_invalid();
        return -1;
    }
    
    if (!opt) {
        printerr_string_null();
        return -1;
    }
    
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
            printerr_uart_opt_invalid("data bits");
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
            printerr_uart_opt_invalid("parity");
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
            printerr_uart_opt_invalid("stop bits");
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
            printerr_uart_opt_invalid("flow control");
            return -1;
        }
        
        i++;
        
        if (opt[i] != '\0') {
            printerr_uart_opt_invalid(NULL);
            return -1;
        }
    }
    
    return 0;
}

void uart_baud_set(uart_t *uart, int baud)
{
    if (!uart) {
        printerr_uart_type_invalid();
        return;
    }
    
    if (!is_baud_valid(baud)) {
        printerr_uart_baud_invalid();
        return;
    }
    
    uart->baud = baud;
    init_baud(uart);
}

int uart_baud_get(uart_t *uart)
{
    if (!uart) {
        printerr_uart_type_invalid();
        return 0;
    }
    
    return uart->baud; 
}

#ifdef __unix__
int uart_fd_get(uart_t *uart)
{
    if (!uart) {
        printerr_uart_type_invalid();
        return -1;
    }
    
    return uart->fd;
}
#elif _WIN32
HANDLE uart_handle_get(uart_t *uart)
{
    if (!uart) {
        printerr_uart_type_invalid();
        return INVALID_HANDLE_VALUE;
    }
    
    return uart->h;
}
#endif /* __unix__ or _WIN32 */

char *uart_dev_get(uart_t *uart)
{
    char *p;
    
    if (!uart) {
        printerr_uart_type_invalid();
        return NULL;
    }
    
    p = malloc(strlen(uart->dev) + 1);
    
    if (!p) {
        printerr_alloc(strerror(errno));
        return NULL;
    }
    
    strcpy(p, uart->dev);
    return p; 
}

void uart_databits_set(uart_t *uart, int data_bits)
{
    if (!uart) {
        printerr_uart_type_invalid();
        return;
    }
    
    if (!is_databits_valid(data_bits))
    {
        printerr_uart_data_invalid();
        return;
    }
    
    uart->data_bits = data_bits;
    init_databits(uart);
}

int uart_databits_get(uart_t *uart)
{
    if (!uart) {
        printerr_uart_type_invalid();
        return 0;
    }
    
    return uart->data_bits;
}

void uart_parity_set(uart_t *uart, int parity)
{
    if (!uart) {
        printerr_uart_type_invalid();
        return;
    }
    
    if (!is_parity_valid(parity))
    {
        printerr_uart_parity_invalid();
        return;
    }
    
    uart->parity = parity;
    init_parity(uart);
}

int uart_parity_get(uart_t *uart)
{
    if (!uart) {
        printerr_uart_type_invalid();
        return 0;
    }
    
    return uart->parity;
}

void uart_stopbits_set(uart_t *uart, int stop_bits)
{
    if (!uart) {
        printerr_uart_type_invalid();
        return;
    }
    
    if (!is_stopbits_valid(stop_bits))
    {
        printerr_uart_stop_invalid();
        return;
    }
    
    uart->stop_bits = stop_bits;
    init_stopbits(uart);
}

int uart_stopbits_get(uart_t *uart)
{
    if (!uart) {
        printerr_uart_type_invalid();
        return 0;
    }
    
    return uart->stop_bits;
}

void uart_flow_set(uart_t *uart, int flow_ctrl)
{
    if (!uart) {
        printerr_uart_type_invalid();
        return;
    }
    
    if (!is_flow_valid(flow_ctrl))
    {
        printerr_uart_flow_invalid();
        return;
    }
    
    uart->flow_ctrl = flow_ctrl;
    init_flow(uart);
}

int uart_flow_get(uart_t *uart)
{
    if (!uart) {
        printerr_uart_type_invalid();
        return 0;
    }
    
    return uart->flow_ctrl;
}

uart_t *libUART_open(const char *dev, int baud, const char *opt)
{
    
}

void libUART_close(uart_t *uart)
{
    
}

int libUART_send(uart_t *uart, char *send_buf, int len)
{
    
}

int libUART_recv(uart_t *uart, char *recv_buf, int len)
{
    
}

void libUART_set_baud(uart_t *uart, int baud)
{
    
}

int libUART_get_baud(uart_t *uart)
{
    
}

int libUART_get_fd(uart_t *uart)
{
    
}

char *libUART_get_dev(uart_t *uart)
{
    
}

void libUART_set_databits(uart_t *uart, int data_bits)
{
    
}

int libUART_get_databits(uart_t *uart)
{
    
}

void libUART_set_parity(uart_t *uart, int parity)
{
    
}

int libUART_get_parity(uart_t *uart)
{
    
}

void libUART_set_stopbits(uart_t *uart, int stop_bits)
{
    
}

int libUART_get_stopbits(uart_t *uart)
{
    
}

void libUART_set_flowctrl(uart_t *uart, int flow_ctrl)
{
    
}

int libUART_get_flowctrl(uart_t *uart)
{
    
}

void libUART_set_pin(uart_t *uart, int pin, int state)
{
    
}

int libUART_get_pin(uart_t *uart, int pin)
{
    
}

int libUART_get_bytes_available(uart_t *uart)
{
    
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
