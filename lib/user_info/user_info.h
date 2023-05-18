//
// Created by padfoot on 5/13/23.
//

#pragma once

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../globals.h"


typedef struct {
    char name[MAX_LENGTH];
    char ip_addr[MAX_LENGTH];
} UserInfo;

short read_user_info(UserInfo *user);

short store_user_info(char *user_name, char *ip_addr);