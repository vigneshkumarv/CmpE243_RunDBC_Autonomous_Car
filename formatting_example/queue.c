#include "queue.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

void queue__init(queue_S *queue) {
  memset(queue->queue_memory, 0, sizeof(queue->queue_memory));
  queue->queue_beginning = 0;
  queue->queue_end = 0;
  queue->queue_num_items = 0;
  queue->queue_is_initialized = true;
}

bool queue__push(queue_S *queue, uint8_t push_value) {
  bool has_space = false;
  bool is_init = queue->queue_is_initialized;
  if (queue->queue_num_items < sizeof(queue->queue_memory)) {
    queue->queue_memory[queue->queue_end] = push_value;
    if ((sizeof(queue->queue_memory) - 1) == queue->queue_end) {
      queue->queue_end = 0;
    } else {
      queue->queue_end++;
    }
    queue->queue_num_items++;
    has_space = true;
  }
  return is_init && has_space;
}

bool queue__pop(queue_S *queue, uint8_t *pop_value) {
  bool has_items = false;
  bool is_init = queue->queue_is_initialized;
  if (queue->queue_num_items) {
    *pop_value = queue->queue_memory[queue->queue_beginning];
    if ((sizeof(queue->queue_memory) - 1) == queue->queue_beginning) {
      queue->queue_beginning = 0;
    } else {
      queue->queue_beginning++;
    }
    queue->queue_num_items--;
    has_items = true;
  }
  return is_init && has_items;
}

size_t queue__get_count(queue_S *queue) { return queue->queue_is_initialized ? queue->queue_num_items : 0; }
