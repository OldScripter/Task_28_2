#ifndef TASK_28_2_TRAIN_H
#define TASK_28_2_TRAIN_H

#include <iostream>
#include <thread>
#include "Station.h"

class Train {

private:
    std::string name;
    double travelTime {0};

public:
    Train(std::string name, double travelTime);
    std::string getName();

    /**
     * @method Start the way to the station during travel time.
     * @param [in/out] station*
     */
    void go(class Station* station);

};

#endif //TASK_28_2_TRAIN_H