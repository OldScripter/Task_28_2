#ifndef TASK_28_2_STATION_H
#define TASK_28_2_STATION_H

#include "Train.h"
#include <iostream>
#include <mutex>

class Station {

private:
    class Train* trainOnStation {nullptr};
    std::mutex* stationAccess;

public:
    Station(std::mutex* stationAccess);
    void setTrainOnStation(Train* train);

    /**
     * @method Unlock the station access mutex. Set the trainOnWays to nullptr.
     */
    void unlockStation();

};

#endif //TASK_28_2_STATION_H