#include <iostream>
#include <initializer_list>
#include <string>
#include <Windows.h>
using namespace std;

typedef unsigned int uint;

template<typename T>
class DoubleLinkedList
{
	private:
		class Node
		{
			public:
				T value;
				Node* next;
				Node* prev;

				Node(const T& value) : value{ value }, next{ nullptr }, prev{ nullptr } {}
		};

		Node* _first;
		Node* _last;

		Node* getNodeByIndex(uint index) const
			{
				uint size = getSize();
				if (index >= size)
					throw "Out of range";

				Node* current = nullptr;
				if (index <= (uint)size / 2)
				{
					current = _first;
					for (size_t i = 0; i < index; i++)
					{
						current = current->next;
					}
				}
				else
				{
					current = _last;
					for (size_t i = 0; i < size - index - 1; i++)
					{
						current = _last->prev;
					}
				}

				return current;
		}

	public:
		DoubleLinkedList() : _first{ nullptr }, _last{ nullptr } {}

		DoubleLinkedList(const initializer_list<T>& list) : DoubleLinkedList()
		{
			for (auto i : list)
			{
				addBack(i);
			}
		}

		DoubleLinkedList(const DoubleLinkedList& list) : DoubleLinkedList()
		{
			Node* current = list._first;

			while (current)
			{
				addBack(current->value);
				current = current->next;
			}
		}

		DoubleLinkedList(DoubleLinkedList&& list)
		{
			Node* current = list._first;
			_first = current;
			_last = list._last;

			while (current)
			{
				_first->next = current->next;
				_first->prev = current->prev;
				_first = _first->next;

				current = current->next;
			}
			_first = list._first;

			list._first = nullptr;
			list._last = nullptr;
		}

		~DoubleLinkedList()
		{
			if (!isEmpty())
			{
				Node* current = _first->next;
				while (current)
				{
					delete _first;
					_first = current;
					current = current->next;
				}

				delete _first;

				_first = nullptr;
				_last = nullptr;
			}
		}

		bool isEmpty() const
		{
			return _first == nullptr;
		}

		uint getSize() const
		{
			uint counter = 0;

			Node* current = _first;
			while (current)
			{
				counter++;
				current = current->next;
			}

			return counter;
		}

		DoubleLinkedList& clear()
		{
			this->~DoubleLinkedList();

			return *this;
		}

		T getLast() const
		{
			return _last->value;
		}

		T getFirst() const
		{
			return _first->value;
		}

		T getByIndex(uint index) const
		{
			return getNodeByIndex(index)->value;
		}

		T setByIndex(uint index, const T& value)
		{
			Node* node = getNodeByIndex(index);
			T current = node->value;

			node->value = value;

			return current;
		}

		T deleteByIndex(uint index)
		{
			if (index >= getSize())
				throw "Out of range";

			T value;

			if (index == 0)
				value = deleteForward();

			else if (index == getSize() - 1)
				value = deleteBack();

			else
			{
				Node* node = getNodeByIndex(index);
				value = node->value;

				node->prev->next = node->next;
				node->next->prev = node->prev;

				delete node;
			}

			return value;
		}

		DoubleLinkedList& insertByIndex(uint index, const T& value)
		{
			if (index >= getSize())
				throw "Out of range";

			if (index == 0)
				addForward(value);

			else if (index == getSize() - 1)
			{
				Node* node = getNodeByIndex(index);

				addBack(_last->value);

				node->value = value;
			}

			else
			{
				Node* newNode = new Node(value);
				Node* nodeDist = getNodeByIndex(index);

				nodeDist->prev->next = newNode;
				newNode->next = nodeDist;

				newNode->prev = nodeDist->prev;
				nodeDist->prev = newNode;
			}
		}

		DoubleLinkedList& addBack(const T& value)
		{
			Node* node = new Node(value);

			if (isEmpty())
			{
				_first = node;
				_last = node;
			}
			else
			{
				_last->next = node;
				node->prev = _last;
				_last = node;
			}

			return *this;
		}

		DoubleLinkedList& addForward(const T& value)
		{
			Node* node = new Node(value);
			if (isEmpty())
			{
				_first = node;
				_last = node;
			}
			else
			{
				node->next = _first;
				_first->prev = node;
				_first = node;
			}

			return *this;
		}

		T deleteBack()
		{
			if (isEmpty())
				throw "Out of range";

			Node* current = _last;
			T value = current->value;

			if (getSize() > 1)
			{
				_last = current->prev;
				_last->next = nullptr;
			}
			else
			{
				_last  = nullptr;
				_first = nullptr;
			}

			delete current;

			return value;
		}

		T deleteForward()
		{
			if (isEmpty())
				throw "Out of range";

			Node* current = _first;
			T value = current->value;

			if (getSize() > 1)
			{
				_first = current->next;
				_first->prev = nullptr;
			}
			else
			{
				_first = nullptr;
				_last  = nullptr;
			}

			delete current;

			return value;
		}

		T& operator[](uint index) const
		{
			return getNodeByIndex(index)->value;
		}

		uint operator()() const
		{
			return getSize();
		}

		T operator()(uint index)
		{
			return deleteByIndex(index);
		}

		T operator()(uint index, const T& value)
		{
			return setByIndex(index, value);
		}

		DoubleLinkedList& operator=(const DoubleLinkedList& list)
		{
			if (&list == this)
				return *this;

			this->~DoubleLinkedList();

			Node* current = list._first;

			while (current)
			{
				addBack(current->value);
				current = current->next;
			}

			return *this;
		}

		friend ostream& operator<<(ostream& out, const DoubleLinkedList& list)
		{
			Node* current = list._first;
			while (current)
			{
				out << current->value << '\t';
				current = current->next;
			}
			out << endl;

			return out;
		}
};

template <typename T>
class DynamicQueue
{
	private:
		DoubleLinkedList<T> _list;

	public:
		DynamicQueue() {}

		explicit DynamicQueue(initializer_list<T> list) : _list{ list } {}

		DynamicQueue(const DynamicQueue& stack) : _list{ stack._list } {}

		DynamicQueue(DynamicQueue&& stack) : _list{ move(stack._list) } {}

		bool isEmpty() const
		{
			return _list.isEmpty();
		}

		uint getSize() const
		{
			return _list.getSize();
		}

		DynamicQueue& clear()
		{
			_list.clear();

			return *this;
		}

		DynamicQueue& enqueue(const T& value)
		{
			_list.addBack(value);

			return *this;
		}

		T dequeue()
		{
			return _list.deleteForward();
		}

		T peek() const
		{
			return _list.getFirst();
		}

		friend ostream& operator<<(ostream& out, const DynamicQueue& queue)
		{
			out << queue._list << endl;

			return out;
		}
};

class Route
{
	private:
		DoubleLinkedList<string> _route;

	public:
		Route() {}

		Route(const initializer_list<string>& list) : _route{ list } {}

		Route(const Route& route): _route{ route._route } {}

		Route(Route&& route) : _route{ move(route._route) } {}

		uint getLength() const
		{
			return _route.getSize();
		}

		Route& addBack(string name)
		{
			_route.addBack(name);

			return *this;
		}

		string deleteBack()
		{
			return _route.deleteBack();
		}

		string setAt(uint index, string value)
		{
			return _route(index, value);
		}

		string getAt(uint index) const
		{
			return _route[index];
		}

		Route& operator=(const Route& route)
		{
			if (&route == this)
				return *this;

			_route = route._route;

			return *this;
		}

		friend ostream& operator<<(ostream& out, const Route& route)
		{
			out << route._route << '\t' << endl;

			return out;
		}
};

class Passenger
{
	private:
		string _name;
		string _destination;

	public:
		Passenger() {}

		Passenger(string name, string destination): _name{name}, _destination{destination} {}

		string setName(string name)
		{ 
			string current = _name;
			_name = name;

			return current;
		}

		string setDestination(string destination)
		{
			string current = _destination;
			_destination = destination;

			return current;
		}

		string getName() const
		{
			return _name;
		}

		string getDestination() const
		{
			return _destination;
		}

		Passenger& operator=(const Passenger& passenger)
		{
			if (&passenger == this)
				return *this;
			
			_name		 = passenger._name;
			_destination = passenger._destination;

			return *this;
		}

		Passenger& print(string shift = "", string number = "")
		{
			cout << shift << number << (number == "" ? "" : ". ") << "Name: " << _name  << "\tDestination : " << _destination << endl;

			return *this;
		}
};

class Bus
{
	private:
		string     _name;
		uint	   _maxAmountPassengers;
		Route      _route;

		DoubleLinkedList<Passenger> _passengers;

	public:
		Bus() {}

		Bus(string name, uint maxAmountPassengers, const Route& route, const initializer_list<const Passenger>& list) :
			_name{ name }, _maxAmountPassengers{ maxAmountPassengers }
		{
			if (maxAmountPassengers < list.size())
				throw "Out of range";

			if (route.getLength() == 0)
				throw "Out of range";

			for (auto i : list)
			{
				_passengers.addBack(i);
			}

			_route = route;
		}

		Bus(string name, uint maxAmountPassengers, uint currentAmountPassengers, const Route& route, const Passenger* passengers) :
			_name{ name }, _maxAmountPassengers{ maxAmountPassengers }
		{
			if (currentAmountPassengers > maxAmountPassengers)
				throw "Out of range";

			if (route.getLength() == 0)
				throw "Out of range";

			for (size_t i = 0; i < currentAmountPassengers; i++)
			{
				_passengers.addBack(passengers[i]);
			}

			_route = route;
		}

		Bus(const Bus& bus):
			_name{ bus._name }, _maxAmountPassengers { bus._maxAmountPassengers }, 
			_route{ bus._route }, _passengers{ bus._passengers } {}

		Bus(Bus&& bus):
			_name{ bus._name }, _maxAmountPassengers{ bus._maxAmountPassengers }, 
			_route{ bus._route }, _passengers{ move(bus._passengers) } {}

		string getName() const
		{
			return _name;
		}

		uint getCurrentAmountPassengers() const
		{
			return _passengers.getSize();
		}

		uint getMaxAmountPassengers() const
		{
			return _maxAmountPassengers;
		}

		Route setRoute(const Route& route)
		{
			Route current = _route;

			_route = route;

			return current;
		}

		Route getRoute() const
		{
			return _route;
		}

		Passenger setPassengerAt(uint index, const Passenger& passenger)
		{
			if (index >= _passengers.getSize())
				throw "Out of range";

			return _passengers(index, passenger);
		}

		Passenger getPassengerAt(uint index) const
		{
			if (index >= _passengers.getSize())
				throw "Out of range";

			return _passengers[index];
		}

		Bus& addBackPassenger(const Passenger& passenger)
		{
			if (_passengers.getSize() + 1 > _maxAmountPassengers)
				throw "Out of range";

			_passengers.addBack(passenger);

			return *this;
		}

		Passenger deleteBackPassenger()
		{
			return _passengers.deleteBack();
		}

		Bus& addForwardPassenger(const Passenger& passenger)
		{
			if (_passengers.getSize() + 1 > _maxAmountPassengers)
				throw "Out of range";

			_passengers.addForward(passenger);

			return *this;
		}

		Passenger deleteForwardPassenger()
		{
			return _passengers.deleteForward();
		}

		Bus& insertPassengerAt(uint index, const Passenger& passenger)
		{
			if (_passengers.getSize() + 1 > _maxAmountPassengers)
				throw "Out of range";

			if (index >= _passengers.getSize())
				throw "Out of range";

			_passengers.insertByIndex(index, passenger);

			return *this;
		}

		Passenger deletePassengerAt(uint index)
		{
			if (index >= _passengers.getSize())
				throw "Out of range";

			return _passengers(index);
		}

		Bus& print(string shift = "")
		{
			cout << shift << "Name: "					   << _name << endl;
			cout << shift << "Current Amount Passengers: " << _passengers.getSize() << endl;
			cout << shift << "Max Amount Passengers: "	   << _maxAmountPassengers << endl;

			cout << endl << shift << "Passengers: " << endl << endl;

			for (size_t i = 0; i < _passengers.getSize(); i++)
			{
				_passengers[i].print("\t\t", to_string(i + 1));

				cout << endl;
			}

			cout << shift << "Route: " << endl << endl;
			cout << shift << "\t" << _route << endl;

			return *this;
		}
};

class Stopping
{
	private:
		string _name;

		DynamicQueue<Bus> _buses;
		DoubleLinkedList<Passenger> _passengers;

	public:
		Stopping(string name) : _name{ name } {}

		string getName() const
		{
			return _name;
		}

		Stopping& enqueueBus(const Bus& bus)
		{
			_buses.enqueue(bus);

			return *this;
		}

		Bus dequeueBus()
		{
			return _buses.dequeue();
		}

		Bus peekBus() const
		{
			return _buses.peek();
		}

		Stopping& addBackPassenger(const Passenger& passenger)
		{
			_passengers.addBack(passenger);

			return *this;
		}

		Passenger deleteBackPassenger()
		{
			return _passengers.deleteBack();
		}

		Stopping& addForwardPassenger(const Passenger& passenger)
		{
			_passengers.addForward(passenger);

			return *this;
		}

		Passenger deleteForwardPassenger()
		{
			return _passengers.deleteForward();
		}

		Passenger deletePassengerAt(uint index)
		{
			return _passengers.deleteByIndex(index);
		}

		Passenger setPassengerAt(uint index, const Passenger& passenger)
		{
			if (index >= _passengers.getSize())
				throw "Out of range";

			return _passengers(index, passenger);
		}

		Passenger getPassengerAt(uint index) const
		{
			if (index >= _passengers.getSize())
				throw "Out of range";

			return _passengers[index];
		}

		Stopping& insertPassengerAt(uint index, const Passenger& passenger)
		{
			if (index >= _passengers.getSize())
				throw "Out of range";

			_passengers.insertByIndex(index, passenger);

			return *this;
		}

		Stopping& print(string shift = "")
		{
			cout << shift << "Stopping Name: " << _name << endl << endl;

			cout << shift << "Bus Amount: " << _buses.getSize() << endl;
			cout << shift << "Last Bus: " << endl << endl;

			if (!_buses.isEmpty())
			{
				_buses.peek().print("\t" + shift);
			} 
			else
			{
				cout << shift << "\tNot buses" << endl;
			}

			cout << endl << endl;

			cout << shift << "Passengers Amount: " << _passengers.getSize() << endl;

			cout << shift << "Passengers: " << endl << endl;

			if (!_passengers.isEmpty())
			{
				for (size_t i = 0; i < _passengers.getSize(); i++)
				{
					_passengers[i].print("\t" + shift, to_string(i + 1));

					cout << endl;
				}
			}
			else
			{
				cout << shift << "\tNot passengers" << endl;
			}

			return *this;
		}
};

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

			public:
				StoppingNode(
					const Stopping& stopping, 
					float averageTimePassengersAtDay,
					float averageTimePassengersAtNight, 
					float averageTimeBusesAtDay, 
					float averageTimeBusesAtNight
				) : 
					_stopping{stopping},
					_averageTimePassengersAtDay{ averageTimePassengersAtDay }, 
					_averageTimePassengersAtNight{ averageTimePassengersAtNight },
					_averageTimeBusesAtDay{ averageTimeBusesAtDay },
					_averageTimeBusesAtNight{ averageTimeBusesAtNight } 
				{}

				Stopping& getStopping()
				{
					return _stopping;
				}

				float getAverageTimePassengersAtDay() const
				{
					return _averageTimePassengersAtDay;
				}

				float getAverageTimePassengersAtNight() const
				{
					return _averageTimePassengersAtNight;
				}

				float getAverageTimeBusesAtDay() const
				{
					return _averageTimeBusesAtDay;
				}

				float getAverageTimeBusesAtNight() const
				{
					return _averageTimeBusesAtNight;
				}

		};

		DoubleLinkedList<StoppingNode> _stoppingNodes;

		bool _isStoppingExists(string name) const
		{
			for (size_t i = 0; i < _stoppingNodes.getSize(); i++)
			{
				if (name == _stoppingNodes[i].getStopping().getName())
					return true;
			}

			return false;
		}

	public:
		Model() {}

		Model& addStopping(
			string name,
			float averageTimePassengersAtDay,
			float averageTimePassengersAtNight,
			float averageTimeBusesAtDay,
			float averageTimeBusesAtNight
		)
		{
			if (_isStoppingExists(name))
			{
				throw "This stopping is already exists";
			}

			Stopping stopping(name);
			StoppingNode stoppingNode(stopping, averageTimePassengersAtDay, averageTimePassengersAtNight, averageTimeBusesAtDay, averageTimeBusesAtNight);

			_stoppingNodes.addBack(stoppingNode);

			return *this;
		}

		Model& simulate()
		{
			

			return *this;
		}

		friend ostream& operator<<(ostream& out, const Model& model)
		{
			out << "Amount Stoppings: " << model._stoppingNodes.getSize() << endl << endl; 
			
			for (size_t i = 0; i < model._stoppingNodes.getSize(); i++)
			{
				out << i + 1 << ". " << endl;

				out << "\tAverage Time Passengers At Day: "   << model._stoppingNodes[i].getAverageTimePassengersAtDay() << endl;
				out << "\tAverage Time Passengers At Night: " << model._stoppingNodes[i].getAverageTimePassengersAtNight() << endl;
				out << "\tAverage Time Buses At Day: "        << model._stoppingNodes[i].getAverageTimeBusesAtDay() << endl;
				out << "\tAverage Time Buses At Night: "	  << model._stoppingNodes[i].getAverageTimeBusesAtNight() << endl;

				out << endl;

				model._stoppingNodes[i].getStopping().print("\t");

				out << endl;
			}
			out << endl;

			return out;
		}
};

int main()
{
	setlocale(LC_ALL, "Ru");

	Route route1({ "Детский сад", "В академию", "в DNS"});

	Passenger pass1("Kostos", "Детский сад");
	Passenger pass2("Fazber338", "в DNS");
	Passenger pass3("KingGor", "В академию");
	Bus bus1("108", 30, route1, { pass1, pass2 });

	Model model;

	model.addStopping("Детский сад", 1, 2, 3, 4);
	model.addStopping("Кинотеатр 'Первомайский'", 4, 8, 12, 16);

	cout << model << endl;

	return 0;
} 
