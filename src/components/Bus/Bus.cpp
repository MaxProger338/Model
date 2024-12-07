#include "Bus.h"

Bus::
    Bus(std::string name, uint maxAmountPassengers, const Route& route, const std::initializer_list<const Passenger>& list):
        _name{ name }, _maxAmountPassengers{ maxAmountPassengers }
    {
        if (maxAmountPassengers < list.size())
        {
            throw "Out of range";
        }

        if (route.getLength() == 0)
        {
            throw "Out of range";
        }

        for (auto i : list)
        {
            _passengers.addBack(i);
        }

        _route = route;
    }

Bus::
    Bus(std::string name, uint maxAmountPassengers, uint currentAmountPassengers, const Route& route, const Passenger* passengers):
        _name{ name }, _maxAmountPassengers{ maxAmountPassengers }
    {
        if (currentAmountPassengers > maxAmountPassengers)
        {
            throw "Out of range";
        }

        if (route.getLength() == 0)
        {
            throw "Out of range";
        }

        for (size_t i = 0; i < currentAmountPassengers; i++)
        {
            _passengers.addBack(passengers[i]);
        }

        _route = route;
    }

Bus::
    Bus(const Bus& bus): 
        _name{ bus._name }, _maxAmountPassengers { bus._maxAmountPassengers }, 
        _route{ bus._route }, _passengers{ bus._passengers } {}

Bus::
    Bus(Bus&& bus):
        _name{ bus._name }, _maxAmountPassengers{ bus._maxAmountPassengers }, 
        _route{ bus._route }, _passengers{ std::move(bus._passengers) } {}

std::string Bus::
    getName() const
    {
        return _name;
    }

uint Bus::
    getCurrentAmountPassengers() const
    {
        return _passengers.getSize();
    }

uint Bus::
    getMaxAmountPassengers() const
    {
        return _maxAmountPassengers;
    }

Route Bus::
    setRoute(const Route& route)
    {
        Route current = _route;

        _route = route;

        return current;
    }

Route Bus::
    getRoute() const
    {
        return _route;
    }

Passenger Bus::
    setPassengerAt(uint index, const Passenger& passenger)
    {
        if (index >= _passengers.getSize())
        {
            throw "Out of range";
        }

        return _passengers(index, passenger);
    }

Passenger Bus::
    getPassengerAt(uint index) const
    {
        if (index >= _passengers.getSize())
        {
            throw "Out of range";
        }

        return _passengers[index];
    }

Bus& Bus::
    addBackPassenger(const Passenger& passenger)
    {
        if (_passengers.getSize() + 1 > _maxAmountPassengers)
        {
            throw "Out of range";
        }

        _passengers.addBack(passenger);

        return *this;
    }

Passenger Bus::
    deleteBackPassenger()
    {
        return _passengers.deleteBack();
    }

Bus& Bus::
    addForwardPassenger(const Passenger& passenger)
    {
        if (_passengers.getSize() + 1 > _maxAmountPassengers)
        {
            throw "Out of range";
        }

        _passengers.addForward(passenger);

        return *this;
    }

Passenger Bus::
    deleteForwardPassenger()
    {
        return _passengers.deleteForward();
    }

Bus& Bus::
    insertPassengerAt(uint index, const Passenger& passenger)
    {
        if (_passengers.getSize() + 1 > _maxAmountPassengers)
        {
            throw "Out of range";
        }

        if (index >= _passengers.getSize())
        {
            throw "Out of range";
        }

        _passengers.insertAt(index, passenger);

        return *this;
    }

Passenger Bus::
    deletePassengerAt(uint index)
    {
        if (index >= _passengers.getSize())
        {
            throw "Out of range";
        }

        return _passengers(index);
    }

Bus& Bus::
    clearPassengers()
    {
        _passengers.clear();

        return *this;
    }

Bus& Bus::
    print(std::string shift)
    {
        std::cout << shift << "Name: "					    << _name << std::endl;
        std::cout << shift << "Current Amount Passengers: " << _passengers.getSize() << std::endl;
        std::cout << shift << "Max Amount Passengers: "	    << _maxAmountPassengers << std::endl;

        std::cout << std::endl << shift << "Passengers: "   << std::endl << std::endl;

        for (size_t i = 0; i < _passengers.getSize(); i++)
        {
            _passengers[i].print("\t" + shift, std::to_string(i + 1));

            std::cout << std::endl;
        }

        std::cout << shift << "Route: " << std::endl << std::endl;
        std::cout << shift << "\t"      << _route << std::endl;

        return *this;
    }
