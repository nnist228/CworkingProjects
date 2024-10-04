#include <arpa/inet.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#define BUFSIZE 2048
#define MAX_EPOLL_EVENTS 128
static char buffer[BUFSIZE];
static struct epoll_event events[MAX_EPOLL_EVENTS];

struct user_data {
  int fd;
  char *url;
  int url_length;
};

bool getUrlByHost(const char *buffer, struct user_data *ptr, int size) {
  char *start_path = NULL, *end_path = NULL, *start_host = NULL,
       *end_host = NULL;
  const char header_name[] = "Host: ";
  const int header_size = sizeof(header_name);
  char *c = (char *)buffer;

  for (; c != buffer + size; ++c) {
    if (*c == ' ') {
      if (start_path == NULL) {
        start_path = c + 1;
      } else if (end_path == NULL) {
        end_path = c;
        break;
      }
    }
  }

  while (c != buffer + size) {
    if (!start_host && *c == header_name[0]) {
      char potential_target[header_size];
      memcpy(potential_target, c, header_size - 1);
      potential_target[header_size - 1] = 0;
      if (!strcmp(potential_target, header_name)) {
        start_host = c + header_size - 1;
      }
      c += header_size - 1;
    } else if (start_host && isspace(*c)) {
      end_host = c;
      break;
    } else {
      ++c;
    }
  }

  if (start_path == NULL || end_path == NULL || start_host == NULL ||
      end_host == NULL) {
    if (ptr->url == NULL) {
      ptr->url = calloc(size + 1, sizeof(char));
      if (!ptr->url) {
        perror("Calloc fails in function getUrlByHost");
        return false;
      }
      ptr->url_length = size + 1;
    } else {
      ptr->url = realloc(ptr->url, size + 1);
      if (!ptr->url) {
        perror("Realloc fails in function getUrlByHost");
        return false;
      }
      ptr->url_length = size + 1;
      ptr->url[ptr->url_length - 1] = 0;
    }
    memcpy(ptr->url, buffer, size);
    return false;
  } else {
    const char http_prefix[] = "http://";
    const int http_size = strlen(http_prefix);
    int abs_path_size = end_path - start_path;
    int host_size = end_host - start_host;
    if (ptr->url == NULL) {
      ptr->url =
          calloc(http_size + host_size + abs_path_size + 1, sizeof(char));
      if (!ptr->url) {
        perror("Calloc fails in function getUrlByHost");
        return false;
      }
      ptr->url_length = http_size + host_size + abs_path_size + 1;
    } else {
      ptr->url = realloc(ptr->url, http_size + host_size + abs_path_size + 1);
      if (!ptr->url) {
        perror("Realloc fails in function getUrlByHost");
        return false;
      }
      ptr->url_length = http_size + host_size + abs_path_size + 1;
      ptr->url[ptr->url_length - 1] = 0;
    }
    memcpy(ptr->url, http_prefix, http_size);
    memcpy(ptr->url + http_size, start_host, host_size);
    memcpy(ptr->url + http_size + host_size, start_path, abs_path_size);
    return true;
  }
}

char *jsonUrlConverter(const char *src, int size) {
  static const char text[] = "{\"url\": \"";
  static const char text2[] = "\"}";
  const int text_size = strlen(text), text2_size = strlen(text2);
  int size_dest = text_size + size + text2_size;
  char *dest = calloc(size_dest, sizeof(char));
  if (!dest) {
    perror("Calloc fails in function jsonUrlConverter");
    return NULL;
  }
  memcpy(dest, text, text_size);
  memcpy(dest + text_size, src, size - 1);
  memcpy(dest + text_size + size - 1, text2, text2_size);
  return dest;
}

char *creatingGETOKHttpResponse(const char *content, int content_size) {
  const char response_header[] =
      "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: ";
  const int response_header_size = strlen(response_header);
  // time_t raw_time;
  // time(&raw_time);
  // struct tm* time_info;
  // time_info = gmtime(&raw_time);
  // char* cur_time = asctime(time_info);
  char temp_num[256];
  int num_size = sprintf(temp_num, "%d\r\n\r\n",
                         content_size + 1); // null-teminator is not included
  char *ptr_resp =
      calloc(response_header_size + num_size + content_size + 2, sizeof(char));
  if (!ptr_resp) {
    perror("Calloc fails in function creatingGETOKHttpResponse");
    return NULL;
  }
  memcpy(ptr_resp, response_header, response_header_size);
  memcpy(ptr_resp + response_header_size, temp_num, num_size);
  memcpy(ptr_resp + response_header_size + num_size, content, content_size);
  memcpy(ptr_resp + response_header_size + num_size + content_size - 1, "\r\n",
         sizeof("\r\n"));
  return ptr_resp;
}

int setnonblocking(int sock) {
  int flags = fcntl(sock, F_GETFL, 0);
  if (flags < 0) {
    perror("fcntl(F_GETFL)");
    return -1;
  }
  if (fcntl(sock, F_SETFL, flags | O_NONBLOCK) < 0) {
    perror("fcntl(F_SETFL)");
    return -1;
  }
  return 0;
}

void process_error(int fd) { printf("fd %d error!\n", fd); }

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s <port>\n", argv[0]);
    return EXIT_FAILURE;
  }

  char *p;
  int port = strtol(argv[1], &p, 10);

  if (*p) {
    printf("Invalid port number\n");
    return EXIT_FAILURE;
  }

  signal(SIGPIPE, SIG_IGN);
  int efd = epoll_create(MAX_EPOLL_EVENTS);
  int listenfd = socket(AF_INET, SOCK_STREAM, 0);

  if (listenfd < 0) {
    perror("socket");
    return EXIT_FAILURE;
  }

  setnonblocking(listenfd);
  struct sockaddr_in servaddr = {.sin_family = AF_INET,
                                 .sin_addr.s_addr = htonl(INADDR_ANY),
                                 .sin_port = htons(port)};

  if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
    perror("bind");
    return EXIT_FAILURE;
  }

  if (listen(listenfd, MAX_EPOLL_EVENTS) < 0) {
    perror("listen");
    return EXIT_FAILURE;
  }

  struct user_data server_ptr = {.fd = listenfd};
  struct epoll_event listenev = {.events = EPOLLIN | EPOLLET,
                                 .data.ptr = &server_ptr};

  if (epoll_ctl(efd, EPOLL_CTL_ADD, listenfd, &listenev) < 0) {
    perror("epoll_ctl");
    return EXIT_FAILURE;
  }

  for (;;) {
    int nfds = epoll_wait(efd, events, MAX_EPOLL_EVENTS, -1);
    if (nfds == -1) {
      perror("epoll_wait()");
      return 2;
    }
    for (int i = 0; i < nfds; i++) {
      struct epoll_event *connev = &events[i];
      struct user_data *ptr = (struct user_data *)connev->data.ptr;
      if ((connev->events & EPOLLERR) || (connev->events & EPOLLRDHUP)) {
        if ((connev->events & EPOLLERR)) {
          fprintf(stderr, "epoll error\n");
        }
        epoll_ctl(efd, EPOLL_CTL_DEL, ptr->fd, connev);
        close(ptr->fd);
        free(ptr);
        continue;
      }
      if (connev->events & EPOLLIN) {
        if (ptr->fd == listenfd) {
          for (;;) {
            int connfd = accept(listenfd, 0, 0);
            if (connfd < 0) {
              if (errno == EAGAIN || errno == EWOULDBLOCK) {
                break;
              }
              perror("accept()");
              continue;
            }
            setnonblocking(connfd);
            ptr = (struct user_data *)calloc(1, sizeof(struct user_data));
            if (!ptr) {
              perror("Malloc fails 2");
              return 3;
            }
            ptr->fd = connfd;
            connev->data.ptr = ptr;
            connev->events = EPOLLIN | EPOLLET | EPOLLERR | EPOLLRDHUP;
            if (epoll_ctl(efd, EPOLL_CTL_ADD, connfd, connev) < 0) {
              perror("epoll_ctl");
              close(connfd);
              return 4;
            }
          }
        } else {
          int rc = read(ptr->fd, buffer, sizeof(buffer));
          if (rc < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
              continue;
            }
            perror("write");
            epoll_ctl(efd, EPOLL_CTL_DEL, ptr->fd, connev);
            close(ptr->fd);
            free(ptr);
          } else if (rc ==
                     0) { // ну потому что errno обновляется только при
                          // появлении ошибки, так бы считывали старое значение
            continue;
          } else {
            bool url_caught = false;
            if (ptr->url == NULL) {
              url_caught = getUrlByHost(buffer, ptr, rc);
            } else {
              const int new_big_buffer_size =
                  ptr->url_length + rc - 1; // minus null terminator;
              char context[new_big_buffer_size];
              memcpy(context, ptr->url, ptr->url_length - 1);
              memcpy(context + ptr->url_length - 1, buffer, rc);
              url_caught = getUrlByHost(context, ptr, new_big_buffer_size);
            }
            if (url_caught) {
              char *back_content = jsonUrlConverter(ptr->url, ptr->url_length);
              if (!back_content) {
                return EXIT_FAILURE;
              }
              char *http_response = creatingGETOKHttpResponse(
                  back_content, strlen(back_content) + 1);
              if (!http_response) {
                return EXIT_FAILURE;
              }
              write(ptr->fd, http_response, strlen(http_response));
              free(ptr->url);
              free(back_content);
              free(http_response);
              ptr->url = NULL;
              ptr->url_length = 0;
            }
          }
        }
      }
    }
  }
  close(listenfd);
  return 0;
}
