/**
 *
 * File Name: util.c
 * Title    : libUART Utilities
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

int enum_contains(int enum_values[], int len, int value)
{
    int i;
    
    for (i = 0; i < len; i++)
        if (enum_values[i] == value)
            return 1;
    
    return 0;
}
