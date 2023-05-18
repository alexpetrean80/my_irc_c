//
// Created by padfoot on 5/14/23.
//

#pragma once

#include <pthread.h>
#include "../message/message.h"

typedef struct Node {
    Message *msg;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    pthread_mutex_t push_lock;
    size_t size;
} Channel;

Channel *init_chan();

void destroy_chan(Channel *chan);
void push_msg_to_chan(Channel *chan, Message *msg);

Message *pop_msg_from_chan(Channel *chan);

Message *front_msg_from_chan(Channel *chan);


