#include "Model.h"

// ========== StoppingNode ==========

Model::StoppingNode::
    StoppingNode(
        const Stopping& stopping, 
        float averageTimePassengersAtDay,
        float averageTimePassengersAtNight, 
        float averageTimeBusesAtDay, 
        float averageTimeBusesAtNight
    ): 
        _stopping{stopping},
        _averageTimePassengersAtDay{ averageTimePassengersAtDay }, 
        _averageTimePassengersAtNight{ averageTimePassengersAtNight },
        _averageTimeBusesAtDay{ averageTimeBusesAtDay },
        _averageTimeBusesAtNight{ averageTimeBusesAtNight } 
    {}

bool Model::StoppingNode::
    _isTimeOut(const SYSTEMTIME& currentTimestamp, time_t& time, float comparer) const
    {
        time_t currentHours = (currentTimestamp.wDay * 24) + currentTimestamp.wHour;
        time_t currentMinutes = (currentHours * 60) + currentTimestamp.wMinute;
        time_t currentSeconds = (currentMinutes * 60) + currentTimestamp.wSecond;
        time_t currentMilliSeconds = (currentSeconds * 1000) + currentTimestamp.wMilliseconds;

        if (currentMilliSeconds - time > comparer * 1000)
        {
            time = currentMilliSeconds;
            return true;
        }

        return false;
    }

Stopping& Model::StoppingNode::
    getStopping()
    {
        return _stopping;
    }    

float Model::StoppingNode::
    getAverageTimePassengersAtDay() const
    {
        return _averageTimePassengersAtDay;
    }

float Model::StoppingNode::
    getAverageTimePassengersAtNight() const
    {
        return _averageTimePassengersAtNight;
    }

float Model::StoppingNode::
    getAverageTimeBusesAtDay() const
    {
        return _averageTimeBusesAtDay;
    }

float Model::StoppingNode::
    getAverageTimeBusesAtNight() const
    {
        return _averageTimeBusesAtNight;
    }

bool Model::StoppingNode::
    isTimeOutPassengersAtDay(const SYSTEMTIME& currentTimestamp)
    {
        return _isTimeOut(currentTimestamp, _milliSeconds1, _averageTimePassengersAtDay);
    }

bool Model::StoppingNode::
    isTimeOutPassengersAtNight(const SYSTEMTIME& currentTimestamp)
    {
        return _isTimeOut(currentTimestamp, _milliSeconds2, _averageTimePassengersAtNight);
    }

bool Model::StoppingNode::
    isTimeOutBusesAtDay(const SYSTEMTIME& currentTimestamp)
    {
        return _isTimeOut(currentTimestamp, _milliSeconds3, _averageTimeBusesAtDay);
    }

bool Model::StoppingNode::
    isTimeOutBusesAtNight(const SYSTEMTIME& currentTimestamp)
    {
        return _isTimeOut(currentTimestamp, _milliSeconds4, _averageTimeBusesAtNight);
    }

// ========== PassengerNode ==========

Model::PassengerNode::
    PassengerNode(const Passenger& passenger, std::string startPlace):
        _passenger{passenger}, _startPlace{startPlace} {}

Passenger& Model::PassengerNode::
    getPassenger()
    {
        return _passenger;
    }

std::string Model::PassengerNode::
    getStartPlace() const
    {
        return _startPlace;
    }

// ========== Model ==========

Model:: 
    Model() {}

int Model:: 
    _getStoppingIndexByName(std::string name) const
    {
        for (size_t i = 0; i < _stoppingNodes.getSize(); i++)
        {
            if (name == _stoppingNodes[i].getStopping().getName())
            {
                return i;
            }
        }

        return -1;
    }

int Model::
    _getPassengerIndexByStartPlace(std::string startPlace) const
    {
        for (size_t i = 0; i < _passengerNodes.getSize(); i++)
        {
            if (_passengerNodes[i].getStartPlace() == startPlace)
            {
                return i;
            }
        }

        return -1;
    }

Model& Model::
    addStopping(
        std::string name,
        float averageTimePassengersAtDay,
        float averageTimePassengersAtNight,
        float averageTimeBusesAtDay,
        float averageTimeBusesAtNight
    )
    {
        if (_getStoppingIndexByName(name) != -1)
        {
            throw "This stopping is already exists";
        }

        Stopping stopping(name);
        StoppingNode stoppingNode(stopping, averageTimePassengersAtDay, averageTimePassengersAtNight, averageTimeBusesAtDay, averageTimeBusesAtNight);

        _stoppingNodes.addBack(stoppingNode);

        return *this;
    }

Model& Model::
    addStopping(
        const Stopping& stopping,
        float averageTimePassengersAtDay,
        float averageTimePassengersAtNight,
        float averageTimeBusesAtDay,
        float averageTimeBusesAtNight
    )
    {
        if (_getStoppingIndexByName(stopping.getName()) != -1)
        {
            throw "This stopping is already exists";
        }

        StoppingNode stoppingNode(stopping, averageTimePassengersAtDay, averageTimePassengersAtNight, averageTimeBusesAtDay, averageTimeBusesAtNight);

        _stoppingNodes.addBack(stoppingNode);

        return *this;
    }

Model& Model::
    addPassenger(std::string startPlace, const Passenger& passenger)
    {

        if (_getStoppingIndexByName(startPlace) == -1)
        {
            throw "Incorrect Start Place";
        }

        if (_getStoppingIndexByName(passenger.getDestination()) == -1)
        {
            throw "Incorrect Start destination";
        }

        PassengerNode passengerNode(passenger, startPlace);

        _passengerNodes.addBack(passengerNode);

        return *this;
    }

Model& Model::
    simulate()
    {
        for (size_t i = 0; i < _stoppingNodes.getSize(); i++)
        {
            // Current Stopping
            Stopping* stopping = &_stoppingNodes[i].getStopping();

            // ----- 1 Condition -----
            int index = _getPassengerIndexByStartPlace(stopping->getName());

            if (index != -1)
            {
                stopping->addBackPassenger(_passengerNodes.deleteAt(index).getPassenger());
            }

            // ----- 2 Condition -----
            

            // ----- 3 Condition -----

            // ----- 4 Condition -----
        }

        return *this;
    }

void Model::
    printBuffers(std::string shift) const
    {
        std::cout << shift << "Buses Amount: " << _buses.getSize() << std::endl;
        
        std::cout << std::endl;
        std::cout << shift << "Buses: " << std::endl << std::endl;

        if (!_buses.isEmpty())
        {
            for (size_t i = 0; i < _buses.getSize(); i++)
            {
                std::cout << "\t" + shift << i + 1 << ". " << std::endl;

                _buses[i].print("\t\t" + shift);
            }
        }
        else
        {
            std::cout << std::endl;
            std::cout << shift << "\tNot buses" << std::endl;
        }

        std::cout << std::endl;
        std::cout << shift << "----------------------------" << std::endl;
        std::cout << std::endl;

        std::cout << shift << "Passsengers Amount: " << _passengerNodes.getSize() << std::endl;

        std::cout << std::endl;
        std::cout << shift << "Passengers: " << std::endl << std::endl;

        if (!_passengerNodes.isEmpty())
        {
            for (size_t i = 0; i < _passengerNodes.getSize(); i++)
            {
                std::cout << "\t" + shift << i + 1 << ". " << std::endl;

                _passengerNodes[i].getPassenger().print("\t\t" + shift);
        
                std::cout << std::endl;
            }
        }
        else
        {
            std::cout << std::endl;
            std::cout << shift << "\tNot passengers" << std::endl;
        }

        std::cout << std::endl;
    }

std::ostream& operator<<(std::ostream& out, const Model& model)
{
    out << "Buffers: " << std::endl << std::endl;
    model.printBuffers("\t");

    out << "==================================================" << std::endl;
    std::cout << std::endl;

    out << "Amount Stoppings: " << model._stoppingNodes.getSize() << std::endl << std::endl; 
    
    out << "Stoppings: " << std::endl;

    if (model._stoppingNodes.getSize() == 0)
    {
        std::cout << std::endl;
        std::cout << "\tNot Stoppings" << std::endl;
        std::cout << std::endl;
    }
    else
    {
        for (size_t i = 0; i < model._stoppingNodes.getSize(); i++)
        {
            std::cout << std::endl;
            out << "\t" << i + 1 << ". " << std::endl;

            out << "\t\tAverage Time Passengers At Day: "   << model._stoppingNodes[i].getAverageTimePassengersAtDay() << std::endl;
            out << "\t\tAverage Time Passengers At Night: " << model._stoppingNodes[i].getAverageTimePassengersAtNight() << std::endl;
            out << "\t\tAverage Time Buses At Day: "        << model._stoppingNodes[i].getAverageTimeBusesAtDay() << std::endl;
            out << "\t\tAverage Time Buses At Night: "	  << model._stoppingNodes[i].getAverageTimeBusesAtNight() << std::endl;

            out << std::endl;

            model._stoppingNodes[i].getStopping().print("\t\t");

            out << std::endl;
        }
    }
    out << std::endl;

    return out;
}