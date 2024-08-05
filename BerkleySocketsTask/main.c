#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


#define PORT 23
#define BUF_SIZE 2048
static char buffer[BUF_SIZE];
static const char server_name[] = "telehack.com";

int main(int argc, char** argv)
{
    if(argc != 3){
        perror("Wrong number of arguments");
        return 1;
    }
    int sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock_fd < 0){
        perror("socket");
        return 2;
    }
    struct addrinfo hint;
    memset(&hint, 0, sizeof(struct addrinfo));
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_flags = 0;
    hint.ai_protocol = 0;  

    struct addrinfo *r_ptr = NULL;
    int error = getaddrinfo(server_name, 0, &hint, &r_ptr);
    if(error != 0){
        perror(gai_strerror(error));
        close(sock_fd);
        freeaddrinfo(r_ptr);
        return 4;
    }
    struct sockaddr_in sock_addr = {0};
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(PORT);
    printf("%s\n",  r_ptr->ai_addr->sa_data);
    int r = inet_pton(AF_INET, r_ptr->ai_addr->sa_data, &sock_addr.sin_addr);
    freeaddrinfo(r_ptr);
    if(r <= 0){
        perror("inet_pton");
        close(sock_fd);
        return 5;
    }
    if(connect(sock_fd, (struct sockaddr*)&sock_addr, sizeof(sock_addr)) < 0){
        perror("connect");
        close(sock_fd);
        return 6;
    }

    int len = 0;
    while((r = recv(sock_fd, &buffer[len], BUF_SIZE - len, 0)) > 0){
        len += r;
    }

    char string_command[512] = "figlet /";
    strcat(string_command, argv[1]);
    strcat(string_command, " ");
    strcat(string_command, argv[2]);

    if(send(sock_fd, string_command, strlen(string_command), 0) < 0){
        perror("send");
        shutdown(sock_fd, SHUT_RDWR);
        close(sock_fd);
        return 8;
    }

    len = 0;
    while((r = recv(sock_fd, &buffer[len], BUF_SIZE - len, 0)) > 0){
        printf("%s", buffer + len);
        len += r;
    }
    shutdown(sock_fd, SHUT_RDWR);
    close(sock_fd);

    return 0;
}