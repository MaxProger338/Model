#pragma once

#ifndef __MODEL_H__
#define __MODEL_H__

#include "../../modules/DoubleLinkedList/DoubleLinkedList.h"

#include "../../components/Stopping/Stopping.h"
#include "../../components/Passenger/Passenger.h"
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

				time_t _milliSeconds1;
				time_t _milliSeconds2;
				time_t _milliSeconds3;
				time_t _milliSeconds4;

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

        Model& simulate();

        void printBuffers(std::string shift = "") const;

        friend std::ostream& operator<<(std::ostream& out, const Model& model);
};

#include "Model.cpp"

#endif