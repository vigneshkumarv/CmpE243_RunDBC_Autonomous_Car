// @file queue.h
#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
  int queue_memory[10];
  int front;
  int rear;
  int size;
  int sum;
  int max;
  int min;
  int second_max;
  // TODO: Add more members as needed
} queue_S;

void queue__init(queue_S *queue);

bool queue__push(queue_S *queue, int push_value);

bool queue__pop(queue_S *queue, int *pop_value);

int queue__get_count(queue_S *queue);

int queue__update_and_get_average(queue_S *queue, int value);

void queue__update_middle(queue_S *queue, int push_value, int *max_value, int *min_value, int *second_max);

#endif
