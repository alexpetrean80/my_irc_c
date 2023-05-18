//
// Created by padfoot on 5/14/23.
//

#pragma once

#include "../../lib/message/message.h"
#include <pthread.h>

typedef struct node_t {
  message_t *msg;
  struct node_t *next;
  struct node_t *prev;
} ch_node_t;

typedef struct {
  ch_node_t *head;
  ch_node_t *tail;
  pthread_mutex_t push_lock;
  size_t size;
} chan_t;

chan_t *init_chan();

void destroy_chan(chan_t *chan);
void push_msg_to_chan(chan_t *chan, message_t *msg);

message_t *pop_msg_from_chan(chan_t *chan);

message_t *front_msg_from_chan(chan_t *chan);
