#pragma once

#ifndef __BUS_H__
#define __BUS_H__

#include "../Route/Route.h"
#include "../Passenger/Passenger.h"
#include "../../modules/DoubleLinkedList/DoubleLinkedList.h"

#include <iostream>
#include <initializer_list>
#include <string>

typedef unsigned int uint;

class Bus
{
    private:
        std::string                 _name;
        uint                        _maxAmountPassengers;

        Route                       _route;
        DoubleLinkedList<Passenger> _passengers;

    public:
        Bus(std::string name, uint maxAmountPassengers, const Route& route, const std::initializer_list<const Passenger>& list);

        Bus(std::string name, uint maxAmountPassengers, uint currentAmountPassengers, const Route& route, const Passenger* passengers);

        Bus(const Bus& bus);

        Bus(Bus&& bus);

        std::string getName() const;

        uint getCurrentAmountPassengers() const;

        uint getMaxAmountPassengers() const;

        Route setRoute(const Route& route);

        Route getRoute() const;

        Passenger setPassengerAt(uint index, const Passenger& passenger);

        Passenger getPassengerAt(uint index) const;

        Bus& addBackPassenger(const Passenger& passenger);

        Passenger deleteBackPassenger();

        Bus& addForwardPassenger(const Passenger& passenger);

        Passenger deleteForwardPassenger();

        Bus& insertPassengerAt(uint index, const Passenger& passenger);

        Passenger deletePassengerAt(uint index);

        Bus& clearPassengers();

        Bus& print(std::string shift = "");
};

#include "Bus.cpp"

#endif