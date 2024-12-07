#include "classes/Model/Model.h"
#include "components/Passenger/Passenger.h"

#include <iostream>

int main(int argc, char** argv) 
{
    try
    {
        Model model;

        model.addStopping("Academy TOP", 0, 0, 0, 0);
        model.addStopping("DNS", 0, 0, 0, 0);

        model.addPassenger("Academy TOP", Passenger("DNS"));
        model.addPassenger("DNS", Passenger("Academy TOP"));

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