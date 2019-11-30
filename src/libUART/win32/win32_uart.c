/**
 *
 * File Name: win32/uart.c
 * Title    : WIN32 UART
 * Project  : libUART
 * Author   : Copyright (C) 2018-2019 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2019-11-20
 * Modified : 2019-11-30
 * Revised  : 
 * Version  : 0.2.0.0
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
#include <Windows.h>

#include "../util.h"
#include "../libUART.h"

#include "error.h"
#include "uart.h"

int uart_baud_valid(int value)
{
    int E[] = {
        UART_BAUD_110,
        UART_BAUD_300,
        UART_BAUD_600,
        UART_BAUD_1200,
        UART_BAUD_2400,
        UART_BAUD_4800,
        UART_BAUD_9600,
        UART_BAUD_14400,
        UART_BAUD_19200,
        UART_BAUD_38400,
        UART_BAUD_57600,
        UART_BAUD_115200,
        UART_BAUD_128000,
        UART_BAUD_256000
    };
    
    if (enum_contains(E, sizeof(E)/sizeof(E[0]), value))
        return 1;
    
    return 0;
}

int uart_init_baud(struct _uart *uart)
{
    BOOL ret;
    DCB dcb = { 0 };
    dcb.DCBlength = sizeof(dcb);

    ret = GetCommState(uart->h, &dcb);
    
    if (!ret) {
        error("GetCommState() failed", 1);
        return -1;
    }
    
    switch (uart->baud) {
    case UART_BAUD_110:
        dcb.BaudRate = CBR_110;
        break;
    case UART_BAUD_300:
        dcb.BaudRate = CBR_300;
        break;
    case UART_BAUD_600:
        dcb.BaudRate = CBR_600;
        break;
    case UART_BAUD_1200:
        dcb.BaudRate = CBR_1200;
        break;
    case UART_BAUD_2400:
        dcb.BaudRate = CBR_2400;
        break;
    case UART_BAUD_4800:
        dcb.BaudRate = CBR_4800;
        break;
    case UART_BAUD_9600:
        dcb.BaudRate = CBR_9600;
        break;
    case UART_BAUD_19200:
        dcb.BaudRate = CBR_19200;
        break;
    case UART_BAUD_38400:
        dcb.BaudRate = CBR_38400;
        break;
    case UART_BAUD_57600:
        dcb.BaudRate = CBR_57600;
        break;
    case UART_BAUD_115200:
        dcb.BaudRate = CBR_115200;
        break;
    case UART_BAUD_128000:
        dcb.BaudRate = CBR_128000;
        break;
    case UART_BAUD_256000:
        dcb.BaudRate = CBR_256000;
        break;
    default:
        error("invalid Baud Rate", 0);
        return -1;
    }
    
    ret = SetCommState(uart->h, &dcb);
    
    if (!ret) {
        error("SetCommState() failed", 1);
        return -1;
    }
    
    return 0;
}

int uart_init_databits(struct _uart *uart)
{
    BOOL ret;
    DCB dcb = { 0 };
    dcb.DCBlength = sizeof(dcb);
    
    ret = GetCommState(uart->h, &dcb);
    
    if (!ret) {
        error("GetCommState() failed", 1);
        return -1;
    }

    switch (uart->data_bits) {
    case 5:
        dcb.ByteSize = 5;
        break;
    case 6:
        dcb.ByteSize = 6;
        break;
    case 7:
        dcb.ByteSize = 7;
        break;
    case 8:
        dcb.ByteSize = 8;
        break;
    default:
        error("invalid Data Bits", 0);
        return -1;
    }
    
    ret = SetCommState(uart->h, &dcb);
    
    if (!ret) {
        error("SetCommState() failed", 1);
        return -1;
    }
    
    return 0;
}

int uart_init_parity(struct _uart *uart)
{
    BOOL ret;
    DCB dcb = { 0 };
    dcb.DCBlength = sizeof(dcb);
    
    ret = GetCommState(uart->h, &dcb);
    
    if (!ret) {
        error("GetCommState() failed", 1);
        return -1;
    }
    
    switch (uart->parity) {
    case UART_PARITY_NO:
        dcb.Parity = NOPARITY;
        break;
    case UART_PARITY_ODD:
        dcb.Parity = ODDPARITY;
        break;
    case UART_PARITY_EVEN:
        dcb.Parity = EVENPARITY;
        break;
    default:
        error("invalid Parity", 0);
        return -1;
    }
    
    ret = SetCommState(uart->h, &dcb);
    
    if (!ret) {
        error("SetCommState() failed", 1);
        return -1;
    }
    
    return 0;
}

int uart_init_stopbits(struct _uart *uart)
{
    BOOL ret;
    DCB dcb = { 0 };
    dcb.DCBlength = sizeof(dcb);
    
    ret = GetCommState(uart->h, &dcb);
    
    if (!ret) {
        error("GetCommState() failed", 1);
        return -1;
    }
    
    switch (uart->stop_bits) {
    case 1:
        dcb.StopBits = ONESTOPBIT;
        break;
    case 2:
        dcb.StopBits = TWOSTOPBITS;
        break;
    default:
        error("invalid Stop Bits", 0);
        return -1;
    }
    
    ret = SetCommState(uart->h, &dcb);
    
    if (!ret) {
        error("SetCommState() failed", 1);
        return -1;
    }
    
    return 0;
}

int uart_init_flow(struct _uart *uart)
{
    BOOL ret;
    DCB dcb = { 0 };
    dcb.DCBlength = sizeof(dcb);
    
    ret =  GetCommState(uart->h, &dcb);
    
    if (!ret) {
        error("GetCommState() failed", 1);
        return -1;
    }
    
    switch (uart->flow_ctrl) {
    case UART_FLOW_NO:
        dcb.fOutxCtsFlow = FALSE,
        dcb.fOutxDsrFlow = FALSE,
        dcb.fDtrControl = DTR_CONTROL_DISABLE;
        dcb.fRtsControl = RTS_CONTROL_DISABLE;
        dcb.fOutX = FALSE;
        dcb.fInX = FALSE;
        break;
    case UART_FLOW_SOFTWARE:
        dcb.fOutxCtsFlow = FALSE,
        dcb.fOutxDsrFlow = FALSE,
        dcb.fDtrControl = DTR_CONTROL_DISABLE;
        dcb.fRtsControl = RTS_CONTROL_DISABLE;
        dcb.fOutX = TRUE;
        dcb.fInX = TRUE;
        break;
    case UART_FLOW_HARDWARE:
        dcb.fOutxCtsFlow = TRUE,
        dcb.fOutxDsrFlow = TRUE,
        dcb.fDtrControl = DTR_CONTROL_ENABLE;
        dcb.fRtsControl = RTS_CONTROL_ENABLE;
        dcb.fOutX = FALSE;
        dcb.fInX = FALSE;
        break;
    default:
        error("invalid Flow Control", 0);
        return -1;
    }
    
    ret =  SetCommState(uart->h, &dcb);
    
    if (!ret) {
        error("SetCommState() failed", 1);
        return -1;
    }
    
    return 0;
}

int uart_init(struct _uart *uart)
{
    int ret;
    
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
    
    return 0;
}

int uart_open(struct _uart *uart)
{
    int ret;
    HANDLE h;
    
    h = CreateFile((LPCTSTR) uart->dev,
                   GENERIC_READ | GENERIC_WRITE,
                   0,
                   NULL,
                   OPEN_EXISTING,
                   0,
                   NULL);
    
    if (h == INVALID_HANDLE_VALUE) {
        error("CreateFile() failed", 1);
        return -1;
    }
    
    uart->h = h;
    ret = uart_init(uart);
    
    if (ret == -1) {
        CloseHandle(h);
        return -1;
    }
    
    return 0;
}

void uart_close(struct _uart *uart)
{
    CloseHandle(uart->h);
    free(uart);
    uart = NULL;
}

int uart_send(struct _uart *uart, char *send_buf, int len)
{
    int ret;
    DWORD dwbytestowrite = (DWORD) len;
    DWORD dwbyteswritten;
    
    ret = WriteFile(uart->h, 
                    (LPVOID) send_buf, 
                    dwbytestowrite, 
                    &dwbyteswritten, 
                    NULL);
    
    if (!ret) {
        error("WriteFile() failed", 1);
        return -1;
    }
    
    ret = (int) dwbyteswritten;
    
    if (ret != len) {
        error("could not send all bytes", 0);
        return ret;
    }
    
    return ret;
}

int uart_recv(struct _uart *uart, char *recv_buf, int len)
{
    int ret = 0;
    DWORD dwbytesread = (DWORD) len;
    
    ret = ReadFile(uart->h, 
                   (LPVOID) recv_buf, 
                   (DWORD) len, 
                   &dwbytesread, 
                   NULL);
    
    if (!ret) {
        error("ReadFile() failed", 1);
        return -1;
    }
    
    ret = (int) dwbytesread;
    return ret;
}

int uart_set_pin(struct _uart *uart, int pin, int state)
{
    int ret;
    DWORD dwfunc;
    
    switch (pin) {
    case UART_PIN_RTS:
        if (state == UART_PIN_HIGH)
            dwfunc = SETRTS;
        else
            dwfunc = CLRRTS;
        break;
    case UART_PIN_DTR:
        if (state == UART_PIN_HIGH)
            dwfunc = SETDTR;
        else
            dwfunc = CLRDTR;
        break;
    default:
        error("invalid pin", 0);
        return -1;
    }
    
    ret = EscapeCommFunction(uart->h, dwfunc);
    
    if (!ret) {
        error("EscapeCommFunction() failed", 1);
        return -1;
    }

    return 0;
}

int uart_get_pin(struct _uart *uart, int pin, int *state)
{
    int ret = 0;
    DWORD dwmstat;

    ret = GetCommModemStatus(uart->h, &dwmstat);

    if (!ret) {
        error("GetCommModemStatus() failed", 1);
        return -1;
    }
    
    switch (pin) {
    case UART_PIN_CTS:
        if (dwmstat == MS_CTS_ON)
            ret = UART_PIN_HIGH;
        else
            ret = UART_PIN_LOW;
        break;
    case UART_PIN_DSR:
        if (dwmstat == MS_DSR_ON)
            ret = UART_PIN_HIGH;
        else
            ret = UART_PIN_LOW;
        break;
    case UART_PIN_DCD:
        if (dwmstat == MS_RLSD_ON)
            ret = UART_PIN_HIGH;
        else
            ret = UART_PIN_LOW;
        break;
    case UART_PIN_RI:
        if (dwmstat == MS_RING_ON)
            ret = UART_PIN_HIGH;
        else
            ret = UART_PIN_LOW;
        break;
    default:
        error("invalid pin", 0);
        ret = -1;
    }
    
    return ret;
}

int uart_get_bytes(struct _uart *uart, int *bytes)
{
    int ret = 0;
    COMSTAT comst;
    DWORD dwerror;
    
    ret = ClearCommError(uart->h, &dwerror, &comst);
    
    if (!ret) {
        error("ClearCommError() failed", 1);
        return -1;
    }
    
    ret = (int) comst.cbInQue;
    
    (*bytes) = ret;
    return 0;
}
