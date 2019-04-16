#include "queue.h"
#include <stdio.h>

#define QUEUE_MAX 10

void queue__init(queue_S *queue) {
  queue->front = 0;
  queue->rear = -1;
  queue->size = 0;
  queue->max = 0;
  queue->min = 0;
  queue->second_max = 0;
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
    return true;
  }
}

int queue__get_count(queue_S *queue) { return queue->size; }

int queue__update_and_get_average(queue_S *queue, int value) {
  int pop_value;
  if (queue->size == QUEUE_MAX) {
    queue__pop(queue, &pop_value);
    queue->sum -= pop_value;
  }
  queue__push(queue, value);
  queue->sum += value;
  return (queue->sum / QUEUE_MAX);
}

void queue__update_middle(queue_S *queue, int push_value, int *max_value, int *min_value, int *second_max) {
  int pop_value;
  if (queue->size == QUEUE_MAX) {
    queue__pop(queue, &pop_value);
    queue->sum -= pop_value;
  }
  queue__push(queue, push_value);

  // copy queue value to a temp array
  int temp_arr[QUEUE_MAX] = {0};
  for (int i = 0; i < QUEUE_MAX; i++) {
    temp_arr[i] = queue->queue_memory[i];
    // printf(" %d ", temp_arr[i]);
  }
  // printf("\n");

  int temp_max = temp_arr[0];
  int temp_second_max = temp_max;
  int temp_min = temp_max;
  for (int i = 0; i < QUEUE_MAX - 1; i++) {
    if (temp_max < temp_arr[i + 1]) {
      temp_second_max = temp_max;
      temp_max = temp_arr[i + 1];
    }
  }
  /*
  for (i = 0; i < 5 - 1; i++) {
      for (j = 0; j < 5 - i - 1; j++)
          if (temp_arr[j] > temp_arr[j + 1]) {
              int temp = temp_arr[j];
              temp_arr[j] = temp_arr[j + 1];
              temp_arr[j + 1] = temp;
          }
  }
  */
  *max_value = temp_max;
  *min_value = temp_min;
  *second_max = temp_second_max;
}
