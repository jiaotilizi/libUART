/**
 *
 * File Name: unix/error.h
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

#ifndef LIBUART_UNIX_ERROR_H
#define LIBUART_UNIX_ERROR_H

extern void error_enable(int enable);
extern void error(const char *err_msg, int detail);

#endif
