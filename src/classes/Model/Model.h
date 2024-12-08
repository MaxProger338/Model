#pragma once

#ifndef __MODEL_H__
#define __MODEL_H__

#include "../../modules/DoubleLinkedList/DoubleLinkedList.h"

#include "../../components/Stopping/Stopping.h"
#include "../../components/Passenger/Passenger.h"
#include "../../components/Route/Route.h"
#include "../../components/Bus/Bus.h"

#include "Windows.h"
#include <iostream>
#include <string>

class Model
{
    private:
        class StoppingNode
        {
            private:
                Stopping _stopping;

                float _averageTimePassengersAtDay;
				float _averageTimePassengersAtNight;
				float _averageTimeBusesAtDay;
				float _averageTimeBusesAtNight;

				time_t _milliSeconds1 = 0;
				time_t _milliSeconds2 = 0;
				time_t _milliSeconds3 = 0;
				time_t _milliSeconds4 = 0;

                bool _isTimeOut(const SYSTEMTIME& currentTimestamp, time_t& time, float comparer) const;

            public:
                StoppingNode(
					const Stopping& stopping, 
					float averageTimePassengersAtDay,
					float averageTimePassengersAtNight, 
					float averageTimeBusesAtDay, 
					float averageTimeBusesAtNight
				);

                Stopping& getStopping(); 

                float getAverageTimePassengersAtDay() const;

                float getAverageTimePassengersAtNight() const;

                float getAverageTimeBusesAtDay() const;

                float getAverageTimeBusesAtNight() const;

                bool isTimeOutPassengersAtDay(const SYSTEMTIME& currentTimestamp);

                bool isTimeOutPassengersAtNight(const SYSTEMTIME& currentTimestamp);

                bool isTimeOutBusesAtDay(const SYSTEMTIME& currentTimestamp);

                bool isTimeOutBusesAtNight(const SYSTEMTIME& currentTimestamp);
        };

        class PassengerNode
        {
            private:
                Passenger   _passenger;
                std::string _startPlace;

            public:
                PassengerNode(const Passenger& passenger, std::string startPlace);

                Passenger& getPassenger();

                std::string getStartPlace() const;
        };

        DoubleLinkedList<StoppingNode>  _stoppingNodes;
		DoubleLinkedList<PassengerNode> _passengerNodes;
		DoubleLinkedList<Bus>           _buses;

        int _getStoppingIndexByName(std::string name) const;

        int _getPassengerIndexByStartPlace(std::string startPlace) const;

        int _getBusIndexByStoppingInRoute(std::string name) const;

        Bus _getOffPassengers(const Bus& bus, Stopping* stopping) const;

        Bus _getOnPassengers(const Bus& bus, Stopping* stopping) const;

        bool _isExistsStoppingInRoute(std::string stoppingName, const Route& route) const;

        bool addPassengerToStopping(Stopping* stopping);

        bool addBusToStopping(Stopping* stopping);

    public:
        Model();

        Model& addStopping(
			std::string name,
			float averageTimePassengersAtDay,
			float averageTimePassengersAtNight,
			float averageTimeBusesAtDay,
			float averageTimeBusesAtNight
		);

        Model& addStopping(
			const Stopping& stopping,
			float averageTimePassengersAtDay,
			float averageTimePassengersAtNight,
			float averageTimeBusesAtDay,
			float averageTimeBusesAtNight
		);

        Model& addPassenger(std::string startPlace, const Passenger& passenger);

        Model& addBus(const Bus& bus);

        Model& simulate(const SYSTEMTIME& timestamp);

        void printBuffers(std::string shift = "") const;

        friend std::ostream& operator<<(std::ostream& out, const Model& model);
};

#include "Model.cpp"

#endif