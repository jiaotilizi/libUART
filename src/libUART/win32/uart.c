/**
 *
 * File Name: win32/uart.c
 * Title    : WIN32 UART
 * Project  : libUART
 * Author   : Copyright (C) 2018-2019 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2019-11-20
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
#include <Windows.h>

#include "uart.h"
#include "error.h"

static int init_baud(uart_t *uart)
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
        error("Invalid Baud Rate", 0);
        return -1;
    }
    
    ret = SetCommState(uart->h, &dcb);
    
    if (!ret) {
        error("SetCommState() failed", 1);
        return -1;
    }
    
    return 0;
}

static int init_databits(uart_t *uart)
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
        error("Invalid Data Bits", 0);
        return -1;
    }
    
    ret = SetCommState(uart->h, &dcb);
    
    if (!ret) {
        error("SetCommState() failed", 1);
        return -1;
    }
    
    return 0;
}

static int init_parity(uart_t *uart)
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
        error("Invalid Parity", 0);
        return -1;
    }
    
    ret = SetCommState(uart->h, &dcb);
    
    if (!ret) {
        error("SetCommState() failed", 1);
        return -1;
    }
    
    return 0;
}

static int init_stopbits(uart_t *uart)
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
        error("Invalid Stop Bits", 0);
        return -1;
    }
    
    ret = SetCommState(uart->h, &dcb);
    
    if (!ret) {
        error("SetCommState() failed", 1);
        return -1;
    }
    
    return 0;
}

static int init_flow(uart_t *uart)
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
        error("Invalid Flow Control", 0);
        return -1;
    }
    
    ret =  SetCommState(uart->h, &dcb);
    
    if (!ret) {
        error("SetCommState() failed", 1);
        return -1;
    }
    
    return 0;
}

static int init(uart_t *uart)
{
    int ret;
    
    if (!uart) {
        printerr_uart_type_invalid();
        return -1;
    }
    
    /* set baud rate */
    ret = init_baud(uart);
    
    if (ret == -1)
        return -1;
    
    /* set data bits */
    ret = init_databits(uart);
    
    if (ret == -1)
        return -1;
    
    /* set parity */
    ret = init_parity(uart);
    
    if (ret == -1)
        return -1;
    
    /* set stop bits */
    ret = init_stopbits(uart);
    
    if (ret == -1)
        return -1;
    
    /* set flow control */
    ret = init_flow(uart);
    
    if (ret == -1)
        return -1;
    
    return 0;
}

uart_t *uart_open(const char *dev, int baud, const char *opt)
{
    int ret;
#ifdef __unix__
    int fd;
#elif _WIN32
    HANDLE h;
    DWORD dwerror;
    LPVOID lpmessage;
#endif /* __unix__ or _WIN32 */
    uart_t *p;
    
    p = malloc(sizeof(uart_t));
    
#ifdef __unix__
    if (!p) {
        printerr_alloc(strerror(errno));
        return NULL;
    }
#elif _WIN32
	if (!p) {
		dwerror = GetLastError();
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			dwerror,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR) &lpmessage,
			0,
			NULL);
		printerr_alloc((const char *) lpmessage);
		LocalFree(lpmessage);
		return NULL;
	}
#endif
    
    if (strlen(dev) >= BUFSZ) {
        printerr_uart_dev_too_long();
        return NULL;
    }
    
    strcpy(p->dev, dev);
#ifdef __unix__
    fd = open(p->dev, O_RDWR | O_NOCTTY | O_NDELAY);
    
    if (fd == -1) {
        printerr_open(strerror(errno));
        return NULL;
    }
    
    p->fd = fd;
#elif _WIN32
    h = CreateFile((LPCTSTR) dev,
                   GENERIC_READ | GENERIC_WRITE,
                   0,
                   NULL,
                   OPEN_EXISTING,
                   0,
                   NULL);
    
    if (h == INVALID_HANDLE_VALUE) {
        dwerror = GetLastError();
        FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | 
                  FORMAT_MESSAGE_IGNORE_INSERTS, 
                  NULL, 
                  dwerror, 
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
                  (LPTSTR) &lpmessage, 
                  0, 
                  NULL);
        printerr_open((const char *) lpmessage);
        LocalFree(lpmessage);
        return NULL;
    }
    
    p->h = h;
#endif /* __unix__ or _WIN32 */
    ret = parse_option(p, opt);
    
    if (ret == -1)
        return NULL;
    
    if (!is_baud_valid(baud)) {
        printerr_uart_baud_invalid();
        return NULL;
    }
    
    p->baud = baud;
    ret = init(p);
    
    if (ret == -1)
        return NULL;
    
    return p;
}

void uart_close(uart_t *uart)
{
    if (!uart) {
        printerr_uart_type_invalid();
        return;
    }
    
#ifdef __unix__
    close(uart->fd);
#elif _WIN32
    CloseHandle(uart->h);
#endif /* __unix__ or _WIN32 */
    free(uart);
    uart = NULL;
}

int uart_send(uart_t *uart, char *send_buf, int len)
{
    int ret;
#ifdef _WIN32
    DWORD dwbytestowrite = (DWORD) len;
    DWORD dwbyteswritten;
    DWORD dwerror;
    LPVOID lpmessage;
#endif /* _WIN32 */
    
    if (!uart) {
        printerr_uart_type_invalid();
        return 0;
    }
    
#ifdef __unix__
    ret = write(uart->fd, send_buf, len);
    
    if (ret == -1) {
        printerr_write(strerror(errno));
        return -1;
    }
#elif _WIN32
    ret = WriteFile(uart->h, 
                    (LPVOID) send_buf, 
                    dwbytestowrite, 
                    &dwbyteswritten, 
                    NULL);
    
    if (!ret) {
        dwerror = GetLastError();
        FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | 
                  FORMAT_MESSAGE_IGNORE_INSERTS, 
                  NULL, 
                  dwerror, 
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
                  (LPTSTR) &lpmessage, 
                  0, 
                  NULL);
        printerr_write((const char *) lpmessage);
        LocalFree(lpmessage);
        return -1;
    }
    
    ret = (int) dwbyteswritten;
#endif /* __unix__ or _WIN32 */
    
    if (ret != len) {
        printerr_write("couldn't send all bytes");
        return ret;
    }
    
    return ret;
}

int uart_recv(uart_t *uart, char *recv_buf, int len)
{
    int ret = 0;
#ifdef _WIN32
    DWORD dwbytesread = (DWORD) len;
    DWORD dwerror;
    LPVOID lpmessage;
#endif /* _WIN32 */
    
    if (!uart) {
        printerr_uart_type_invalid();
        return 0;
    }
    
#ifdef __unix__
    ret = read(uart->fd, recv_buf, len);
    
    if (ret == -1) {
        printerr_read(strerror(errno));
        return -1;
    }
#elif _WIN32
    ret = ReadFile(uart->h, 
                   (LPVOID) recv_buf, 
                   (DWORD) len, 
                   &dwbytesread, 
                   NULL);
    
    if (!ret) {
        dwerror = GetLastError();
        FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | 
                  FORMAT_MESSAGE_IGNORE_INSERTS, 
                  NULL, 
                  dwerror, 
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
                  (LPTSTR) &lpmessage, 
                  0, 
                  NULL);
        printerr_read((const char *) lpmessage);
        LocalFree(lpmessage);
        return -1;
    }
    
    ret = (int) dwbytesread;
#endif /* __unix__ or _WIN32 */
    return ret;
}

void uart_pin_set(uart_t *uart, int pin, int state)
{
    int ret;
#ifdef __unix__
    int status;
#elif _WIN32
    DWORD dwfunc;
    DWORD dwerror;
    LPVOID lpmessage;
#endif /* __unix__ or _WIN32 */
    
    if (!uart) {
        printerr_uart_type_invalid();
        return;
    }
    
#ifdef __unix__
    ret = ioctl(uart->fd, TIOCMGET, &status);
    
    if (ret == -1) {
        printerr_ioctl(strerror(errno));
        return;
    }
#endif /* __unix__ */
    
    switch (pin) {
    case UART_PIN_RTS:
        if (state == UART_PIN_HIGH)
#ifdef __unix__
            status |= TIOCM_RTS;
        else
            status &= ~TIOCM_RTS;
#elif _WIN32
            dwfunc = SETRTS;
        else
            dwfunc = CLRRTS;
#endif /* __unix__ or _WIN32 */
        break;
    case UART_PIN_DTR:
        if (state == UART_PIN_HIGH)
#ifdef __unix__
            status |= TIOCM_DTR;
        else
            status &= ~TIOCM_DTR;
#elif _WIN32
            dwfunc = SETDTR;
        else
            dwfunc = CLRDTR;
#endif /* __unix__ or _WIN32 */
        break;
    default:
        printerr_uart_pin_invalid();
    }
    
#ifdef __unix__
    ioctl(uart->fd, TIOCMSET, status);
    
    if (ret == -1) {
        printerr_ioctl(strerror(errno));
        return;
    }
#elif _WIN32
    ret = EscapeCommFunction(uart->h, dwfunc);
    
    if (!ret) {
        dwerror = GetLastError(); 
        FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | 
                  FORMAT_MESSAGE_IGNORE_INSERTS, 
                  NULL, 
                  dwerror, 
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
                  (LPTSTR) &lpmessage, 
                  0, 
                  NULL);
        printerr_uart_comm((const char *) lpmessage);
        LocalFree(lpmessage);
        return;
    }
#endif /* __unix__ or _WIN32 */
}

int uart_pin_get(uart_t *uart, int pin)
{
    int ret = 0;
#ifdef __unix__
    int status;
#elif _WIN32
    DWORD dwmstat;
    DWORD dwerror;
    LPVOID lpmessage;
#endif /* __unix__ or _WIN32 */
    
    if (!uart) {
        printerr_uart_type_invalid();
        return 0;
    }
    
#ifdef __unix__
    ioctl(uart->fd, TIOCMGET, &status);
    
    if (ret == -1) {
        printerr_ioctl(strerror(errno));
        return -1;
    }
#elif _WIN32
    ret = GetCommModemStatus(uart->h, &dwmstat);

    if (!ret) {
        dwerror = GetLastError();
        FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | 
                  FORMAT_MESSAGE_IGNORE_INSERTS, 
                  NULL, 
                  dwerror, 
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
                  (LPTSTR) &lpmessage, 
                  0, 
                  NULL);
        printerr_uart_comm((const char *) lpmessage);
        LocalFree(lpmessage);
        return -1;
    }
#endif /* __unix__ or _WIN32 */
    
    switch (pin) {
    case UART_PIN_CTS:
#ifdef __unix__
        if (status & TIOCM_CTS)
#elif _WIN32
        if (dwmstat == MS_CTS_ON)
#endif /* __unix__ or _WIN32 */
            ret = UART_PIN_HIGH;
        else
            ret = UART_PIN_LOW;
        break;
    case UART_PIN_DSR:
#ifdef __unix__
        if (status & TIOCM_DSR)
#elif _WIN32
        if (dwmstat == MS_DSR_ON)
#endif /* __unix__ or _WIN32 */
            ret = UART_PIN_HIGH;
        else
            ret = UART_PIN_LOW;
        break;
    case UART_PIN_DCD:
#ifdef __unix__
        if (status & TIOCM_CAR)
#elif _WIN32
        if (dwmstat == MS_RLSD_ON)
#endif /* __unix__ or _WIN32 */
            ret = UART_PIN_HIGH;
        else
            ret = UART_PIN_LOW;
        break;
    case UART_PIN_RI:
#ifdef __unix__
        if (status & TIOCM_RI)
#elif _WIN32
        if (dwmstat == MS_RING_ON)
#endif /* __unix__ or _WIN32 */
            ret = UART_PIN_HIGH;
        else
            ret = UART_PIN_LOW;
        break;
    default:
        printerr_uart_pin_invalid();
        ret = -1;
    }
    
    return ret;
}

int uart_bytes_get(uart_t *uart)
{
    int ret = 0;
#ifdef _WIN32
    COMSTAT comst;
    DWORD dwerror;
    LPVOID lpmessage;
#endif /* _WIN32 */
    
    if (!uart) {
        printerr_uart_type_invalid();
        return 0;
    }
    
#ifdef __unix__
    ioctl(uart->fd, FIONREAD, &ret);
    
    if (ret == -1) {
        printerr_ioctl(strerror(errno));
        return -1;
    }
#elif _WIN32
    ret = ClearCommError(uart->h, &dwerror, &comst);
    
    if (!ret) {
        dwerror = GetLastError();
        FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | 
                  FORMAT_MESSAGE_IGNORE_INSERTS, 
                  NULL, 
                  dwerror, 
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
                  (LPTSTR) &lpmessage, 
                  0, 
                  NULL);
        printerr_uart_comm((const char *) lpmessage);
        LocalFree(lpmessage);
        return -1;
    }
    
    ret = (int) comst.cbInQue;
#endif /* __unix__ or _WIN32 */
    
    return ret;
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

HANDLE uart_handle_get(uart_t *uart)
{
    if (!uart) {
        printerr_uart_type_invalid();
        return INVALID_HANDLE_VALUE;
    }
    
    return uart->h;
}

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
