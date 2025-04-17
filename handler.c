#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include "handler.h"

int verbose = 0;

void* handleConnection(int sock_fd_ptr) {
    int sock_fd = (int)(intptr_t)sock_fd_ptr;

    printf("Handling connection on %d\n", sock_fd); 

    char buffer[1024];  

    while (1) {
        memset(buffer, 0, sizeof(buffer));  

        ssize_t bytes_read = read(sock_fd, buffer, 1023);

        if (bytes_read > 0) {
            write(sock_fd, buffer, bytes_read);
            if (verbose == 1) {
                printf("read %ld bytes from %d: %s\n", bytes_read, sock_fd, buffer);
            }
        } else if (bytes_read == 0) {
            printf("Connection closed\n");
            break;
        } else {
            perror("read");
            break;
        }
    }

    printf("Done with connection %d\n", sock_fd);
    close(sock_fd);
    return NULL;
}
