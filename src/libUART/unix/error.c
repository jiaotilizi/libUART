/**
 *
 * File Name: unix/error.c
 * Title    : libUART UNIX Error handling
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
#include <string.h>
#include <errno.h>

#include "../version.h"

static int g_enable = 1;

void error_enable(int enable)
{
    g_enable = enable;
}

void error(const char *err_msg, int detail)
{
    if (!g_enable)
        return;
    
    fprintf(stderr, "[%s] error: ", LIBUART_NAME);
    
    if (detail)
        fprintf(stderr, "%s (%s)\r\n", err_msg, strerror(errno));
    else
        fprintf(stderr, "%s\r\n", err_msg);
}
