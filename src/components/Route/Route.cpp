#include "Route.h"

Route::
    Route() {}

Route::
    Route(const std::initializer_list<std::string>& list):
        _route{ list } {}

Route::
    Route(const Route& route): 
        _route{ route._route } {}

Route::
    Route(Route&& route) : 
        _route{ std::move(route._route) } {}

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

        _route = route._route;

        return *this;
    }

std::ostream& operator<<(std::ostream& out, const Route& route)
{
    out << route._route << '\t' << std::endl;

    return out;
}