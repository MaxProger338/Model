#include "Route.h"

Route::
    Route(): Route({}) {}

Route::
    Route(const std::initializer_list<std::string>& list):
        _route{ list }, _stateRoute{ false }
    {
        if (list.size() == 0)
        {
            _nextStoppingIndex = -1;
        }
        else
        {
            _nextStoppingIndex = 0;
        }
    }

Route::
    Route(const Route& route): 
        _route{ route._route },
        _nextStoppingIndex{ route._nextStoppingIndex },
        _stateRoute{ route._stateRoute } {}

Route::
    Route(Route&& route) : 
        _route{ std::move(route._route) },
        _nextStoppingIndex{ route._nextStoppingIndex }, 
        _stateRoute{ route._stateRoute } {}

bool Route::
    addSetNextStopping()
    {
        if (_nextStoppingIndex < _route.getSize() - 1)
        {
            _nextStoppingIndex++;

            return true;
        }

        return false;
    }

bool Route::
    subSetNextStopping()
    {   
        if (_nextStoppingIndex > 0)
        {
            _nextStoppingIndex--;

            return true;
        }

        return false;
    }

Route& Route::
    setNextStopping()
    {
        if (!_stateRoute)
        {
            if (!addSetNextStopping())
            {
                _stateRoute = true;
                subSetNextStopping();
            }
        }

        else
        {
            if (!subSetNextStopping())
            {
                _stateRoute = false;
                addSetNextStopping();
            }
        }

        return *this;
    }

int Route::
    getNextStoppingIndex() const
    {
        return _nextStoppingIndex;
    }

uint Route::
    getLength() const
    {
        return _route.getSize();
    }

Route& Route::
    addBack(std::string name)
    {
        _route.addBack(name);

        return *this;
    }

std::string Route::
    deleteBack()
    {
        return _route.deleteBack();
    }

std::string Route::
    setAt(uint index, std::string value)
    {
        return _route(index, value);
    }

std::string Route::
    getAt(uint index) const
    {
        return _route[index];
    }

Route& Route::
    operator=(const Route& route)
    {
        if (&route == this)
        {
            return *this;
        }

        _route             = route._route;
        _nextStoppingIndex = route._nextStoppingIndex;
        _stateRoute        = route._stateRoute;

        return *this;
    }

std::ostream& operator<<(std::ostream& out, const Route& route)
{
    out << route._route << '\t' << std::endl;

    return out;
}