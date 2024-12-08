#include "classes/Model/Model.h"
#include "components/Passenger/Passenger.h"
#include "components/Route/Route.h"
#include "components/Stopping/Stopping.h"

#include <iostream>

int main(int argc, char** argv) 
{
    try
    {
        Model model;

        Stopping stopping1("Academy TOP");
        stopping1.addBackPassenger(Passenger("Marakasy", "House"));

        Stopping stopping2("KYLIBACA");
        stopping2.addBackPassenger(Passenger("Arthur Morgan", "Academy TOP"));
        stopping2.addBackPassenger(Passenger("K1ngG0r", "House"));

        Stopping stopping3("House");
        stopping3.addBackPassenger(Passenger("Fazber", "KYLIBACA"));
        stopping3.addBackPassenger(Passenger("filosof", "KYLIBACA"));
        stopping3.addBackPassenger(Passenger("kostos", "Academy TOP"));

        model.addStopping(stopping1, 1, 2, 4, 8);
        model.addStopping(stopping2, 1, 2, 4, 8);
        model.addStopping(stopping3, 1, 2, 4, 8);

        model.addBus(Bus("108", 30, Route{"Academy TOP", "KYLIBACA"}, {Passenger("SKUF", "KYLIBACA")}));
        model.addBus(Bus("41", 10, Route{"House", "KYLIBACA", "Academy TOP"}, {}));

        while (1)
        {
        	SYSTEMTIME timestamp;
        	GetLocalTime(&timestamp);

        	model.simulate(timestamp);

        	static time_t time         = 0;
        	time_t currentHours        = (timestamp.wDay * 24)   + timestamp.wHour;
        	time_t currentMinutes      = (currentHours * 60)     + timestamp.wMinute;
        	time_t currentSeconds      = (currentMinutes * 60)   + timestamp.wSecond;
        	time_t currentMilliSeconds = (currentSeconds * 1000) + timestamp.wMilliseconds;
 
        	if (currentMilliSeconds - time > 1000)
        	{
        		time = currentMilliSeconds;
        		std::cout << model << std::endl;
            }
        }
    }
    catch (const char* str)
    {
        std::cout << "Error: " << str << std::endl;
    }
    catch (...)
    {
        std::cout << "FUCK YOU!!! (said by MEMORY)" << std::endl; 
    }

    return 0;
}