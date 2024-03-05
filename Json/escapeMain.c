#include <stdio.h>
#include <string.h>

int main()
{
    /* 字符串转义 */
    char * ptr = "hello\\world";

    // char * ptr = "hello\0world";

    int len = strlen(ptr);

    printf("len:%d\n", len);
    printf("ptr:%s\n", ptr);



    return 0;
}