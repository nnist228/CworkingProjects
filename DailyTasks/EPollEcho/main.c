#include <sys/epoll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <unistd.h>
static char buffer[2048];


int setnonblocking(int sock)
{
    int opts;
    opts = fcntl(sock,F_GETFL);
    if (opts < 0)
    {
    perror("fcntl(F_GETFL)");
    return -1;
    }
    opts = (opts | O_NONBLOCK);
    if (fcntl(sock,F_SETFL,opts) < 0)
    {
    perror("fcntl(F_SETFL)");
    return -1;
    }
    return 0;
}

void echo(int fd){
    for(;;){
        int rc = recv(fd, buffer, sizeof(buffer), 0);
        if (rc < 0)
        {
            if(errno == EAGAIN || errno == EWOULDBLOCK) {
              break;
            } else {
              perror("read()");
              return;
            }
        } else if (rc == 0) {
            close(rc);
            break;
        } else {
            rc = send(fd, buffer, sizeof(buffer), 0);
            if (rc < 0)
            {
                perror("write");
                return;
            }
        }
    }
}

#if 0
void do_read(int fd)
{
    int rc = recv(fd, buffer, sizeof(buffer), 0);
    if (rc < 0)
    {
        perror("read");
        return;
    }
    buffer[rc] = 0;
    printf("read: %s\n", buffer);
    }
#endif
#if 0
void do_write(int fd)
{
    static const char* greeting = "O hai!\n";
    int rc = send(fd, greeting, strlen(greeting), 0);
    if (rc < 0)
    {
        perror("write");
        return;
    }
}
#endif 

void process_error(int fd)
{
    printf("fd %d error!\n", fd);
}

#define MAX_EPOLL_EVENTS 128
static struct epoll_event events[MAX_EPOLL_EVENTS];
#define BACKLOG 128


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
    struct sockaddr_in servaddr = {0};
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("bind");
        return EXIT_FAILURE;
    }

    if (listen(listenfd, BACKLOG) < 0)
    {
        perror("listen");
        return EXIT_FAILURE;
    }

    struct epoll_event listenev;
    listenev.events = EPOLLIN | EPOLLET;
    listenev.data.fd = listenfd;

    if (epoll_ctl(efd, EPOLL_CTL_ADD, listenfd, &listenev) < 0)
    {
        perror("epoll_ctl");
        return EXIT_FAILURE;
    }
    struct epoll_event connev;
    int events_count = 1;

    for (;;)
    {
        int nfds = epoll_wait(efd, events, MAX_EPOLL_EVENTS, -1);
        if (nfds == -1) {
            perror("epoll_wait()");
            return 1;
        }
        for (int i = 0; i < nfds; i++)
        {
            if ((events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP) ||
                (!(events[i].events & EPOLLIN)) || (!(events[i].events & EPOLLOUT))) 
            {
                fprintf(stderr, "epoll error\n");
                close(events[i].data.fd);
                continue;
            }
            if (events[i].data.fd == listenfd)
            {
                for(;;){
                    struct sockaddr in_addr;
                    socklen_t in_addr_len = sizeof(in_addr);
                    int connfd = accept(listenfd, &in_addr, &in_addr_len);
                    if (connfd < 0)
                    {
                        if (errno == EAGAIN || errno == EWOULDBLOCK) {
                            break;
                        } else {
                            perror("accept()");
                            return 1;
                        }
                    }
                    if (events_count == MAX_EPOLL_EVENTS-1)
                    {
                        printf("Event array is full\n");
                        close(connfd);
                        continue;
                    }
                    setnonblocking(connfd);
                    connev.data.fd = connfd;
                    connev.events = EPOLLIN | EPOLLOUT /*| EPOLLET | EPOLLRDHUP*/;
                    if (epoll_ctl(efd, EPOLL_CTL_ADD, connfd, &connev) < 0)
                    {
                        perror("epoll_ctl");
                        close(connfd);
                        return 1;
                    }
                    events_count++;
                }
            }
            else
            {
                int fd = events[i].data.fd;
                if (events[i].events & EPOLLIN & EPOLLOUT)
                    echo(fd);
                #if 0
                if (events[i].events & EPOLLOUT)
                do_write(fd);
                if (events[i].events & EPOLLRDHUP)
                process_error(fd);
                epoll_ctl(efd, EPOLL_CTL_DEL, fd, &connev);
                close(fd);
                events_count--;
                #endif
            }
        }
    }
    return 0;
}
