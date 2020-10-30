/**
 *
 * File Name: libUART.h
 * Title    : libUART Demo Application
 * Project  : libUART - libUART_demo
 * Author   : Copyright (C) 2018-1019 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2019-11-30
 * Modified : 
 * Revised  : 
 * Version  : 0.2.0.0
 * License  : ISC (see file LICENSE.txt)
 *
 * NOTE: This code is currently below version 1.0, and therefore is considered
 * to be lacking in some functionality or documentation, or may not be fully
 * tested. Nonetheless, you can expect most functions to work.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef __unix__
#include <unistd.h>
#define UART_DEV    "/dev/ttyUSB0"
#elif _WIN32
#include <Windows.h>
#define UART_DEV    "\\\\.\\COM66"
#endif

#include <libUART.h>


void HAL_SleepS(unsigned int time_s)
{
#ifdef __unix__
	sleep(time_s);
#elif _WIN32
	Sleep(time_s * 1000);
#endif
}

void HAL_SleepMS(unsigned int time_ms)
{
#ifdef __unix__
	usleep(time_ms * 1000);
#elif _WIN32
	Sleep(time_ms);
#endif
}

DWORD WINAPI ThreadFun(LPVOID pM)  
{  
    printf("我是子线程， pid = %d\n", GetCurrentThreadId());
    uart_t *uart = (uart_t *)pM;
    char c = '\0';
    int ret = 0;

    while (1) {
        ret = libUART_getc(uart, &c);
        if (1 == ret) {
            printf("%c", c);
        }
    }
    
    return 0;  
}

bool send_cmd_wait_reply(uart_t *uart, char *cmd_str, char *ok_str, char *err_str, long timeout_ms)
{
	bool result = false;
    bool matched_ok = false;
    bool matched_err = false;
	int send_len = 0;
	char buffer[512] = {'\0',};
    

	if (0 > (send_len = libUART_puts(uart, cmd_str))) {
		//printf("###### Send CMD [%s] error \r\n", cmd_str);
	} else {
		//printf("###### Send CMD [%s] success \r\n", cmd_str);
        //libUART_flush(uart);
	}

	//while (0 < timeout_ms) {
		//libUART_recv(uart, buffer, sizeof(buffer));
		//if (NULL != strstr(buffer, ok_str)) {
		//	printf("###### Recieve [%s] \r\n", ok_str);
		//	result = true;
		//	break;
		//} else if (NULL != strstr(buffer, err_str)) {
		//	printf("###### Recieve [%s] \r\n", err_str);
		//	result = false;
		//	break;
		//}
		//libUART_getc(uart, &c);
        //printf("###### Recieve [%c] \r\n", c);
		//timeout_ms--;
		//HAL_SleepMS(1);
	//}
#if 1
    char c;
    int ret = 0;
	int len_ok_str = strlen(ok_str);
    int len_err_str = strlen(err_str);
    int i = 0;
    int j = 0;

	while (0 < timeout_ms) {        //若需要延时生效，ReadFile为非阻塞，则需要调用SetCommTimeouts使ReadIntervalTimeout为MAXDWORD，会影响性能
	    ret = libUART_getc(uart, &c);
        //printf("%c", c);
        if (1 == ret) {
            if (i < len_ok_str && c == ok_str[i]) {
                i++;
                if (i == len_ok_str) {
                    result = true;
                    break;
                } else {
                    matched_ok = true;
                }
            } else {
                matched_ok = false;
                i = 0;
            }
            
            if (j < len_err_str && c == err_str[j]) {
                j++;
                if (j == len_err_str) {
                    result = false;
                    break;
                } else {
                    matched_err = true;
                }
            } else {
                matched_err = false;
                j = 0;
            }

            if (true == matched_ok || true == matched_err) {
                continue;
            }
        }else {
            timeout_ms--;
            HAL_SleepMS(1);
        }
    }
#endif
	return result;
}




int main1(int argc, char* argv[])
{
    uart_t *uart;
    char* buf;
    int bytes;
    
    printf("%s %s\r\n", libUART_get_libname(), libUART_get_libversion());
    uart = libUART_open(UART_DEV, UART_BAUD_115200, "8N1N");
    
    if (!uart)
        return -1;
    
    //printf("TX: %d byte(s)\n", libUART_puts(uart, "AT+TCDEVINFOSET=1,\"LN19CSVR64\",\"door1\",\"oql3IfVOGFqT09iKVqLBaQ==\"\r\n"));
	printf("TX: %d byte(s)\n", libUART_puts(uart, "AT+TCMQTTCONN=1,5000,240,1,0\r\n"));
    
	HAL_SleepS(1);
	
    libUART_get_bytes_available(uart, &bytes);
    printf("RX: %d byte(s) available\n", bytes);
    buf = (char *) malloc(bytes + 1);
    libUART_recv(uart, buf, bytes);
    buf[bytes] = '\0';
    printf("RX: %s\n", buf);
    free(buf);
    libUART_close(uart);

	system("pause");
    return 0;
}

char g_str_10[11] = "012345678\n";
char g_str_1024[1025] = "012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012\n";
char g_str_3072[3073] = "01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901230123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012\n";

void network_connect(uart_t *uart)
{
    send_cmd_wait_reply(uart, "AT+CGATT=1\r\n", "OK", "+CME ERROR", 200);
	send_cmd_wait_reply(uart, "AT+CGDCONT=1,\"IP\",\"cmnet\"\r\n", "OK", "+CME ERROR", 200);
	send_cmd_wait_reply(uart, "AT+CGACT=1,1\r\n", "OK", "+CME ERROR", 200);
}

void network_disconnect(uart_t *uart)
{
	send_cmd_wait_reply(uart, "AT+CGACT=0,1\r\n", "OK", "+CME ERROR", 200);
}


void test_case_ftp_put(uart_t *uart)
{
    SYSTEMTIME time;
    char dateTimeStr[200] = {'\0',};
    
    send_cmd_wait_reply(uart, "AT^FTPOPEN=\"120.79.94.27:49999\",\"cmiotftp\",\"123\",1,180,0\r\n", "OK", "+CME ERROR", 200);
    send_cmd_wait_reply(uart, "AT^FTPOPEN?\r\n", "^FTPOPEN:1", "^FTPOPEN:0", 200);
    
    send_cmd_wait_reply(uart, "AT^FTPPUTSET=\"/testuart.bin\"\r\n", "OK", "+CME ERROR", 200);
    send_cmd_wait_reply(uart, "AT^FTPPUT=1\r\n", "^FTPPUT:1,3072", "+CME ERROR", 200);
    
    GetLocalTime(&time);
    snprintf(dateTimeStr, sizeof(dateTimeStr), "%d-%02d-%02d %02d:%02d:%02d.%03d\t", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
    printf("\r\nftp put data start --------- %s\r\n", dateTimeStr);

    char *str_tmp = NULL;
    str_tmp = g_str_1024;
    char cmd_tmp[64] = {'\0',};
    snprintf(cmd_tmp, sizeof(cmd_tmp), "AT^FTPPUT=2,%d\r\n", strlen(str_tmp));
    
    for (int i = 0; i < 500; i++) {
        send_cmd_wait_reply(uart, cmd_tmp, ">", "+CME ERROR", 200);
        send_cmd_wait_reply(uart, str_tmp, "OK", "+CME ERROR", 200);
    }

    GetLocalTime(&time);
    snprintf(dateTimeStr, sizeof(dateTimeStr), "%d-%02d-%02d %02d:%02d:%02d.%03d\t", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
    printf("\r\nftp put data end --------- %s\r\n", dateTimeStr);

    send_cmd_wait_reply(uart, "AT^FTPPUT=2,0\r\n", "^FTPPUT:2,0", "+CME ERROR", 200);

    send_cmd_wait_reply(uart, "AT^FTPCLOSE\r\n", "^URCFTP:0", "+CME ERROR", 200);
}

void test_case_ftp_get(uart_t *uart)
{
    SYSTEMTIME time;
    char dateTimeStr[200] = {'\0',};
    
    send_cmd_wait_reply(uart, "AT^FTPOPEN=\"120.79.94.27:49999\",\"cmiotftp\",\"123\",1,180,0\r\n", "OK", "+CME ERROR", 200);
    send_cmd_wait_reply(uart, "AT^FTPOPEN?\r\n", "^FTPOPEN:1", "^FTPOPEN:0", 200);
    
    GetLocalTime(&time);
    snprintf(dateTimeStr, sizeof(dateTimeStr), "%d-%02d-%02d %02d:%02d:%02d.%03d\t", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
    printf("\r\nftp get data start --------- %s\r\n", dateTimeStr);

    char cmd_tmp[64] = {'\0',};
    
    for (int i = 0; i < 1; i++) {
        snprintf(cmd_tmp, sizeof(cmd_tmp), "AT^FTPGETSET=\"/testuart.bin\",%d,%d\r\n", 1024 * i, 1024);
        send_cmd_wait_reply(uart, cmd_tmp, "OK", "+CME ERROR", 200);
    
        GetLocalTime(&time);
        snprintf(dateTimeStr, sizeof(dateTimeStr), "%d-%02d-%02d %02d:%02d:%02d.%03d\t", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
        printf("\r\nAT^FTPGETSET end --------- %s\r\n", dateTimeStr);
        
        send_cmd_wait_reply(uart, "AT^FTPGET=1\r\n", "^FTPGET:2,0", "+CME ERROR", 200);

        
        GetLocalTime(&time);
        snprintf(dateTimeStr, sizeof(dateTimeStr), "%d-%02d-%02d %02d:%02d:%02d.%03d\t", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
        printf("\r\nAT^FTPGET=1 end --------- %s\r\n", dateTimeStr);
    }

    GetLocalTime(&time);
    snprintf(dateTimeStr, sizeof(dateTimeStr), "%d-%02d-%02d %02d:%02d:%02d.%03d\t", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
    printf("\r\nftp get data end --------- %s\r\n", dateTimeStr);

    send_cmd_wait_reply(uart, "AT^FTPCLOSE\r\n", "^URCFTP:0", "+CME ERROR", 200);
}


void test_case_tencent_iot(uart_t *uart)
{
    send_cmd_wait_reply(uart, "AT+TCDEVINFOSET=1,\"LN19CSVR64\",\"door1\",\"oql3IfVOGFqT09iKVqLBaQ==\"\r\n", "+TCDEVINFOSET:OK", "+TCDEVINFOSET:FAIL", 200);
	send_cmd_wait_reply(uart, "AT+TCMQTTCONN=1,5000,240,1,0\r\n", "+TCMQTTCONN:OK", "+TCMQTTCONN:FAIL", 1000);
	send_cmd_wait_reply(uart, "AT+TCMQTTDISCONN\r\n", "OK", "+CME ERROR", 1000);
}


int main(int argc, char* argv[])
{
    uart_t *uart;
    
    printf("%s %s\r\n", libUART_get_libname(), libUART_get_libversion());
    uart = libUART_open(UART_DEV, UART_BAUD_921600, "8N1N");
    
    if (!uart)
        return -1;

    //printf("我是主线程， pid = %d\n", GetCurrentThreadId());
    //HANDLE handle = CreateThread(NULL, 0, ThreadFun, uart, 0, NULL);
    
    send_cmd_wait_reply(uart, "ATE0\r\n", "OK", "+CME ERROR", 200);

    test_case_ftp_put(uart);

    send_cmd_wait_reply(uart, "ATE1\r\n", "OK", "+CME ERROR", 200);
	
    libUART_close(uart);

	system("pause");
    return 0;
}

