/**
 *
 * File Name: unix/uart.h
 * Title    : UNIX UART library
 * Project  : libUART
 * Author   : Copyright (C) 2018-2019 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2019-11-21
 * Modified : 
 * Revised  : 
 * Version  : 0.1.0.0
 * License  : ISC (see file LICENSE.txt)
 *
 * NOTE: This code is currently below version 1.0, and therefore is considered
 * to be lacking in some functionality or documentation, or may not be fully
 * tested. Nonetheless, you can expect most functions to work.
 *
 */

#ifndef LIBUART_UNIX_UART_H
#define LIBUART_UNIX_UART_H

#define DEV_NAME_LEN        256

struct _uart {
    int fd;
    char dev[DEV_NAME_LEN];
    int baud;
    int data_bits;
    int stop_bits;
    int parity;
    int flow_ctrl;
};

extern int uart_baud_valid(int value);
extern int uart_init_baud(struct _uart *uart);
extern int uart_init_databits(struct _uart *uart);
extern int uart_init_parity(struct _uart *uart);
extern int uart_init_stopbits(struct _uart *uart);
extern int uart_init_flow(struct _uart *uart);
extern int uart_init(struct _uart *uart);
extern struct _uart *uart_open(const char *dev, int baud, const char *opt);
extern void uart_close(struct _uart *uart);
extern int uart_send(struct _uart *uart, char *send_buf, int len);
extern int uart_recv(struct _uart *uart, char *recv_buf, int len);
extern int uart_set_pin(struct _uart *uart, int pin, int state);
extern int uart_get_pin(struct _uart *uart, int pin, int *state);
extern int uart_get_bytes(struct _uart *uart, int *bytes);

#endif
