#include <stdio.h>
#include <libUART.h>

int main(int argc, char* argv[])
{
    printf("%s\r\n", libUART_get_libname());
    return 0;
}