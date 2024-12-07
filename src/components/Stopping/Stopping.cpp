#include "Stopping.h"

Stopping::
    Stopping(std::string name) : _name{ name } {}

std::string Stopping::
    getName() const
    {
        return _name;
    }

Stopping& Stopping::
    enqueueBus(const Bus& bus)
    {
        _buses.enqueue(bus);

        return *this;
    }

Bus Stopping::
    dequeueBus()
    {
        return _buses.dequeue();
    }

Bus Stopping::
    peekBus() const
    {
        return _buses.peek();
    }

uint Stopping::
    getAmountPassengers() const
    {
        return _passengers.getSize();
    }

Stopping& Stopping::
    addBackPassenger(const Passenger& passenger)
    {
        _passengers.addBack(passenger);

        return *this;
    }

Passenger Stopping::
    deleteBackPassenger()
    {
        return _passengers.deleteBack();
    }

Stopping& Stopping::
    addForwardPassenger(const Passenger& passenger)
    {
        _passengers.addForward(passenger);

        return *this;
    }

Passenger Stopping::
    deleteForwardPassenger()
    {
        return _passengers.deleteForward();
    }

Passenger Stopping::
    deletePassengerAt(uint index)
    {
        return _passengers(index);
    }

Passenger Stopping::
    setPassengerAt(uint index, const Passenger& passenger)
    {
        if (index >= _passengers.getSize())
        {
            throw "Out of range";
        }

        return _passengers(index, passenger);
    }


Passenger Stopping::
    getPassengerAt(uint index) const
    {
        if (index >= _passengers.getSize())
        {
            throw "Out of range";
        }

        return _passengers[index];
    }

Stopping& Stopping::
    insertPassengerAt(uint index, const Passenger& passenger)
    {
        if (index >= _passengers.getSize())
        {
            throw "Out of range";
        }

        _passengers.insertAt(index, passenger);

        return *this;
    }


Stopping& Stopping::
    print(std::string shift)
    {
        std::cout << shift << "Stopping Name: " << _name << std::endl << std::endl;

        std::cout << shift << "Bus Amount: " << _buses.getSize() << std::endl;
        std::cout << shift << "Last Bus: " << std::endl << std::endl;

        if (!_buses.isEmpty())
        {
            _buses.peek().print("\t" + shift);
        } 
        else
        {
            std::cout << shift << "\tNot buses" << std::endl;
        }

        std::cout << std::endl << std::endl;

        std::cout << shift << "Passengers Amount: " << _passengers.getSize() << std::endl;

        std::cout << shift << "Passengers: " << std::endl << std::endl;

        if (!_passengers.isEmpty())
        {
            for (size_t i = 0; i < _passengers.getSize(); i++)
            {
                _passengers[i].print("\t" + shift, std::to_string(i + 1));

                std::cout << std::endl;
            }
        }
        else
        {
            std::cout << shift << "\tNot passengers" << std::endl;
        }

        return *this;
    }