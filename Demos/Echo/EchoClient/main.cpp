#include <cstdio>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <ctype.h>
#include <arpa/inet.h>

constexpr int PORT{ 6666 };
constexpr char* SERVERADDR = "127.0.0.1";

int main(int argc, char* argv[])
{
    if (argc != 2)
        return -1;
    char* msg = argv[1];
    printf("msg is %s\n", msg);

    struct sockaddr_in serverAddr;
    bzero(&serverAddr, sizeof(serverAddr));

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    inet_pton(AF_INET, SERVERADDR, &serverAddr.sin_addr);
    serverAddr.sin_port = htons(PORT);

    int ret = connect(sockfd, (struct sockaddr*) & serverAddr, sizeof(serverAddr));
    if (!ret)
    {
        printf("connect failed. %s, %d", serverAddr.sin_addr, serverAddr.sin_port);
    }

    write(sockfd, msg, strlen(msg));

    char buf[256] = { 0 };
    ssize_t readLen = read(sockfd, buf, sizeof(buf) - 1);
    if (readLen > 0)
    {
        printf("recieve is %s, len is %d\n", buf, readLen);
    }

    close(sockfd);
    return 0;
}