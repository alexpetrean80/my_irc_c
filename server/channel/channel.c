//
// Created by padfoot on 5/14/23.
//

#include "channel.h"
#include <malloc.h>

channel_t *init_chan() {
  channel_t *chan = (channel_t *)malloc(sizeof(channel_t));
  chan->head = NULL;
  chan->tail = NULL;
  chan->size = 0;
  pthread_mutex_init(&chan->push_lock, NULL);

  return chan;
}

void destroy_chan(channel_t *chan) {
  pthread_mutex_destroy(&chan->push_lock);

  node_t *current = chan->head;
  while (current != NULL) {
    node_t *next = current->next;
    free(current->msg);
    free(current);
    current = next;
  }
}

void push_msg_to_chan(channel_t *chan, Message *msg) {
  node_t *new = (node_t *)malloc(sizeof(node_t));
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
