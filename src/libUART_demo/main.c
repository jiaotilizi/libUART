/**
 *
 * File Name: libUART.h
 * Title    : libUART Demo Application
 * Project  : libUART - libUART_demo
 * Author   : Copyright (C) 2018-1019 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2019-11-30
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

#ifdef __unix__
#include <unistd.h>

#define UART_DEV    "/dev/ttyUSB0"
#elif _WIN32
#include <Windows.h>

#define UART_DEV    "\\\\.\\COM3"
#endif
#include <libUART.h>

int main(int argc, char* argv[])
{
    uart_t *uart;
    char* buf;
    int bytes;
    
    printf("%s %s\r\n", libUART_get_libname(), libUART_get_libversion());
    uart = libUART_open(UART_DEV, UART_BAUD_9600, "8N1N");
    
    if (!uart)
        return -1;
    
    printf("TX: %d byte(s)\n", libUART_puts(uart, "Hello World!"));
    Sleep(1000);
    libUART_get_bytes_available(uart, &bytes);
    printf("RX: %d byte(s) available\n", bytes);
    buf = (char *) malloc(bytes + 1);
    libUART_recv(uart, buf, bytes);
    buf[bytes] = '\0';
    printf("RX: %s\n", buf);
    free(buf);
    libUART_close(uart);
    return 0;
}
