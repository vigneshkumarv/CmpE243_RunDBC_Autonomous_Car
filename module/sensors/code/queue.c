#include "queue.h"
#include <stdio.h>

//#define QUEUE_MAX 10
#define QUEUE_MAX 3

void queue__init(queue_S *queue) {
  queue->front = 0;
  queue->rear = -1;
  queue->size = 0;
}

bool queue__push(queue_S *queue, int push_value) {
  if (queue->size == QUEUE_MAX) {
    return false;
  } else {
    if (queue->rear == QUEUE_MAX - 1) {
      queue->rear = -1;
    }

    queue->rear += 1;
    queue->queue_memory[queue->rear] = push_value;
    queue->size += 1;
    queue->sum += push_value;

    return true;
  }
}

bool queue__pop(queue_S *queue, int *pop_value) {
  if (queue->size == 0) {
    return false;
  }

  else {
    if (queue->front == QUEUE_MAX) {
      queue->front = 0;
    }
    *pop_value = queue->queue_memory[queue->front];
    queue->front += 1;
    queue->size -= 1;
    queue->sum -= *pop_value;
    return true;
  }
}

int queue__get_count(queue_S *queue) { return queue->size; }

int queue__update_and_get_average(queue_S *queue, int value) {
  int pop_value;
  if (queue->size == QUEUE_MAX) {
    queue__pop(queue, &pop_value);
    //queue->sum -= pop_value;
  }
  queue__push(queue, value);
  return (queue->sum / QUEUE_MAX);
}

int queue__update_and_get_median(queue_S *queue, int value) {
  int pop_value;
  if (queue->size == QUEUE_MAX) {
    queue__pop(queue, &pop_value);
  }
  queue__push(queue, value);

  if ((queue->queue_memory[0] >= queue->queue_memory[1]) && (queue->queue_memory[0] >= queue->queue_memory[2]))
      return (queue->queue_memory[1] >= queue->queue_memory[2]) ? queue->queue_memory[1] : queue->queue_memory[2];

  else if ((queue->queue_memory[1] >= queue->queue_memory[0]) && (queue->queue_memory[1] >= queue->queue_memory[2]))
      return (queue->queue_memory[0] >= queue->queue_memory[2]) ? queue->queue_memory[0] : queue->queue_memory[2];

  else
      return (queue->queue_memory[1]> queue->queue_memory[0]) ? queue->queue_memory[1] : queue->queue_memory[0];

}
