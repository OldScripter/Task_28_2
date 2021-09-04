#include "../include/Station.h"

Station::Station(std::mutex* stationAccess)
{
    this->stationAccess = stationAccess;
    this->trainOnStation = nullptr;
    std::cout << "Station is created.\n";
    stationAccess->unlock();
    std::cout   << "\t - Station: Way is free.\n";
}

void Station::setTrainOnStation(Train *train)
{
    stationAccess->lock();
    this->trainOnStation = train;
    std::cout   << "\t - Station: Train "
                << train->getName()
                << " is arrived on station.\n";


    std::cout   << "\t - Station: Way is busy.\n";

    std::string command;
    do
    {
        std::cout << "Station: enter the command [depart]: ";
        std::getline(std::cin, command);
        if (command == "depart" && trainOnStation != nullptr)
        {
            unlockStation();
        }
        else
        {
            std::cerr << "Unknown command. Try again.\n";
        }
    } while (command != "depart");
}

void Station::unlockStation()
{
    std::cout   << "\t - Station: Train "
                << trainOnStation->getName()
                << " had departed from station.\n";

    this->trainOnStation = nullptr;
    std::cout   << "\t - Station: Way is free.\n";
    stationAccess->unlock();
}