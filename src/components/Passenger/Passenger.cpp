#include "Passenger.h"

Passenger::
    Passenger() {}

Passenger::
    Passenger(std::string name, std::string destination): 
        _name{name}, _destination{destination} {}

Passenger::
    Passenger(std::string destination) : 
        _destination{ destination } 
    {
        std::string arrNames[] = {
            "Kostos pc",
            "Kostos mobile",
            "Fazber338",
            "KingGor",
            "Arthur Morgan",
            "Marakasy",
            "filosof",
            "KOT",
            "Solara",
            "Gendalf_grey",
            "VilkaLojka",
            "ReXeR",
            "Сотый",
            "Lonodo21",
            "LOR1XFN22",
            "Вампус",
            "SuperMax",
            "T.Vaskin",
        };

        int length = sizeof(arrNames) / sizeof(arrNames[0]);

        _name = arrNames[rand() % length];
    }

std::string Passenger::
    setName(std::string name)
    {
        std::string current = _name;
        _name               = name;

        return current;
    }

std::string Passenger:: 
    getName() const
    {
        return _name;
    }

std::string Passenger:: 
    setDestination(std::string destination)
    {   
        std::string current = _destination;
        _destination        = destination;

        return current;
    }

std::string Passenger::
    getDestination() const
    {
        return _destination;
    }

Passenger& Passenger::
    operator=(const Passenger& passenger)
    {
        if (&passenger == this)
        {
            return *this;
        }
        
        _name		 = passenger._name;
        _destination = passenger._destination;

        return *this;
    }

void Passenger::
    print(std::string shift, std::string number) const
    {
        std::cout << shift << number << (number == "" ? "" : ". ") << "Name: " << _name  << "\tDestination : " << _destination << std::endl;
    }

std::ostream& operator<<(std::ostream& out, const Passenger& passenger)
{
    passenger.print();

    return out;
}