# libuart

Easy to use library for accessing the UART (RS232) interface.


## Functions:

### uart\_t *uart\_open(const char *dev, int baud, const char *opt)

Open a UART port.

#### Arguments
*dev*   The device name of the UART port
*baud*  The baud rate of the UART port. (Use the enums in the header file, other values where not accepted) 
*opt*   The configuration string of the UART port.

The configuration string must be 4 chars long. The first char represents the number of data bits (valid values are 5, 6, 7 or 8). The second char represents the parity (valid values are N for No, O for Odd or E for Even). The third char represents the number of stop bits (valid values are 1 or 2). The fourth char represents the flow control (valid values are N for No, S for Software or H for Hardware).

*Example configuration string:*
8N1N

8 -> Use 8 data bits
N -> No parity
1 -> Use 1 stop bit
N -> No flow control

#### Return:
If success an *uart\_t* object will be returned. On error, a NULL pointer
will be returned.

### void uart\_close(uart\_t *uart)

Close the connection.

### int uart_send(uart_t *uart, char *send_buf, int len)

Transmit data via UART.

### int uart_recv(uart_t *uart, char *recv_buf, int len)

Receive data from the UART port.

### void uart_baud_set(uart_t *uart, int baud)

Set the baud rate from the UART port.

### int uart_baud_get(uart_t *uart)

Get the current baud rate from the UART port.

### int uart_fd_get(uart_t *uart)

Get the file descriptor from the UART port.

### char *uart_dev_get(uart_t *uart)

Get the device of the from the UART port.

### void uart_databits_set(uart_t *uart, int data_bits)

Set the data bits from the UART port.

### int uart_databits_get(uart_t *uart)

Get the data bits from the uart port.

### void uart_parity_set(uart_t *uart, int parity)

Set the parity from the UART port.

### int uart_parity_get(uart_t *uart)

Get the parity from the UART port.

### void uart_stopbits_set(uart_t *uart, int stop_bits)

Set the stop bits from the UART port.

### int uart_stopbits_get(uart_t *uart)

Get the stop bits from the UART port.

### void uart_flow_set(uart_t *uart, int flow_ctrl)

Set the flow control from the UART port.

### int uart_flow_get(uart_t *uart)

Get the flow control from the UART port.

### void uart_pin_set(uart_t *uart, int pin, int state)

Set the state of a specific pin from the UART port.

### int uart_pin_get(uart_t *uart, int pin)

Get the state of a specific pin from the UART port.

### int uart_bytes_get(uart_t *uart);

Get the current available bytes in the receive buffer.
