/**
 *
 * File Name: error.c
 * Title    : Generic error messages source
 * Project  : libuart
 * Author   : Copyright (C) 2018 krjdev@gmail.com
 * Created  : 2018-05-21
 * Modified : 2018-05-25
 * Revised  : 
 * Version  : 0.1.0.0
 * License  : BSD-3-Clause (see file LICENSE.txt)
 *
 * NOTE: This code is currently below version 1.0, and therefore is considered
 * to be lacking in some functionality or documentation, or may not be fully
 * tested. Nonetheless, you can expect most functions to work.
 *
 */

#include <stdio.h>

void printerr(void)
{
    fprintf(stderr, "[libuart] error: ");
}

void printerr_alloc(const char *err_msg)
{
    printerr();
    fprintf(stderr, "couldn't allocate memory (%s)\n", err_msg);
}

void printerr_realloc(const char *err_msg)
{
    printerr();
    fprintf(stderr, "couldn't reallocate memory (%s)\n", err_msg);
}

void printerr_open(const char *err_msg)
{
    printerr();
    fprintf(stderr, "couldn't open (%s)\n", err_msg);
}

void printerr_read(const char *err_msg)
{
    printerr();
    fprintf(stderr, "couldn't read (%s)\n", err_msg);
}

void printerr_write(const char *err_msg)
{
    printerr();
    fprintf(stderr, "couldn't write (%s)\n", err_msg);
}

void printerr_ioctl(const char *err_msg)
{
    printerr();
    fprintf(stderr, "ioctl failed (%s)\n", err_msg);
}

void printerr_fcntl(const char *err_msg)
{
    printerr();
    fprintf(stderr, "fcntl failed (%s)\n", err_msg);
}

void printerr_pointer_null(void)
{
    printerr();
    fprintf(stderr, "invalid pointer (NULL)\n");
}

void printerr_string_null(void)
{
    printerr();
    fprintf(stderr, "invalid string (NULL)\n");
}
