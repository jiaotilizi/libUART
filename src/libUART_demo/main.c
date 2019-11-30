#include <stdio.h>

#include <libUART.h>

int main(int argc, char* argv[])
{
    printf("%s %s\r\n", libUART_get_libname(), libUART_get_libversion());
    return 0;
}
