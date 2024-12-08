#pragma once

#ifndef __ROUTE_H__
#define __ROUTE_H__

#include "../../modules/DoubleLinkedList/DoubleLinkedList.h"

#include <iostream>
#include <initializer_list>
#include <string>

typedef unsigned int uint;

class Route
{
    private:
        DoubleLinkedList<std::string> _route;
        int                           _nextStoppingIndex;
        bool                          _stateRoute;

        bool addSetNextStopping();

        bool subSetNextStopping();

    public:
        Route();

        Route(const std::initializer_list<std::string>& list);

        Route(const Route& route);

        Route(Route&& route);

        Route& setNextStopping();

        int getNextStoppingIndex() const;

        uint getLength() const;

        Route& addBack(std::string name);

        std::string deleteBack();

        std::string setAt(uint index, std::string value);

        std::string getAt(uint index) const;

        Route& operator=(const Route& route);

        friend std::ostream& operator<<(std::ostream& out, const Route& route);
};

#include "Route.cpp"

#endif