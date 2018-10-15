#include <string>
#include <iostream>
#include <vector>
#include <fstream>

struct Task {
	unsigned int time;
	unsigned int earlyPenealty;
	unsigned int latePenealty;
};

class Scheduler {
public:
	Scheduler(std::string path, unsigned short instanceNum);
	~Scheduler();

	void printData();

private:
	unsigned int tasksCount;
	std::vector<Task> instance;

	bool parseFile(std::string path, unsigned short instanceNum);
};