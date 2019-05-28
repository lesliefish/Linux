#include <cstdio>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <ctype.h>
#include <arpa/inet.h>

constexpr int PORT{ 6666 };

int main(int argc, char* argv[])
{
    int sock{ -1 };
    struct sockaddr_in serverAddr {};

    sock = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&serverAddr, sizeof(serverAddr));

    serverAddr.sin_port = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(PORT);

    bind(sock, (struct sockaddr*) & serverAddr, sizeof(serverAddr));

    listen(sock, 128);

    printf("waiting for connecting: \n");

    while (true)
    {
        struct sockaddr_in client;
        socklen_t clientAddrLen;
        char clientIp[16] = { 0 };
        auto clientSock = accept(sock, (struct sockaddr*) & client, &clientAddrLen);
        printf("client ip is %s, port is %d \n",
            inet_ntop(AF_INET, &client.sin_addr.s_addr, clientIp, sizeof(clientIp)),
            ntohs(client.sin_port));

        char readBuf[256] = { 0 };
        int readLen = read(clientSock, readBuf, sizeof(readBuf) - 1);
        readBuf[readLen] = '\0';
        printf("recieve is %s, len is %d\n", readBuf, readLen);
    }

    return 0;
}