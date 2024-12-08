#pragma once

#ifndef __STOPPING_H__
#define __STOPPING_H__

#include "../../modules/DoubleLinkedList/DoubleLinkedList.h"
#include "../../modules/DynamicQueue/DynamicQueue.h"

#include "../Bus/Bus.h"
#include "../Passenger/Passenger.h"

#include <iostream>
#include <string>

class Stopping
{
    private:
        std::string _name;

        DynamicQueue<Bus> _buses;
		DoubleLinkedList<Passenger> _passengers;

    public:
        Stopping(std::string name);

        std::string getName() const;

        Stopping& enqueueBus(const Bus& bus);

        Bus dequeueBus();

        Bus peekBus() const;

        uint getAmountPassengers() const;

        Stopping& addBackPassenger(const Passenger& passenger);

        Passenger deleteBackPassenger();

        Stopping& addForwardPassenger(const Passenger& passenger);

        Passenger deleteForwardPassenger();

        Passenger deletePassengerAt(uint index);

        Passenger setPassengerAt(uint index, const Passenger& passenger);

        Passenger getPassengerAt(uint index) const;

        Stopping& insertPassengerAt(uint index, const Passenger& passenger);

        Stopping& print(std::string shift = "");

        Stopping& operator=(const Stopping& src);
};

#include "Stopping.cpp"

#endif 