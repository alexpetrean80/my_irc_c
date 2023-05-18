//
// Created by padfoot on 5/13/23.
//

#pragma once

#include "../../lib/globals.h"

typedef struct {
  char ip_addr[MAX_LENGTH];
  unsigned int port;
  char name[MAX_LENGTH];
} server_t;
