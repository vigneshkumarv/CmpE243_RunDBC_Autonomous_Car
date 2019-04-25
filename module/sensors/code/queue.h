// @file queue.h
#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
  int queue_memory[3];
  int front;
  int rear;
  int size;
  int sum;

  // TODO: Add more members as needed
} queue_S;

void queue__init(queue_S *queue);

bool queue__push(queue_S *queue, int push_value);

bool queue__pop(queue_S *queue, int *pop_value);

int queue__get_count(queue_S *queue);

int queue__update_and_get_average(queue_S *queue, int value);

int queue__update_and_get_median(queue_S *queue, int value);

#endif
