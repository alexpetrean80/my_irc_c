//
// Created by padfoot on 5/13/23.
//

#pragma once

#include "../server.h"
#include <stddef.h>

typedef struct node_t {
  server_t *elem;
  struct node_t *next;
} sl_node_t;

typedef struct {
  sl_node_t *first;
  size_t size;
} server_list_t;

server_list_t *init_server_list();

void free_server_list(server_list_t *list);

server_t *append_server_list(server_list_t *list, char *name, char *ip_addr,
                             unsigned int port);

short remove_server_list(server_list_t *list, char *name);

server_t *get_server_info(server_list_t *list, char *name);

char **get_all_server_names(server_list_t *list);

server_list_t *read_server_list_from_file();

void write_server_list_to_file(server_list_t *list);
