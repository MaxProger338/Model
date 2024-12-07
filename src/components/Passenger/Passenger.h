#pragma once

#ifndef __PASSENGER_H__
#define __PASSENGER_H__

#include <iostream>
#include <string>

class Passenger
{
    private:
        std::string _name;
        std::string _destination;

    public:
        Passenger();

        Passenger(std::string name, std::string destination);

        Passenger(std::string destination);

        std::string setName(std::string name);

        std::string getName() const;

        std::string setDestination(std::string destination);

        std::string getDestination() const;

        Passenger& operator=(const Passenger& passenger);

        void print(std::string shift = "", std::string number = "") const;

        friend std::ostream& operator<<(std::ostream&, const Passenger& passenger);
};

#include "Passenger.cpp"

#endif 