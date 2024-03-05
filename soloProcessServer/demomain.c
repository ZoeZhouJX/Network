#include <stdio.h>

int main()
{
    /* 16进制 */
    int num = 121;
    printf("num:0X%x\n", num);

    num = 0X12345678;
    printf("num:0X%x\n", num);

    /* 8进制 */
    int num = 0121;
    printf("num:0X%x\n", num);

    return 0;
}