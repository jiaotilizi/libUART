/**
 *
 * File Name: libUART.hpp
 * Title    : libUART class
 * Project  : libUART - libUART_cpp
 * Author   : Copyright (C) 2018-1019 Johannes Krottmayer <krjdev@gmail.com>
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

#ifndef LIBUART_LIBUART_HPP
#define LIBUART_LIBUART_HPP

class libUART {
public:
    libUART(void);
    ~libUART(void);
    int Send();
    int Recv();
    
private:
    
};

#endif
