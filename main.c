#include <stdio.h>
#include <string.h>
#include "handler.h"
#include "setup.h"

int main(int argc, char* argv[]) {
    int port = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
            port = parse_port(argv[i + 1]);
            if (port <= 0) {
                printf("Invalid port number\n");
                return 1;
            }
            i++;
        } else if (strcmp(argv[i], "-v") == 0) {
            verbose = 1;
        } else {
            printf("Unknown argument: %s\n", argv[i]);
            return 1;
        }
    }

    if (port == 0) {
        printf("Usage: %s -p <port> [-v]\n", argv[0]);
        return 1;
    }

    return start_server(port);
}
