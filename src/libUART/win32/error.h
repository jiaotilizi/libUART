/**
 *
 * File Name: win32/error.h
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

#ifndef LIBUART_WIN32_ERROR_H
#define LIBUART_WIN32_ERROR_H

extern void error_enable(int enable);
extern void error(const char *err_msg, int detail);

#endif
