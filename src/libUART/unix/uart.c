/**
 *
 * File Name: unix/uart.c
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
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

#include "../libUART.h"
#include "../util.h"
#include "error.h"
#include "uart.h"

static int parse_option(struct _uart *uart, const char *opt)
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

int uart_baud_valid(int value)
{
    int E[] = {
        UART_BAUD_0,
        UART_BAUD_50,
        UART_BAUD_75,
        UART_BAUD_110,
        UART_BAUD_134,
        UART_BAUD_150,
        UART_BAUD_200,
        UART_BAUD_300,
        UART_BAUD_600,
        UART_BAUD_1200,
        UART_BAUD_1800,
        UART_BAUD_2400,
        UART_BAUD_4800,
        UART_BAUD_9600,
        UART_BAUD_19200,
        UART_BAUD_38400,
        UART_BAUD_57600,
        UART_BAUD_115200,
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
    };
    
    if (enum_contains(E, sizeof(E)/sizeof(E[0]), value))
        return 1;
    
    return 0;
}

int uart_init_baud(struct _uart *uart)
{
    int ret;
    struct termios options;
    
    ret = tcgetattr(uart->fd, &options);
    
    if (ret == -1) {
        error("tcgetattr() failed", 1);
        return -1;
    }
    
    switch (uart->baud) {
    case UART_BAUD_0:
        ret = cfsetispeed(&options, B0);
        
        if (ret == -1) {
            error("cfsetispeed() failed", 1);
            return -1;
        }
        
        ret = cfsetospeed(&options, B0);
        
        if (ret == -1) {
            error("cfsetospeed() failed", 1);
            return -1;
        }

        break;
    case UART_BAUD_50:
        ret = cfsetispeed(&options, B50);
        
        if (ret == -1) {
            error("cfsetispeed() failed", 1);
            return -1;
        }
        
        ret = cfsetospeed(&options, B50);
        
        if (ret == -1) {
            error("cfsetospeed() failed", 1);
            return -1;
        }

        break;
    case UART_BAUD_75:
        ret = cfsetispeed(&options, B75);
        
        if (ret == -1) {
            error("cfsetispeed() failed", 1);
            return -1;
        }
        
        ret = cfsetospeed(&options, B75);
        
        if (ret == -1) {
            error("cfsetospeed() failed", 1);
            return -1;
        }

        break;
    case UART_BAUD_110:
        ret = cfsetispeed(&options, B110);
        
        if (ret == -1) {
            error("cfsetispeed() failed", 1);
            return -1;
        }
        
        ret = cfsetospeed(&options, B110);
        
        if (ret == -1) {
            error("cfsetospeed() failed", 1);
            return -1;
        }
        
        break;
    case UART_BAUD_134:
        ret = cfsetispeed(&options, B134);
        
        if (ret == -1) {
            error("cfsetispeed() failed", 1);
            return -1;
        }
        
        ret = cfsetospeed(&options, B134);
        
        if (ret == -1) {
            error("cfsetospeed() failed", 1);
            return -1;
        }

        break;
    case UART_BAUD_150:
        ret = cfsetispeed(&options, B150);
        
        if (ret == -1) {
            error("cfsetispeed() failed", 1);
            return -1;
        }
        
        ret = cfsetospeed(&options, B150);
        
        if (ret == -1) {
            error("cfsetospeed() failed", 1);
            return -1;
        }

        break;
    case UART_BAUD_200:
        ret = cfsetispeed(&options, B200);
        
        if (ret == -1) {
            error("cfsetispeed() failed", 1);
            return -1;
        }
        
        ret = cfsetospeed(&options, B200);
        
        if (ret == -1) {
            error("cfsetospeed() failed", 1);
            return -1;
        }

        break;
    case UART_BAUD_300:
        ret = cfsetispeed(&options, B300);
        
        if (ret == -1) {
            error("cfsetispeed() failed", 1);
            return -1;
        }
        
        ret = cfsetospeed(&options, B300);
        
        if (ret == -1) {
            error("cfsetospeed() failed", 1);
            return -1;
        }
        
        break;
    case UART_BAUD_600:
        ret = cfsetispeed(&options, B600);
        
        if (ret == -1) {
            error("cfsetispeed() failed", 1);
            return -1;
        }
        
        ret = cfsetospeed(&options, B600);
        
        if (ret == -1) {
            error("cfsetospeed() failed", 1);
            return -1;
        }
        
        break;
    case UART_BAUD_1200:
        ret = cfsetispeed(&options, B1200);
        
        if (ret == -1) {
            error("cfsetispeed() failed", 1);
            return -1;
        }
        
        ret = cfsetospeed(&options, B1200);
        
        if (ret == -1) {
            error("cfsetospeed() failed", 1);
            return -1;
        }
        
        break;
    case UART_BAUD_1800:
        ret = cfsetispeed(&options, B1800);
        
        if (ret == -1) {
            error("cfsetispeed() failed", 1);
            return -1;
        }
        
        ret = cfsetospeed(&options, B1800);
        
        if (ret == -1) {
            error("cfsetospeed() failed", 1);
            return -1;
        }

        break;
    case UART_BAUD_2400:
        ret = cfsetispeed(&options, B2400);
        
        if (ret == -1) {
            error("cfsetispeed() failed", 1);
            return -1;
        }
        
        ret = cfsetospeed(&options, B2400);
        
        if (ret == -1) {
            error("cfsetospeed() failed", 1);
            return -1;
        }
        
        break;
    case UART_BAUD_4800:
        ret = cfsetispeed(&options, B4800);
        
        if (ret == -1) {
            error("cfsetispeed() failed", 1);
            return -1;
        }
        
        ret = cfsetospeed(&options, B4800);
        
        if (ret == -1) {
            error("cfsetospeed() failed", 1);
            return -1;
        }
        
        break;
    case UART_BAUD_9600:
        ret = cfsetispeed(&options, B9600);
        
        if (ret == -1) {
            error("cfsetispeed() failed", 1);
            return -1;
        }
        
        ret = cfsetospeed(&options, B9600);
        
        if (ret == -1) {
            error("cfsetospeed() failed", 1);
            return -1;
        }
        
        break;
    case UART_BAUD_19200:
        ret = cfsetispeed(&options, B19200);
        
        if (ret == -1) {
            error("cfsetispeed() failed", 1);
            return -1;
        }
        
        ret = cfsetospeed(&options, B19200);
        
        if (ret == -1) {
            error("cfsetospeed() failed", 1);
            return -1;
        }
        
        break;
    case UART_BAUD_38400:
        ret = cfsetispeed(&options, B38400);
        
        if (ret == -1) {
            error("cfsetispeed() failed", 1);
            return -1;
        }
        
        ret = cfsetospeed(&options, B38400);
        
        if (ret == -1) {
            error("cfsetospeed() failed", 1);
            return -1;
        }
        
        break;
    case UART_BAUD_57600:
        ret = cfsetispeed(&options, B57600);
        
        if (ret == -1) {
            error("cfsetispeed() failed", 1);
            return -1;
        }
        
        ret = cfsetospeed(&options, B57600);
        
        if (ret == -1) {
            error("cfsetospeed() failed", 1);
            return -1;
        }
        
        break;
    case UART_BAUD_115200:
        ret = cfsetispeed(&options, B115200);
        
        if (ret == -1) {
            error("cfsetispeed() failed", 1);
            return -1;
        }
        
        ret = cfsetospeed(&options, B115200);
        
        if (ret == -1) {
            error("cfsetospeed() failed", 1);
            return -1;
        }
        
        break;
    case UART_BAUD_230400:
        ret = cfsetispeed(&options, B230400);
        
        if (ret == -1) {
            error("cfsetispeed() failed", 1);
            return -1;
        }
        
        ret = cfsetospeed(&options, B230400);
        
        if (ret == -1) {
            error("cfsetospeed() failed", 1);
            return -1;
        }

        break;
    case UART_BAUD_460800:
        ret = cfsetispeed(&options, B460800);
        
        if (ret == -1) {
            error("cfsetispeed() failed", 1);
            return -1;
        }
        
        ret = cfsetospeed(&options, B460800);
        
        if (ret == -1) {
            error("cfsetospeed() failed", 1);
            return -1;
        }

        break;
    case UART_BAUD_500000:
        ret = cfsetispeed(&options, B500000);
        
        if (ret == -1) {
            error("cfsetispeed() failed", 1);
            return -1;
        }
        
        ret = cfsetospeed(&options, B500000);
        
        if (ret == -1) {
            error("cfsetospeed() failed", 1);
            return -1;
        }

        break;
    case UART_BAUD_576000:
        ret = cfsetispeed(&options, B576000);
        
        if (ret == -1) {
            error("cfsetispeed() failed", 1);
            return -1;
        }
        
        ret = cfsetospeed(&options, B576000);
        
        if (ret == -1) {
            error("cfsetospeed() failed", 1);
            return -1;
        }

        break;
    case UART_BAUD_921600:
        ret = cfsetispeed(&options, B921600);
        
        if (ret == -1) {
            error("cfsetispeed() failed", 1);
            return -1;
        }
        
        ret = cfsetospeed(&options, B921600);
        
        if (ret == -1) {
            error("cfsetospeed() failed", 1);
            return -1;
        }

        break;
    case UART_BAUD_1000000:
        ret = cfsetispeed(&options, B1000000);
        
        if (ret == -1) {
            error("cfsetispeed() failed", 1);
            return -1;
        }
        
        ret = cfsetospeed(&options, B1000000);
        
        if (ret == -1) {
            error("cfsetospeed() failed", 1);
            return -1;
        }

        break;
    case UART_BAUD_1152000:
        ret = cfsetispeed(&options, B1152000);
        
        if (ret == -1) {
            error("cfsetispeed() failed", 1);
            return -1;
        }
        
        ret = cfsetospeed(&options, B1152000);
        
        if (ret == -1) {
            error("cfsetospeed() failed", 1);
            return -1;
        }

        break;
    case UART_BAUD_1500000:
        ret = cfsetispeed(&options, B1500000);
        
        if (ret == -1) {
            error("cfsetispeed() failed", 1);
            return -1;
        }
        
        ret = cfsetospeed(&options, B1500000);
        
        if (ret == -1) {
            error("cfsetospeed() failed", 1);
            return -1;
        }

        break;
    case UART_BAUD_2000000:
        ret = cfsetispeed(&options, B2000000);
        
        if (ret == -1) {
            error("cfsetispeed() failed", 1);
            return -1;
        }
        
        ret = cfsetospeed(&options, B2000000);
        
        if (ret == -1) {
            error("cfsetospeed() failed", 1);
            return -1;
        }

        break;
    case UART_BAUD_2500000:
        ret = cfsetispeed(&options, B2500000);
        
        if (ret == -1) {
            error("cfsetispeed() failed", 1);
            return -1;
        }
        
        ret = cfsetospeed(&options, B2500000);
        
        if (ret == -1) {
            error("cfsetospeed() failed", 1);
            return -1;
        }

        break;
    case UART_BAUD_3000000:
        ret = cfsetispeed(&options, B3000000);
        
        if (ret == -1) {
            error("cfsetispeed() failed", 1);
            return -1;
        }
        
        ret = cfsetospeed(&options, B3000000);
        
        if (ret == -1) {
            error("cfsetospeed() failed", 1);
            return -1;
        }

        break;
    case UART_BAUD_3500000:
        ret = cfsetispeed(&options, B3500000);
        
        if (ret == -1) {
            error("cfsetispeed() failed", 1);
            return -1;
        }
        
        ret = cfsetospeed(&options, B3500000);
        
        if (ret == -1) {
            error("cfsetospeed() failed", 1);
            return -1;
        }

        break;
    case UART_BAUD_4000000:
        ret = cfsetispeed(&options, B4000000);
        
        if (ret == -1) {
            error("cfsetispeed() failed", 1);
            return -1;
        }
        
        ret = cfsetospeed(&options, B4000000);
        
        if (ret == -1) {
            error("cfsetospeed() failed", 1);
            return -1;
        }

        break;
    default:
        error("invalid Baud Rate", 0);
        return -1;
    }
    
    ret = tcsetattr(uart->fd, TCSANOW, &options);
    
    if (ret == -1) {
            error("tcsetattr() failed", 1);
            return -1;
    }
    
    return 0;
}

int uart_init_databits(struct _uart *uart)
{
    int ret;
    struct termios options;
    
    ret = tcgetattr(uart->fd, &options);
    
    if (ret == -1) {
        error("tcgetattr() failed", 1);
        return -1;
    }
    
    switch (uart->data_bits) {
    case 5:
        options.c_cflag &= ~CSIZE;
        options.c_cflag |= CS5;
        break;
    case 6:
        options.c_cflag &= ~CSIZE;
        options.c_cflag |= CS6;
        break;
    case 7:
        options.c_cflag &= ~CSIZE;
        options.c_cflag |= CS7;
        break;
    case 8:
        options.c_cflag &= ~CSIZE;
        options.c_cflag |= CS8;
        break;
    default:
        error("invalid Data Bits", 0);
        return -1;
    }
    
    ret = tcsetattr(uart->fd, TCSANOW, &options);
    
    if (ret == -1) {
        error("tcsetattr() failed", 1);
        return -1;
    }
    
    return 0;
}

int uart_init_parity(struct _uart *uart)
{
    int ret;
    struct termios options;
    
    ret = tcgetattr(uart->fd, &options);
    
    if (ret == -1) {
        error("tcgetattr() failed", 1);
        return -1;
    }
    
    switch (uart->parity) {
    case UART_PARITY_NO:
        options.c_cflag &= ~PARENB;
        break;
    case UART_PARITY_ODD:
        options.c_cflag |= PARENB;
        options.c_cflag |= PARODD;
        break;
    case UART_PARITY_EVEN:
        options.c_cflag |= PARENB;
        options.c_cflag &= ~PARODD;
        break;
    default:
        error("invalid Parity", 0);
        return -1;
    }
    
    ret = tcsetattr(uart->fd, TCSANOW, &options);
    
    if (ret == -1) {
        error("tcsetattr() failed", 1);
        return -1;
    }
    
    return 0;
}

int uart_init_stopbits(struct _uart *uart)
{
    int ret;
    struct termios options;
    
    ret = tcgetattr(uart->fd, &options);
    
    if (ret == -1) {
        error("tcgetattr() failed", 1);
        return -1;
    }
    
    switch (uart->stop_bits) {
    case 1:
        options.c_cflag &= ~CSTOPB;
        break;
    case 2:
        options.c_cflag |= CSTOPB;
        break;
    default:
        error("invalid Stop Bits", 0);
        return -1;
    }
    
    ret = tcsetattr(uart->fd, TCSANOW, &options);
    
    if (ret == -1) {
        error("tcsetattr() failed", 1);
        return -1;
    }
    
    return 0;
}

int uart_init_flow(struct _uart *uart)
{
    int ret;
    struct termios options;
    
    ret = tcgetattr(uart->fd, &options);
    
    if (ret == -1) {
        error("tcgetattr() failed", 1);
        return -1;
    }
    
    switch (uart->flow_ctrl) {
    case UART_FLOW_NO:
        options.c_cflag &= ~CRTSCTS;
        options.c_iflag &= ~(IXON | IXOFF | IXANY);
        break;
    case UART_FLOW_SOFTWARE:
        options.c_cflag &= ~CRTSCTS;
        options.c_iflag |= (IXON | IXOFF | IXANY);
        break;
    case UART_FLOW_HARDWARE:
        options.c_cflag |= CRTSCTS;
        options.c_iflag &= ~(IXON | IXOFF | IXANY);
        break;
    default:
        error("invalid Flow control", 0);
        return -1;
    }
    
    ret = tcsetattr(uart->fd, TCSANOW, &options);
    
    if (ret == -1) {
        error("tcsetattr() failed", 1);
        return -1;
    }
    
    return 0;
}

int uart_init(struct _uart *uart)
{
    int ret;
    struct termios options;
    
    /* set non-blocking mode */
    ret = fcntl(uart->fd, F_SETFL, FNDELAY);
    
    if (ret == -1) {
        error("fcntl() failed", 1);
        return -1;
    }
    
    /* set baud rate */
    ret = uart_init_baud(uart);
    
    if (ret == -1)
        return -1;
    
    /* set data bits */
    ret = uart_init_databits(uart);
    
    if (ret == -1)
        return -1;
    
    /* set parity */
    ret = uart_init_parity(uart);
    
    if (ret == -1)
        return -1;
    
    /* set stop bits */
    ret = uart_init_stopbits(uart);
    
    if (ret == -1)
        return -1;
    
    /* set flow control */
    ret = uart_init_flow(uart);
    
    if (ret == -1)
        return -1;
    
    ret = tcgetattr(uart->fd, &options);
    
    if (ret == -1) {
        error("tcgetattr() failed", 1);
        return -1;
    }
    
    /* set raw input mode */
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    
    /* enable receiver and set local mode */
    options.c_cflag |= (CLOCAL | CREAD);
    ret = tcsetattr(uart->fd, TCSANOW, &options);
    
    if (ret == -1) {
        error("tcsetattr() failed", 1);
        return -1;
    }
    
    return 0;
}

struct _uart *uart_open(const char *dev, int baud, const char *opt)
{
    int ret;
    int fd;
    struct _uart *p;
    
    p = (struct _uart *) malloc(sizeof(struct _uart));
    
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
    fd = open(p->dev, O_RDWR | O_NOCTTY | O_NDELAY);
    
    if (fd == -1) {
        error("open() failed", 1);
        free(p);
        return NULL;
    }
    
    p->fd = fd;
    ret = parse_option(p, opt);
    
    if (ret == -1)
        return NULL;
    
    if (!uart_baud_valid(baud)) {
        error("invalid Baud Rate", 0);
        close(fd);
        free(p);
        return NULL;
    }
    
    p->baud = baud;
    ret = uart_init(p);
    
    if (ret == -1) {
        close(fd);
        free(p);
        return NULL;
    }
    
    return p;
}

void uart_close(struct _uart *uart)
{
    close(uart->fd);
    free(uart);
    uart = NULL;
}

int uart_send(struct _uart *uart, char *send_buf, int len)
{
    int ret;
    
    ret = write(uart->fd, send_buf, len);
    
    if (ret == -1) {
        error("write() failed", 1);
        return -1;
    }
    
    if (ret != len) {
        error("could not send all bytes", 0);
        return ret;
    }
    
    return ret;
}

int uart_recv(struct _uart *uart, char *recv_buf, int len)
{
    int ret = 0;
    
    ret = read(uart->fd, recv_buf, len);
    
    if (ret == -1) {
        error("read() failed", 1);
        return -1;
    }

    return ret;
}

int uart_set_pin(struct _uart *uart, int pin, int state)
{
    int ret;
    int status;
    
    ret = ioctl(uart->fd, TIOCMGET, &status);
    
    if (ret == -1) {
        error("ioctl() failed", 1);
        return -1;
    }
    
    switch (pin) {
    case UART_PIN_RTS:
        if (state == UART_PIN_HIGH)
            status |= TIOCM_RTS;
        else
            status &= ~TIOCM_RTS;
        break;
    case UART_PIN_DTR:
        if (state == UART_PIN_HIGH)
            status |= TIOCM_DTR;
        else
            status &= ~TIOCM_DTR;
        break;
    default:
        error("invalid pin", 0);
        return -1;
    }
    
    ioctl(uart->fd, TIOCMSET, status);
    
    if (ret == -1) {
        error("ioctl() failed", 1);
        return -1;
    }
    
    return 0;
}

int uart_get_pin(struct _uart *uart, int pin, int *state)
{
    int ret = 0;
    int status;
    
    ioctl(uart->fd, TIOCMGET, &status);
    
    if (ret == -1) {
        error("ioctl() failed", 1);
        return -1;
    }
    
    switch (pin) {
    case UART_PIN_CTS:
        if (status & TIOCM_CTS)
            ret = UART_PIN_HIGH;
        else
            ret = UART_PIN_LOW;
        break;
    case UART_PIN_DSR:
        if (status & TIOCM_DSR)
            ret = UART_PIN_HIGH;
        else
            ret = UART_PIN_LOW;
        break;
    case UART_PIN_DCD:
        if (status & TIOCM_CAR)
            ret = UART_PIN_HIGH;
        else
            ret = UART_PIN_LOW;
        break;
    case UART_PIN_RI:
        if (status & TIOCM_RI)
            ret = UART_PIN_HIGH;
        else
            ret = UART_PIN_LOW;
        break;
    default:
        error("invalid pin", 0);
        return -1;
    }
    
    (*state) = ret;
    return 0;
}

int uart_get_bytes(struct _uart *uart, int *bytes)
{
    int ret = 0;
    
    ioctl(uart->fd, FIONREAD, &ret);
    
    if (ret == -1) {
        error("ioctl() failed", 1);
        return -1;
    }
    
    (*bytes) = ret;
    return 0;
}
