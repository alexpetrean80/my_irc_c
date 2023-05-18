//
// Created by padfoot on 5/13/23.
//

#pragma once

#include <stddef.h>
#include "../../server/server.h"

typedef struct Node {
    Server *elem;
    struct Node *next;
} Node;

typedef struct {
    Node *first;
    size_t size;
} ServerList;

ServerList *init_server_list();

void free_server_list(ServerList *list);

Server *append_server_list(ServerList *list, char *name, char *ip_addr, unsigned int port);

short remove_server_list(ServerList *list, char *name);

Server *get_server_info(ServerList *list, char *name);

char **get_all_server_names(ServerList *list);

ServerList *read_server_list_from_file();

void write_server_list_to_file(ServerList *list);

