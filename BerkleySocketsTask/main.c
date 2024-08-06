#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


#define BUF_SIZE 2048
static  char buffer[BUF_SIZE];
static const  char server_name[] = "telehack.com";

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
    int error = getaddrinfo(server_name, "telnet", &hint, &r_ptr);
    if(error != 0){
        perror(gai_strerror(error));
        close(sock_fd);
        freeaddrinfo(r_ptr);
        return 4;
    }

    if(connect(sock_fd, r_ptr->ai_addr, r_ptr->ai_addrlen) < 0){
        perror("connect");
        close(sock_fd);
        return 6;
    }
    freeaddrinfo(r_ptr);

    size_t len = 0;
    while((len = recv(sock_fd, buffer, BUF_SIZE, 0)) > 0){
        if(buffer[len-1] == '.' && buffer[len-2] == '\n'){
            memset(buffer, '\0', sizeof(buffer));
            break;
        }
        memset(buffer, '\0', sizeof(buffer));
    }
    
    char string_command[BUF_SIZE] = "figlet /";
    strcat(string_command, argv[1]);
    strcat(string_command, " ");
    size_t offset = strlen(string_command);
    size_t length = 0;
    while(length < strlen(argv[2])){
        len = BUF_SIZE - offset - 2;
        strncat(string_command, argv[2] + length , len);
        length += len;
        strcat(string_command, "\r\n");
        size_t command_size = strlen(string_command);
        if(send(sock_fd, string_command, command_size + 1, 0) < 0){
            perror("send");
            shutdown(sock_fd, SHUT_RDWR);
            close(sock_fd);
            return 8;
        }
        len = 0;
        while((len = recv(sock_fd, buffer, BUF_SIZE, 0)) > 0){
            if(buffer[len-1] == '.' && buffer[len-2] == '\n'){
                buffer[len-2] = '\0';
                printf("%s", buffer + command_size);
                memset(buffer, '\0', sizeof(buffer));
                break;
            }
            printf("%s", buffer + command_size);
            memset(buffer, '\0', sizeof(buffer));
            command_size = 0;
        }
        memset(string_command + offset, '\0', sizeof(string_command) - offset);
    }
    
    shutdown(sock_fd, SHUT_RDWR);
    close(sock_fd);

    return 0;
}
