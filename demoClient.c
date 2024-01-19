#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <error.h>

#define SERVER_PORT 8888
#define SERVER_IP   "172.28.106.66"
#define BUFFER_SIZE 128

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("socket error");
        exit(-1);
    }

    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    /* 端口 */
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(SERVER_PORT);
    /* IP地址 */
    int ret = inet_pton(AF_INET, SERVER_IP, (void *)&(serverAddress.sin_addr.s_addr));
    if (ret != 1)
    {
        perror("inet_pton error");
        exit(-1);
    }

    /* ip地址 */
    ret = connect(sockfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    if (ret == -1)
    {
        perror("connect error");
        exit(-1);
    }

    /* 缓存区 */
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));

    char receiveBuffer[BUFFER_SIZE];
    memset(receiveBuffer, 0, sizeof(receiveBuffer));

    while (1)
    {
        strncpy(buffer, "加油 254", sizeof(buffer) - 1);

        write(sockfd, buffer, sizeof(buffer));

        read(sockfd, receiveBuffer, sizeof(receiveBuffer) - 1);
        printf("receive:%s\n", receiveBuffer);
    }

    /* 休息5s */
    sleep(5);

    close(sockfd);

    return 0;
}