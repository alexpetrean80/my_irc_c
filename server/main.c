#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define EVER ;;
#define PORT 2323
#define MAX_CLIENT_LIMIT 100

void *conn_handler(void *arg) {
    return NULL;
}


int main(void) {
    int server_fd;
    struct sockaddr_in server_addr;

    pthread_t threads[MAX_CLIENT_LIMIT];
    unsigned short thread_count = 0;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (0 == server_fd) {
        perror("Cannot create socket.");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Cannot set sock options.");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("Cannot bind socket to addr.");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 5) < 0) {
        perror("Listen failed.");
        exit(EXIT_FAILURE);
    }

    printf("Server started on port %d...\n", PORT);

    int client_fd;
    for (EVER) {
        if ((client_fd = accept(server_fd, (struct sockaddr *) &server_addr, (socklen_t *) &server_addr)) < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        if (pthread_create(&threads[thread_count], NULL, conn_handler, (void *) &client_fd) == 0) {
            perror("Cannot spawn thread.");
            exit(EXIT_FAILURE);
        } else {
            thread_count++;
        }
    }

}