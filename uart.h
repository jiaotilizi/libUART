/**
 *
 * File Name: uart.h
 * Title    : UART library header 
 * Project  : libuart
 * Author   : Copyright (C) 2018 krjdev@gmail.com
 * Created  : 2018-05-21
 * Modified : 2018-05-24
 * Revised  : 
 * Version  : 0.1.0.0
 * License  : BSD-3-Clause (see file LICENSE.txt)
 *
 * NOTE: This code is currently below version 1.0, and therefore is considered
 * to be lacking in some functionality or documentation, or may not be fully
 * tested. Nonetheless, you can expect most functions to work.
 *
 */

#ifndef UART_H
#define UART_H

#define BUFSZ 256

typedef struct str_uart {
    int fd;
    char dev[BUFSZ];
    int baud;
    int data_bits;
    int stop_bits;
    int parity;
    int flow_ctrl;
} uart_t;

enum e_baud {
    UART_BAUD_0 = 0,
    UART_BAUD_50 = 50,
    UART_BAUD_75 = 75,
    UART_BAUD_110 = 110,
    UART_BAUD_134 = 134,
    UART_BAUD_150 = 150,
    UART_BAUD_200 = 200,
    UART_BAUD_300 = 300,
    UART_BAUD_600 = 600,
    UART_BAUD_1200 = 1200,
    UART_BAUD_1800 = 1800,
    UART_BAUD_2400 = 2400,
    UART_BAUD_4800 = 4800,
    UART_BAUD_9600 = 9600,
    UART_BAUD_19200 = 19200,
    UART_BAUD_38400 = 38400,
    UART_BAUD_57600 = 57600,
    UART_BAUD_115200 = 115200
};

enum e_parity {
    UART_PARITY_NO,
    UART_PARITY_ODD,
    UART_PARITY_EVEN
};

enum e_flow {
    UART_FLOW_NO,
    UART_FLOW_SOFTWARE,
    UART_FLOW_HARDWARE
};

enum e_pins {
    UART_PIN_RTS,   /* Request to Send (out) */
    UART_PIN_CTS,   /* Clear to Send (in) */
    UART_PIN_DSR,   /* Data Set Ready (in) */
    UART_PIN_DCD,   /* Data Carrier Detect (in) */
    UART_PIN_DTR,   /* Data Terminal Ready (out) */
    UART_PIN_RI     /* Ring Indicator (in) */
};

#define UART_PIN_LOW 0
#define UART_PIN_HIGH 1

extern uart_t *uart_open(const char *dev, int baud, const char *opt);
extern void uart_close(uart_t *uart);
extern int uart_send(uart_t *uart, char *send_buf, int len);
extern int uart_recv(uart_t *uart, char *recv_buf, int len);
extern void uart_baud_set(uart_t *uart, int baud);
extern int uart_baud_get(uart_t *uart);
extern int uart_fd_get(uart_t *uart);
extern char *uart_dev_get(uart_t *uart);
extern void uart_databits_set(uart_t *uart, int data_bits);
extern int uart_databits_get(uart_t *uart);
extern void uart_parity_set(uart_t *uart, int parity);
extern int uart_parity_get(uart_t *uart);
extern void uart_stopbits_set(uart_t *uart, int stop_bits);
extern int uart_stopbits_get(uart_t *uart);
extern void uart_flow_set(uart_t *uart, int flow_ctrl);
extern int uart_flow_get(uart_t *uart);
extern void uart_pin_set(uart_t *uart, int pin, int state);
extern int uart_pin_get(uart_t *uart, int pin);
extern int uart_bytes_get(uart_t *uart);

#endif
