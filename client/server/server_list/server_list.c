//
// Created by padfoot on 5/13/23.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server_list.h"

ServerList *init_server_list() {
    ServerList *srv_list = (ServerList *) malloc(sizeof(ServerList));
    srv_list->first = NULL;
    srv_list->size = 0;
    return srv_list;
}

void free_server_list(ServerList *srv_list) {
    Node *current = srv_list->first;
    Node *next = NULL;

    while (current != NULL) {
        free(current->elem);
        next = current->next;
        free(current);
        current = next;
    }

    free(srv_list);
}

Server *append_server_list(ServerList *list, char *name, char *ip_addr, unsigned int port) {
    Node *new = (Node *) malloc(sizeof(Node));
    new->elem = (Server *) malloc(sizeof(Server));
    strncpy(new->elem->name, name, MAX_LENGTH - 1);
    strncpy(new->elem->ip_addr, ip_addr, MAX_LENGTH - 1);
    new->elem->port = port;
    if (NULL == list->first) {
        list->first = new;
    } else {
        new->next = list->first;
        list->first = new;
    }
    list->size++;

    return new->elem;
}

short remove_server_list(ServerList *list, char *name) {
    Node *current = list->first;
    Node *prev = NULL;
    while (current != NULL) {
        if (strcmp(current->elem->name, name) != 0) {
            prev = current;
            current = current->next;
            continue;
        }
        if (prev == NULL) { // removing the first node
            list->first = current->next;
        } else {
            prev->next = current->next;
        }
        free(current->elem);
        free(current);
        list->size--;
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

Server *get_server_info(ServerList *list, char *name) {
    Node *current = list->first;
    while (current != NULL) {
        if (strcmp(current->elem->name, name) == 0) {
            return current->elem;
        }

        current = current->next;
    }
    return NULL;
}


char **get_all_server_names(ServerList *list) {
    char **server_names = (char **) malloc(sizeof(char *) * list->size);
    Node *current = list->first;
    for (unsigned int i = 0; i < list->size; i++) {
        strcpy(server_names[i], current->elem->name);
    }

    return server_names;
}

ServerList *read_server_list_from_file() {
    FILE *fp = fopen(SERVER_LIST_FILE_NAME, "rb");
    if (fp == NULL) {
        perror("Error opening file for reading");
        return NULL;
    }
    ServerList *list = init_server_list();
    Server server;
    while (fread(&server, sizeof(Server), 1, fp) == 1) {
        append_server_list(list, server.name, server.ip_addr, server.port);
    }
    fclose(fp);
    return list;
}

void write_server_list_to_file(ServerList *list) {
    FILE *fd = fopen(SERVER_LIST_FILE_NAME, "wb");
    if (fd == NULL) {
        perror("Error opening file for writing");
        return;
    }
    Node *current = list->first;
    while (current != NULL) {
        fwrite(current->elem, sizeof(Server), 1, fd);
        current = current->next;
    }
    fclose(fd);
}
