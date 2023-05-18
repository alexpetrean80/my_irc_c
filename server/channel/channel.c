//
// Created by padfoot on 5/14/23.
//

#include <malloc.h>
#include "channel.h"

Channel *init_chan() {
    Channel *chan = (Channel *) malloc(sizeof(Channel));
    chan->head = NULL;
    chan->tail = NULL;
    chan->size = 0;
    pthread_mutex_init(&chan->push_lock, NULL);

    return chan;
}

void destroy_chan(Channel *chan) {
    pthread_mutex_destroy(&chan->push_lock);

    Node *current = chan->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current->msg);
        free(current);
        current = next;
    }
}

void push_msg_to_chan(Channel *chan, Message *msg) {
    Node *new = (Node *) malloc(sizeof(Node));
    new->msg = msg;
    new->next = NULL;
    pthread_mutex_lock(&chan->push_lock);
    chan->tail->next = new;
    new->prev = chan->tail;
    chan->tail = new;
    pthread_mutex_unlock(&chan->push_lock);
}

Message *pop_msg_from_chan(Channel *chan) {
    Message *msg = chan->head->msg;

    chan->head = chan->head->next;
    free(chan->head->prev);
    chan->head->prev = NULL;

    return msg;
}

Message *front_msg_from_chan(Channel *chan) {
    Message *msg = chan->head->msg;
    return msg;
}



