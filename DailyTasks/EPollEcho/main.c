#include <sys/epoll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <fcntl.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <unistd.h>
#define BUFSIZE 2048
#define MAX_EPOLL_EVENTS 128    
static char buffer[BUFSIZE];   
static struct epoll_event events[MAX_EPOLL_EVENTS];
static const size_t error_lenght = sizeof("Invalid number! One number per time, please");

struct user_data{
    int fd;
    long count;
    long sum;
};

bool string_validation(char* string, int size){
    for(int i = (string[0] == '-') ? 1 : 0; i < size; i++){
        if(!isdigit(string[i])){
            return false;
        }
    }
    return true;
}

int setnonblocking(int sock)
{
    int flags = fcntl(sock, F_GETFL, 0);
    if (flags < 0)
    {
        perror("fcntl(F_GETFL)");
        return -1;
    }
    if (fcntl(sock,F_SETFL, flags | O_NONBLOCK) < 0)
    {
        perror("fcntl(F_SETFL)");
        return -1;
    }
    return 0;
}

void process_error(int fd)
{
    printf("fd %d error!\n", fd);
}


int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("Usage: %s <port>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char* p;
    int port = strtol(argv[1], &p, 10);

    if (*p)
    {
        printf("Invalid port number\n");
        return EXIT_FAILURE;
    }

    signal(SIGPIPE, SIG_IGN);
    int efd = epoll_create(MAX_EPOLL_EVENTS);
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);

    if (listenfd < 0)
    {
        perror("socket");
        return EXIT_FAILURE;
    }

    setnonblocking(listenfd);
    struct sockaddr_in servaddr = {.sin_family = AF_INET, .sin_addr.s_addr = htonl(INADDR_ANY), .sin_port = htons(port)};

    if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("bind");
        return EXIT_FAILURE;
    }

    if (listen(listenfd, MAX_EPOLL_EVENTS) < 0)
    {
        perror("listen");
        return EXIT_FAILURE;
    }

    struct user_data* server_ptr = (struct user_data*) malloc(sizeof(struct user_data));
    if(!server_ptr){
        perror("Malloc fails 1");
        return 1;
    }
    server_ptr->fd = listenfd;
    struct epoll_event listenev = {.events = EPOLLIN | EPOLLET, .data.ptr = (void*) server_ptr};
    if (epoll_ctl(efd, EPOLL_CTL_ADD, listenfd, &listenev) < 0)
    {
        perror("epoll_ctl");
        return EXIT_FAILURE;
    }
    for (;;)
    {
        int nfds = epoll_wait(efd, events, MAX_EPOLL_EVENTS, -1);
        if (nfds == -1) {
            perror("epoll_wait()");
            return 2;
        }
        for (int i = 0; i < nfds; i++)
        {
            struct epoll_event* connev = &events[i];
            struct user_data* ptr = (struct user_data*) connev->data.ptr;
            if((connev->events & EPOLLERR) || (connev->events & EPOLLRDHUP))
            {
                fprintf(stderr, "epoll error\n");
                epoll_ctl(efd, EPOLL_CTL_DEL, ptr->fd, connev);
                close(ptr->fd);
                free(ptr);
                continue;
            }
            if(connev->events & EPOLLIN){
                if (ptr->fd == listenfd)
                {
                    for(;;){
                        int connfd = accept(listenfd, 0, 0); 
                        if (connfd < 0)
                        {
                            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                                break;
                            }
                            perror("accept()");
                            continue; //здесь нужно крашиться или норм?
                        }
                        setnonblocking(connfd);
                        ptr = (struct user_data*) malloc(sizeof(struct user_data));
                        if(!ptr){
                            perror("Malloc fails 2");
                            return 3;
                        }
                        ptr->fd = connfd;
                        ptr->sum = 0;
                        ptr->count = 0;
                        connev->data.ptr = (void*) ptr;
                        connev->events = EPOLLIN | EPOLLET | EPOLLERR | EPOLLRDHUP;
                        if (epoll_ctl(efd, EPOLL_CTL_ADD, connfd, connev) < 0)
                        {
                            perror("epoll_ctl");
                            close(connfd);
                            return 4;
                        }
                    }
                }
                else
                {
                    int rc;
                    fear: // страх оставить хвостик, неактуально в данной задаче
                    rc = read(ptr->fd, buffer, sizeof(buffer));
                    if(rc < 0){
                        if(errno == EAGAIN || errno == EWOULDBLOCK){
                            continue;
                        }
                        perror("write");
                        goto cleanup;
                    } else if(rc == 0){ // ну потому что errno обновляется только при появлении ошибки, так бы считывали старое значение
                        continue;
                    } else{
                        if(string_validation(buffer, rc)){ //ВСЕГДА false wtf?
                            long new_number = atol(buffer);
                            ptr->count += 1;
                            ptr->sum += new_number;
                            double mean = (double)ptr->sum / ptr->count;
                            int back = sprintf(buffer, "%lf\n", mean);
                            back = send(ptr->fd, buffer, back, 0);
                            if (back < 0)
                            {
                                if(errno == EAGAIN || errno == EWOULDBLOCK){
                                    continue;
                                }
                                perror("write");
                                goto cleanup;
                            }
                            if(rc >= BUFSIZE) // а вдруг там что-то еще, неактуально в данной задаче
                                goto fear;
                            continue;
                        } else{
                            rc = send(ptr->fd, "Invalid number! One number per time, please", error_lenght, 0);
                            if (rc < 0)
                            {
                                if(errno == EAGAIN || errno == EWOULDBLOCK){
                                    continue;
                                }
                                perror("write on invalid input");
                                goto cleanup;
                            }
                            continue;
                        }
                        cleanup:
                            epoll_ctl(efd, EPOLL_CTL_DEL, ptr->fd, connev);
                            close(ptr->fd);
                            free(ptr);
                    }
                }
            }
        }
    }
    close(listenfd);
    free(server_ptr);
    return 0;
}
