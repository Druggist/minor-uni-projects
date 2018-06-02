#include <pthread.h>
#include <vector>

#define CANALS_COUNT 5
#define CANALS_CAPACITY_MIN 1
#define CANALS_CAPACITY_MAX 5
#define CANALS_TIME_MIN 1
#define CANALS_TIME_MAX 5

#define ROOT 0
#define OK_TAG 11
#define MSG_TAG 22

#define REQ_MSG 100
#define REL_MSG 200
#define OK_MSG 300

typedef struct Ships {
	int shipId;
	int timestamp;
} Ship;

typedef struct Canals {
	std::vector<Ship> queue;
	int capacity;
	int direction;
} Canal;

typedef struct Message {
	int shipId;
	int canalId;
	int direction;
	int timestamp;
	int type;
} Msg;

typedef struct threadParams{
  pthread_mutex_t *mutexCanals;
  pthread_cond_t *changeCondition;
  int tid;
  int shipsCount;
  int *clock;
  Canal *canals;
  bool* isRunning;
  bool* allQueued;
} ThreadParams;