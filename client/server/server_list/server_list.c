//
// Created by padfoot on 5/13/23.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server_list.h"

server_list_t *init_server_list() {
    server_list_t *srv_list = (server_list_t *) malloc(sizeof(server_list_t));
    srv_list->first = NULL;
    srv_list->size = 0;
    return srv_list;
}

void free_server_list(server_list_t *srv_list) {
    sl_node_t *current = srv_list->first;
    sl_node_t *next = NULL;

    while (current != NULL) {
        free(current->elem);
        next = current->next;
        free(current);
        current = next;
    }

    free(srv_list);
}

server_t *append_server_list(server_list_t *list, char *name, char *ip_addr, unsigned int port) {
    sl_node_t *new = (sl_node_t *) malloc(sizeof(sl_node_t));
    new->elem = (server_t *) malloc(sizeof(server_t));
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

short remove_server_list(server_list_t *list, char *name) {
    sl_node_t *current = list->first;
    sl_node_t *prev = NULL;
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

server_t *get_server_info(server_list_t *list, char *name) {
    sl_node_t *current = list->first;
    while (current != NULL) {
        if (strcmp(current->elem->name, name) == 0) {
            return current->elem;
        }

        current = current->next;
    }
    return NULL;
}


char **get_all_server_names(server_list_t *list) {
    char **server_names = (char **) malloc(sizeof(char *) * list->size);
    sl_node_t *current = list->first;
    for (unsigned int i = 0; i < list->size; i++) {
        strcpy(server_names[i], current->elem->name);
    }

    return server_names;
}

server_list_t *read_server_list_from_file() {
    FILE *fp = fopen(SERVER_LIST_FILE_NAME, "rb");
    if (fp == NULL) {
        perror("Error opening file for reading");
        return NULL;
    }
    server_list_t *list = init_server_list();
    server_t server;
    while (fread(&server, sizeof(server_t), 1, fp) == 1) {
        append_server_list(list, server.name, server.ip_addr, server.port);
    }
    fclose(fp);
    return list;
}

void write_server_list_to_file(server_list_t *list) {
    FILE *fd = fopen(SERVER_LIST_FILE_NAME, "wb");
    if (fd == NULL) {
        perror("Error opening file for writing");
        return;
    }
    sl_node_t *current = list->first;
    while (current != NULL) {
        fwrite(current->elem, sizeof(server_t), 1, fd);
        current = current->next;
    }
    fclose(fd);
}
