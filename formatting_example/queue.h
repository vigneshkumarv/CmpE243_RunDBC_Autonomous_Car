// @file queue.h
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
  uint8_t queue_memory[100];
  uint8_t queue_beginning;
  uint8_t queue_end;
  uint8_t queue_num_items;
  uint8_t queue_is_initialized;

  // TODO: Add more members as needed
} queue_S;

void queue__init(queue_S *queue);

bool queue__push(queue_S *queue, uint8_t push_value);

bool queue__pop(queue_S *queue, uint8_t *pop_value);

size_t queue__get_count(queue_S *queue);
