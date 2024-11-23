#include <iostream>
#include <initializer_list>
#include <string>
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

				Node(T value) : value{ value }, next{ nullptr }, prev{ nullptr } {}
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

			cout << "Drop list" << endl;
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

		T setByIndex(uint index, T value)
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

		DoubleLinkedList& insertByIndex(uint index, T value)
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

		DoubleLinkedList& addBack(T value)
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

		DoubleLinkedList& addForward(T value)
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

		T operator()(uint index, T value)
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

		DynamicQueue& enqueue(T value)
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

		~Route()
		{
			cout << "Drop route" << endl;
		}

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

		~Passenger()
		{
			cout << "Drop passenger" << endl;
		}

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

		friend ostream& operator<<(ostream& out, const Passenger& passenger)
		{
			out << "Name: " << passenger._name  << "\tDestination: " << passenger._destination << endl;

			return out;
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

			_route                   = route;
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

		~Bus()
		{
			cout << "Drop bus" << endl;
		}

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

		Passenger setPassengerAt(uint index, Passenger passenger)
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

		Bus& addPassenger(Passenger passenger)
		{
			if (_passengers.getSize() + 1 > _maxAmountPassengers)
				throw "Out of range";

			_passengers.addBack(passenger);

			return *this;
		}

		Passenger deletePassenger()
		{
			return _passengers.deleteBack();
		}

		friend ostream& operator<<(ostream& out, const Bus& bus)
		{
			out << "Name: "					   << bus._name << endl;
			out << "currentAmountPassengers: " << bus._passengers.getSize() << endl;
			out << "maxAmountPassengers: "	   << bus._maxAmountPassengers << endl;

			out << endl << "Passengers: " << endl << endl;

			for (size_t i = 0; i < bus._passengers.getSize(); i++)
			{
				out << '\t' << i + 1 << ".  " << bus._passengers[i] << endl;
			}

			out << "Route: " << endl << endl;
			out << '\t' << bus._route << endl;

			return out;
		}
};

class Stopping
{
	public:
		enum STOPPING_TYPE
		{
			FINAL,
			NOT_FINAL
		};

	private:
		string        _name;
		STOPPING_TYPE _type;

		DoubleLinkedList<Bus> _buses;

	public:
		Stopping(string name) : Stopping(name, NOT_FINAL) {}

		Stopping(string name, STOPPING_TYPE type): _name{name}, _type{type} {}

		~Stopping()
		{
			cout << "Drop stopping" << endl;
		}

		Stopping& addBus(Bus bus)
		{
			_buses.addBack(bus);

			return *this;
		}

		void deleteBus()
		{
			_buses.deleteBack();
		}

		friend ostream& operator<<(ostream& out, const Stopping& stopping)
		{
			out << stopping._buses.getFirst();

			return out;
		}
};

int main()
{
	setlocale(LC_ALL, "Ru");

	Route route({ "Детский сад", "в DNS", "В академию" });

	Passenger pass1("Kostos", "Детский сад");
	Passenger pass2("Fazber338", "в DNS");
	Passenger pass3("KingGor", "В академию");

	Bus bus("108", 30, route, { pass1, pass2, pass3 });

	//Stopping stopping("Детский сад", Stopping::NOT_FINAL);
	//stopping.addBus(bus);

	//stopping.deleteBus();

	//cout << stopping << endl;

	return 0;
}
