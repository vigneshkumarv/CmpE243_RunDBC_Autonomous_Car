// @file queue.h
#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
  float queue_memory[3];
  int front;
  int rear;
  int size;
  float sum;

  // TODO: Add more members as needed
} queue_S;

void queue__init(queue_S *queue);

bool queue__push(queue_S *queue, float push_value);

bool queue__pop(queue_S *queue, float *pop_value);

int queue__get_count(queue_S *queue);

float queue__update_and_get_average(queue_S *queue, float value);

#endif
