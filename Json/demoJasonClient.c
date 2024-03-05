#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <json-c/json.h>

int main(void)
{
    // 第一步：创建socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("socket");
        exit(1);
    }

    // 第二步：发起连接
    struct sockaddr_in server_info; // 保存服务器的信息
    bzero(&server_info, sizeof(server_info));
    server_info.sin_family = AF_INET;
    server_info.sin_port = 7000;
    server_info.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sockfd, (struct sockaddr *)&server_info, sizeof(server_info)) == -1)
    {
        perror("connect");
        exit(2);
    }

    // 第三步：读写数据
    struct json_object *json = json_object_new_object();
    json_object_object_add(json, "name", json_object_new_string("xiaoming"));
    json_object_object_add(json, "age", json_object_new_int(20));

    const char *buf = json_object_to_json_string(json);

    if (send(sockfd, buf, strlen(buf), 0) == -1)
    {
        perror("send");
        exit(3);
    }

    printf("字符串 %s 发送成功 长度 %ld \n", buf, strlen(buf));

    close(sockfd);

    return 0;
}