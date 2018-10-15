#include "scheduler.h"

int main() {
	Scheduler *scheduler = new Scheduler("../data/sch10.txt", 9);

	scheduler->printData();
	return 0;
}