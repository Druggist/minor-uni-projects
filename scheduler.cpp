#include "scheduler.h"

Scheduler::Scheduler(std::string path, unsigned short instanceNum) {
    this->parseFile(path, instanceNum);
}

bool Scheduler::parseFile(std::string path, unsigned short instanceNum) {
    std::ifstream file;

    file.open(path);
    if(!file.is_open()) return false;

    unsigned int instancesCount;
    file >> instancesCount;
    if(instanceNum >= instancesCount) return false;

    for(int i = 0; i < instanceNum; i++) {
        unsigned int currentTasksCount;
        file >> currentTasksCount;
        std::string tmp;
        getline(file, tmp);
        while(currentTasksCount > 0) {
            getline(file, tmp);
            currentTasksCount--;
        }
    }


    file >> this->tasksCount;

    for (int i = 0; i < this->tasksCount; i++) {
        Task task;

        file >> task.time;
        file >> task.earlyPenealty;
        file >> task.latePenealty;

        this->instance.push_back(task);
    }

    return true;
}

void Scheduler::printData() {
    std::cout<<this->tasksCount<<std::endl;
    for(Task& task : this->instance) {
        std::cout<< task.time<<"\t"<<task.earlyPenealty<<"\t"<<task.latePenealty<<std::endl;
    }

}
