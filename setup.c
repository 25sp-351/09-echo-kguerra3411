#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>
#include <stdint.h>
#include "handler.h"
#include "setup.h"

int parse_port(const char* str) {
    int port = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] < '0' || str[i] > '9') {
            return -1;
        }
        port = port * 10 + (str[i] - '0');
    }
    return port;
}

int start_server(int port) {
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        perror("socket");
        return 1;
    }

    struct sockaddr_in socket_address;
    memset(&socket_address, 0, sizeof(socket_address));
    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = htonl(INADDR_ANY);
    socket_address.sin_port = htons(port);

    printf("Binding to port %d\n", port);

    int returnval = bind(socket_fd, (struct sockaddr*)&socket_address, sizeof(socket_address));
    if (returnval < 0) {
        perror("bind");
        return 1;
    }

    returnval = listen(socket_fd, 5);
    if (returnval < 0) {
        perror("listen");
        return 1;
    }

    struct sockaddr_in client_address;
    socklen_t client_address_len = sizeof(client_address);

    while (1) {
        int client_fd = accept(socket_fd, (struct sockaddr*)&client_address, &client_address_len);
        if (client_fd < 0) {
            perror("accept");
            continue;
        }

        printf("Accepted connection on %d\n", client_fd);

        pthread_t thread;
        pthread_create(&thread, NULL, (void* (*)(void*)) handleConnection, (void*)(intptr_t) client_fd);
        pthread_detach(thread);
    }

    close(socket_fd);
    return 0;
}
