//
// Created by padfoot on 5/13/23.
//

#pragma once

#include "../globals.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
  char name[MAX_LENGTH];
  char ip_addr[MAX_LENGTH];
} user_info_t;

short read_user_info(user_info_t *user);

short store_user_info(char *user_name, char *ip_addr);
