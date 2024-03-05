#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <json-c/json.h>

int main(void)
{
    // 第一步：创建socket
    //  socket()：地址族：IPV4协议  套接字类型：流式套接字
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("socket");
        exit(1);
    }

    // 第二步：绑定信息
    struct sockaddr_in server_info;                  // 用于保存服务器的信息(IP PORT)
    bzero(&server_info, sizeof(struct sockaddr_in)); // 清空
    server_info.sin_family = AF_INET;                // 地址族
    server_info.sin_port = 7000;                     // 端口 大于1024都行
    // server_info.sin_addr.s_addr = 127.0.0.1; // 表示回环IP 用于测试
    server_info.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(sockfd, (struct sockaddr *)&server_info, sizeof(server_info)) == -1)
    {
        perror("bind");
        exit(2);
    }

    // 第三步：设置监听队列
    if (listen(sockfd, 10) == -1)
    {
        perror("listen");
        exit(3);
    }

    printf("等待客户端的连接 ...\n");

    // 第四步：接受连接 （阻塞）
    struct sockaddr_in client_info; // 用于保存客户端的信息
    int length = sizeof(client_info);

    int fd = accept(sockfd, (struct sockaddr *)&client_info, &length);
    if (fd == -1)
    {
        perror("accept");
        exit(4);
    }

    printf("接受客户端的连接 %d \n", fd);

    // 第五步：读写操作
    char buf[1024] = {0};
    ssize_t size;

    size = recv(fd, buf, sizeof(buf), 0);
    if (size == -1)
    {
        perror("recv");
        exit(5);
    }

    // 字符串转换成json
    struct json_object *obj = json_tokener_parse(buf);
    struct json_object *json;

    json_object_object_get_ex(obj, "name", &json);
    printf("name: %s\n", json_object_get_string(json));

    json_object_object_get_ex(obj, "age", &json);
    printf("age: %d\n", json_object_get_int(json));

    close(fd);     // 关闭TCP连接，不能再接收数据
    close(sockfd); // 关闭socket，不能再处理客户端的请求

    // sockfd用于处理客户端连接  fd用于处理客户端的消息
    return 0;
}