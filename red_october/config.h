#include <pthread.h>
#include <vector>

#define CANALS_COUNT 5
#define CANALS_CAPACITY_MIN 1
#define CANALS_CAPACITY_MAX 5

#define ROOT 0

typedef struct Queues {
  int shipId;
  int timestamp;
} Queue;

typedef struct Canals {
  std::vector<Queue> queue;
  int capacity;
  int direction;
} Canal;