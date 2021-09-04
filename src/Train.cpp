#include "../include/Train.h"

Train::Train(std::string name, double travelTime)
{
    this->name = std::move(name);
    this->travelTime = travelTime;
    std::cout << "Train " << this->name << " is created.\n";
}

void Train::go(Station* station)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(int(travelTime * 1000)));
    station->setTrainOnStation(this);
}

std::string Train::getName() {
    return this->name;
}