#include <iostream>
#include <mutex>
#include <list>
#include "include/Train.h"

//==========    Global      ==========

std::mutex stationAccess;
const int TRAIN_COUNT = 3;

//==========    Functions   ==========

/**
 * @function Run "go" method for pointed train. Convenient to use in separate thread.
 * @param [in/out] train
 * @param [in/out] station
 */
void launchTrain(Train* train, Station* station)
{
    train->go(station);
}

/**
 * @function Get the double value from input.
 * @param [in] label std::string
 * @param [in] min double Minimal value (including)
 * @param [in] max double Maximal value (including)
 * @return double
 */
double getDoubleFromCin(std::string label, double min, double max)
{
    do
    {
        double result{-1};
        std::cout << label;
        std::cout << "\t - minimal = " << min << "\n";
        std::cout << "\t - maximal = " << max << "\n";
        std::string buffer;
        std::getline(std::cin, buffer);
        try
        {
            result = std::stod(buffer);
            if (result < min || result > max)
            {
                throw -1;
            }
            return result;
        }
        catch (int)
        {
            std::cerr << "Value is not between min and max. Try again.\n";
        }
        catch (...)
        {
            std::cerr << "Double value input error. Try again.\n";
        }
    } while(true);
}

int main() {

    //Create station:
    Station* station = new Station(&stationAccess);

    //Create Trains:
    std::list<Train*> trains;
    for (int i = 0; i < TRAIN_COUNT; ++i)
    {
        std::cout << "Please enter the train name for train #" << i + 1 << ":\n";
        std::string trainName;
        std::getline(std::cin, trainName);
        double travelTime = getDoubleFromCin("Please enter the travel time for train #" + std::to_string(i + 1) + ":\n", 1, 20);
        Train* train = new Train(trainName, travelTime);
        trains.push_back(train);
    }

    //Launch trains:
    std::cout << "---=== Trains are launched! ===---\n";
    std::list<std::thread*> trainWays;
    for (Train* train : trains)
    {
        std::thread* trainWay = new std::thread(launchTrain, train, station);
        trainWays.push_back(trainWay);
    }

    //Thread join:
    for (std::thread* t : trainWays)
    {
        if (t->joinable()) t->join();
    }

    std::cout << "---=== All trains were departed from station! ===---\n";

    return 0;
}