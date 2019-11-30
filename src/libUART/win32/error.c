/**
 *
 * File Name: win32/error.c
 * Title    : WIN32 Error handling
 * Project  : libUART
 * Author   : Copyright (C) 2018-2019 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2019-11-19
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

#include <Windows.h>

#include "../version.h"

static int g_enable = 1;

void error_enable(int enable)
{
    g_enable = enable;
}

void error(const char *err_msg, int detail)
{
    DWORD dwError;
    LPVOID lpvError;
    
    if (!g_enable)
        return;
    
    fprintf(stderr, "[%s] error: ", LIBUART_NAME);
    
    if (detail) {
        dwError = GetLastError();
        FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | 
                      FORMAT_MESSAGE_ALLOCATE_BUFFER | 
                      FORMAT_MESSAGE_IGNORE_INSERTS, 
                      NULL, 
                      dwError, 
                      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
                      (LPTSTR) &lpvError, 
                      0, 
                      NULL);
        fprintf(stderr, "%s (%s)\r\n", err_msg, (char *) lpvError);
        LocalFree(lpvError);
    } else
        fprintf(stderr, "%s\r\n", err_msg);
}
