#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#define BACKLOG 10

int main(int argc, char **argv) {
    int status;
    struct addrinfo hints;
    struct addrinfo *servinfo;
    struct sockaddr_storage their_addr;
    socklen_t addr_size;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ((status = getaddrinfo(NULL, "3490", &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }

    int s;
    if ((s = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1) {
        fprintf(stderr, "socket error: %d\n", status);
        exit(1);
    }

    printf("%d\n", s);
    int yes=1;

    if ((status = setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes)) == -1) {
        fprintf(stderr, "setsockopt error: %d\n", status);
        exit(1);
    } 

    if((status = bind(s, servinfo->ai_addr, servinfo->ai_addrlen)) == -1) {
        fprintf(stderr, "bind error: %d\n", status);
        exit(1);
    }

    listen(s, BACKLOG);

    addr_size = sizeof their_addr;
    int new_fd = accept(s, (struct sockaddr *)&their_addr, &addr_size);
    printf("%d\n", new_fd);

    int t = 10;
    char c;
    while (t--) {
        char *msg = "Hi mom!\0";
        int len = strlen(msg), bytes_sent;
        if ((bytes_sent = send(new_fd, msg, len, 0)) == -1) {
            fprintf(stderr, "send error: %d\n", status);
            exit(1);
        }
    }
    char *msg = "Ja!\0";
    int len = strlen(msg), bytes_sent;
    if ((bytes_sent = send(new_fd, msg, len, 0)) == -1) {
        fprintf(stderr, "send error: %d\n", status);
        exit(1);
    }
    

    freeaddrinfo(servinfo);
}
