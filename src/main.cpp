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

        model.addStopping(stopping1, 0, 0, 0, 0);
        model.addStopping(stopping2, 0, 0, 0, 0);
        model.addStopping(stopping3, 0, 0, 0, 0);

        model.addBus(Bus("108", 30, Route{"Academy TOP", "KYLIBACA"}, {Passenger("SKUF", "KYLIBACA")}));
        model.addBus(Bus("41", 10, Route{"House", "KYLIBACA", "Academy TOP"}, {}));

        model.simulate();
        model.simulate();
        model.simulate();
        model.simulate();

        std::cout << model << std::endl;
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