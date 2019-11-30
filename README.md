# libUART

Easy to use library for accessing the UART (RS232) interface.

## Functions:

```c
uart_t *libUART_open(const char *dev, int baud, const char *opt);
```

Open a UART port connection.

#### Arguments:
Arg | Description
--- | -----------
*dev* | The device name of the UART port
*baud* | The baud rate of the UART port (Use the *enums* in the header file, other values are not accepted)
*opt* | The configuration string of the UART port

The configuration string must be 4 chars long. The first char represents the number of data bits (valid values are **5**, **6**, **7** or **8**), the second char represents the parity (valid values are **N** for No parity, **O** for Odd parity or **E** for Even parity), the third char represents the number of stop bits (valid values are **1** or **2**) and the fourth char represents the flow control (valid values are **N** for No flow control, **S** for Software flow control or **H** for Hardware flow control).

*Example configuration string:*  
**8N1N**

Char | Description
---- | -----------
8 | 8 data bits
N | No parity
1 | 1 stop bit
N | No flow control

#### Return:
On success, an *uart\_t* object will be returned. On error, a *NULL* pointer will be returned.

```c
void libUART_close(uart_t *uart);
```

Close the connection.

#### Arguments:
Arg | Description
--- | -----------
*uart* | The *uart_t* object

```c
int libUART_send(uart_t *uart, char *send_buf, int len);
```

Transmit data via UART.

### Arguments:
Arg | Description
--- | -----------
*uart* | The *uart_t* object
*send\_buf* | The pointer to the data to transmit
*len* | The length of the data in bytes

#### Return:
On success, the number of transmited bytes will be returned. On error, *-1* will be returned.

```c
int libUART_recv(uart_t *uart, char *recv_buf, int len);
```

Receive data from the UART port.

### Arguments:
Arg | Description
--- | -----------
*uart* | The *uart_t* object
*recv\_buf* | The pointer where the received data is stored
*len* | The length of the data in bytes

#### Return:
On success, the number of received bytes will be returned. On error, *-1* will be returned.

```c
int libUART_puts(uart_t *uart, char *msg);
```

Transmit string via UART.

### Arguments:
Arg | Description
--- | -----------
*uart* | The *uart_t* object
*msg* | The string

#### Return:
On success, the number of transmited bytes will be returned. On error, *-1* will be returned.

```c
int libUART_getc(uart_t *uart, char *c);
```

Get character from UART.

### Arguments:
Arg | Description
--- | -----------
*uart* | The *uart_t* object
*c* | The retruned char

#### Return:
On success, the number of transmited bytes will be returned. On error, *-1* will be returned.

```c
int libUART_set_baud(uart_t *uart, int baud);
```

Set the baud rate from the UART port.

#### Arguments:
Arg | Description
--- | -----------
*uart* | The *uart_t* object
*baud* | The baud rate (Use the *enums* in the header file, other values where not accepted)

#### Return:
On success, *0* will be returned. On error, *-1* will be returned.

```c
libUART_get_baud(uart_t *uart, int *baud);
```

Get the current baud rate from the UART port.

#### Arguments:
Arg | Description
--- | -----------
*uart* | The *uart_t* object
*baud* | The returned Baud Rate


#### Return:
On success, *0* will be returned. On error, *-1* will be returned.

```c
int libUART_get_fd(uart_t *uart, int *fd);
```

Get the file descriptor from the UART port. (Linux/UNIX only) 

#### Arguments:
Arg | Description
--- | -----------
*uart* | The *uart_t* object
*fd* | The returned File descriptor

#### Return:
On success, *0* will be returned. On error, *-1* will be returned.

```c
int libUART_get_handle(uart_t *uart, HANDLE *handle);
```
Get the handle from the UART port. (Windows only)

#### Arguments:
Arg | Description
--- | -----------
*uart* | The *uart_t* object
*handle* | The returned HANDLE

#### Return:
On success, *0* will be returned. On error, *-1* will be returned.

```c
int libUART_get_dev(uart_t *uart, char **dev);
```

Get the device of the from the UART port.

#### Arguments:
Arg | Description
--- | -----------
*uart* | The *uart_t* object
*dev* | The returned poniter to the device name.

#### Return:
On success, *0* will be returned. On error, *-1* will be returned.

```c
int libUART_set_databits(uart_t *uart, int data_bits);
```

Set the data bits from the UART port.

#### Arguments:
Arg | Description
--- | -----------
*uart* | The *uart_t* object
*data\_bits* | The number of data bits (valid values are **5**, **6**, **7** ot **8**)

#### Return:
On success, *0* will be returned. On error, *-1* will be returned.

```c
int libUART_get_databits(uart_t *uart, int *data_bits);
```

Get the data bits from the uart port.

#### Arguments:
Arg | Description
--- | -----------
*uart* | The *uart_t* object
*data_bits* | The returned Data Bits

#### Return:
On success, *0* will be returned. On error, *-1* will be returned.

```c
int libUART_set_parity(uart_t *uart, int parity);
```

Set the parity from the UART port.

#### Arguments:
Arg | Description
--- | -----------
*uart* | The *uart_t* object
*parity* | The parity (valid values are **UART\_PARITY\_NO**, **UART\_PARITY\_ODD** or **UART\_PARITY\_EVEN**)

#### Return:
On success, *0* will be returned. On error, *-1* will be returned.

```c
int libUART_get_parity(uart_t *uart, int *parity);
```

Get the parity from the UART port.

#### Arguments:
Arg | Description
--- | -----------
*uart* | The *uart_t* object
*uart* | The returned Parity

#### Return:
On success, *0* will be returned. On error, *-1* will be returned.

```c
int libUART_set_stopbits(uart_t *uart, int stop_bits);
```

Set the stop bits from the UART port.

#### Arguments:
Arg | Description
--- | -----------
*uart* | The *uart_t* object
*stop\_bits* | The number of stop bits (valid values are **1** or **2**)

#### Return:
On success, *0* will be returned. On error, *-1* will be returned.


```c
int libUART_get_stopbits(uart_t *uart, int *stop_bits);
```

Get the stop bits from the UART port.

#### Arguments:
Arg | Description
--- | -----------
*uart* | The *uart_t* object
*stop_bits* | The returned Stop Bits

#### Return:
On success, *0* will be returned. On error, *-1* will be returned.

```c
int libUART_set_flowctrl(uart_t *uart, int flow_ctrl);
```

Set the flow control from the UART port.


#### Arguments:
Arg | Description
--- | -----------
*uart* | The *uart_t* object
*flow\_ctrl* | The flow control (valid values are **UART\_FLOW\_NO**, **UART\_FLOW\_SOFTWARE** or **UART\_FLOW\_HARDWARE**)

#### Return:
On success, *0* will be returned. On error, *-1* will be returned.

```c
int libUART_get_flowctrl(uart_t *uart, int *flow_ctrl);
```

Get the flow control from the UART port.

#### Arguments:
Arg | Description
--- | -----------
*uart* | The *uart_t* object
*flow_ctrl* | The returned Flow Control

#### Return:
On success, *0* will be returned. On error, *-1* will be returned.

```c
int libUART_set_pin(uart_t *uart, int pin, int state);
```

Set the state of a specific pin from the UART port.

#### Arguments:
Arg | Description
--- | -----------
*uart* | The *uart_t* object
*pin* | The control pin of the UART
*state* | The state of the pin to set (valid values are **0** or **1**)

##### Pins:
Pin | Description
--- | -----------
UART\_PIN\_RTS | Request to Send
UART\_PIN\_CTS | Clear to Send
UART\_PIN\_DSR | Data Set Ready
UART\_PIN\_DCD | Data Carrier Detect
UART\_PIN\_DTR | Data Terminal Ready
UART\_PIN\_RI | Ring Indicator

#### Return:
On success, *0* will be returned. On error, *-1* will be returned.

```c
int libUART_get_pin(uart_t *uart, int pin, int *state);
```

Get the state of a specific pin from the UART port.

#### Arguments:
Arg | Description
--- | -----------
*uart* | The *uart_t* object
*pin* | The control pin of the UART
*state* | The returned State of the pin

#### Return:
On success, *0* will be returned. On error, *-1* will be returned.

```c
int libUART_get_bytes_available(uart_t *uart, int *num);
```

Get the current available bytes in the receive buffer.

#### Arguments:
Arg | Description
--- | -----------
*uart* | The *uart_t* object
*num* | The returned available bytes

### Return:
On success, *0* will be returned. On error, *-1* will be returned.

```c
void libUART_set_error(int enable);
```
Enable or disable error message output.

```c
char *libUART_get_libname(void);
```

Get the library name.

```c
char *libUART_get_libversion(void);
```

Get the library version.

```c
char *libUART_get_libname(void);
```

Get the library copyright.

# LICENSE
> Copyright (c) 2018-2019 [Johannes Krottmayer](mailto:krjdev@gmail.com)  
>  
> Permission to use, copy, modify, and/or distribute this software for any  
> purpose with or without fee is hereby granted, provided that the above  
> copyright notice and this permission notice appear in all copies.  
>  
> THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES  
> WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF  
> MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR  
> ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES  
> WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN  
> ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF  
> OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
