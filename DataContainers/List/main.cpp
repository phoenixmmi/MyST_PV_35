#include<iostream>

namespace DataContainers
{
	class List
	{
		class Element
		{
			int data;
			Element* pNext;
			Element* pPrev;
		public:
			Element(int data, Element* pNext = nullptr, Element* pPrev = nullptr) :data(data), pNext(pNext), pPrev(pPrev)
			{
				std::cout << "EConstructor:\t" << this << std::endl;
			}
			~Element()
			{
				std::cout << "EDestructor:\t" << this << std::endl;
			}
			friend class List;
		};
		Element* head;	//�������� ��������� �� ������ ������
		Element* tail;	//��������� �� ����� ������
		unsigned int size;	//���������� ��������� ������
	public:

		class Iterator
		{
			Element* Temp;
		public:
			Iterator(Element* Temp = nullptr)
			{
				this->Temp = Temp;
#ifdef DEBUG
				std::cout << "ItConstructor:\t" << this << std::endl;
#endif // DEBUG
			}
			~Iterator()
			{
#ifdef DEBUG
				std::cout << "ItDestructor:\t" << this << std::endl;
#endif // DEBUG
			}

			//		Operators:
			Iterator& operator++()
			{
				Temp = Temp->pNext;
				return *this;
			}

			Iterator operator++(int)
			{
				Iterator old = *this;	//CopyConstructor
				Temp = Temp->pNext;
				return old;
			}

			const int& operator*()const
			{
				return Temp->data;
			}
			int& operator*()
			{
				return Temp->data;
			}

			bool operator==(const Iterator& other)const
			{
				return this->Temp == other.Temp;
			}
			bool operator!=(const Iterator& other)const
			{
				return this->Temp != other.Temp;
			}

			//////////////////
		};

		class ReverseIterator
		{
			Element* Temp;
		public:
			ReverseIterator(Element* Temp = nullptr)
			{
				this->Temp = Temp;
#ifdef DEBUG
				std::cout << "RItConstructor:\t" << this << std::endl;
#endif // DEBUG
			}
			~ReverseIterator()
			{
#ifdef DEBUG
				std::cout << "RItDestructor:\t" << this << std::endl;
#endif // DEBUG
			}

			//		Operators:
			ReverseIterator& operator++()
			{
				Temp = Temp->pPrev;
				return *this;
			}
			ReverseIterator operator++(int)
			{
				ReverseIterator old = *this;
				Temp = Temp->pPrev;
				return old;
			}

			const int& operator*()const
			{
				return Temp->data;
			}
			int& operator*()
			{
				return Temp->data;
			}

			bool operator==(const ReverseIterator& other)const
			{
				return this->Temp == other.Temp;
			}
			bool operator!=(const ReverseIterator& other)const
			{
				return this->Temp != other.Temp;
			}
		};

		const Iterator begin()const
		{
			return this->head;
		}
		const Iterator end()const
		{
			return nullptr;
		}
		const ReverseIterator rbegin()const
		{
			return tail;
		}
		const ReverseIterator rend()const
		{
			return head->pPrev;
		}
		Iterator begin()
		{
			return this->head;
		}
		Iterator end()
		{
			return tail->pNext;
		}
		ReverseIterator rbegin()
		{
			return tail;
		}
		ReverseIterator rend()
		{
			return head->pPrev;
		}

		List()
		{
			head = tail = nullptr;
			size = 0;
			std::cout << "LConstructor:\t" << this << std::endl;
		}
		List(const std::initializer_list<int>& il) :List()
		{
			std::cout << typeid(il.begin()).name() << std::endl;
			/*for (int const* it = il.begin(); it != il.end(); it++)
			{
				push_back(*it);
			}*/
			for (int i : il)
			{
				push_back(i);
			}
		}
		List(const List& other) :List()
		{
			/*for (Element* Temp = other.head; Temp; Temp = Temp->pNext)
			{
				push_back(Temp->data);
			}*/
			for (Iterator it = other.head; it != nullptr; it++)
				push_back(*it);
			std::cout << "LCopyConstructor:\t" << this << std::endl;
		}
		List(List&& other)
		{
			this->head = other.head;
			this->tail = other.tail;
			this->size = other.size;
			other.head = other.tail = nullptr;
			std::cout << "LMoveConstructor:\t" << this << std::endl;
		}
		~List()
		{
			while (head || tail)
			{
				pop_front();
				pop_back();
			}
			std::cout << "LDestructor:\t" << this << std::endl;
		}

		//			Operators:
		List& operator=(const List& other)
		{
			if (this == &other)return *this;
			while (head)pop_front();
			for (Element* Temp = other.head; Temp; Temp = Temp->pNext)push_back(Temp->data);
			std::cout << "LCopyAssignment:\t" << this << std::endl;
			return *this;
		}
		List& operator=(List&& other)
		{
			while (head)pop_front();
			this->head = other.head;
			this->tail = other.tail;
			this->size = other.size;
			other.head = other.tail = nullptr;
			std::cout << "LMoveConstructor:\t" << this << std::endl;
			return *this;
		}

		//			Adding elements:
		void push_front(int data)
		{
			if (head == nullptr)
			{
				head = tail = new Element(data);
				size++;
				return;
			}
			head = head->pPrev = new Element(data, head);
			size++;
		}
		void push_back(int data)
		{
			if (tail == nullptr)
			{
				head = tail = new Element(data);
				size++;
				return;
			}
			tail = tail->pNext = new Element(data, nullptr, tail);
			size++;
		}
		void insert(int index, int data)
		{
			if (index > size)throw std::exception("Error: out of range");
			Element* Temp;
			if (index < size / 2)
			{
				Temp = head;
				for (int i = 0; i < index; i++)Temp = Temp->pNext;
			}
			else
			{
				Temp = tail;
				for (int i = 0; i < size - 1 - index; i++)Temp = Temp->pPrev;
			}

			/*Element* New = new Element(data);
			New->pNext = Temp;
			New->pPrev = Temp->pPrev;
			Temp->pPrev->pNext = New;
			Temp->pPrev = New;*/

			Temp->pPrev = Temp->pPrev->pNext = new Element(data, Temp, Temp->pPrev);
			size++;
		}
		//			Removing elements:
		void pop_front()
		{
			if (head == tail)
			{
				delete head;
				head = tail = nullptr;
				if (size)size--;
				return;
			}
			head = head->pNext;
			delete head->pPrev;
			head->pPrev = nullptr;
			size--;
		}
		void pop_back()
		{
			if (head == tail)
			{
				delete tail;
				head = tail = nullptr;
				if (size)size--;
				return;
			}
			tail = tail->pPrev;
			delete tail->pNext;
			tail->pNext = nullptr;
			size--;
		}

		void erase(int index)
		{
			if (index >= size)throw std::exception("Error: Out of range");
			if (index == 0)
			{
				pop_front();
				return;
			}
			if (index == size - 1)
			{
				pop_back();
				return;
			}

			Element* Temp;
			if (index < size / 2)
			{
				Temp = head;
				for (int i = 0; i < index; i++)Temp = Temp->pNext;
			}
			else
			{
				Temp = tail;
				for (int i = 0; i < size - 1 - index; i++)Temp = Temp->pPrev;
			}

			Temp->pPrev->pNext = Temp->pNext;
			Temp->pNext->pPrev = Temp->pPrev;
			delete Temp;
			size--;
		}

		//			Methods:
		void print()const
		{
			for (Element* Temp = head; Temp != nullptr; Temp = Temp->pNext)
			{
				std::cout << Temp->pPrev << "\t" << Temp << "\t" << Temp->data << "\t" << Temp->pNext << std::endl;
			}
			std::cout << "List size:\t" << size << std::endl;
		}
		void print_reverse()const
		{
			for (Element* Temp = tail; Temp != nullptr; Temp = Temp->pPrev)
			{
				std::cout << Temp->pPrev << "\t" << Temp << "\t" << Temp->data << "\t" << Temp->pNext << std::endl;
			}
			std::cout << "List size:\t" << size << std::endl;
		}
	};

	List operator+(const List& left, const List& right)
	{
		List buffer = left;	//CopyConstructor
		for (List::Iterator it = right.begin(); it != right.end(); it++)
		{
			buffer.push_back(*it);
		}
		std::cout << "Global operator +\n";
		return buffer;
	}
}

//#define BASE_CHECK
//#define CONSTRUCTORS_CHECK

void main()
{
	int n;
	//std::cout << "Input list size: "; std::cin >> n;
#ifdef BASE_CHECK
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	list.print_reverse();
	int index;
	int data;
	try
	{
		std::cout << "Input index: "; std::cin >> index;
		//std::cout << "Input value: "; std::cin >> data;
		//list.insert(index, data);
		list.erase(index);
		list.print();
		list.print_reverse();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
#endif // BASE_CHECK

#ifdef CONSTRUCTORS_CHECK
	int arr[] = { 3, 5, 8 };

	List list = { 3, 5, 8, 13, 21 };
	list = list;
	list.print();
	list.print_reverse();

	List list2 = list;
	//list2 = list;
	list2.print();
	list2.print_reverse();
#endif // CONSTRUCTORS_CHECK

	int arr[] = { 3, 5, 8, 13, 21 };
	for (int i : arr)
	{
		std::cout << i << "\t";
	}
	std::cout << std::endl;

	DataContainers::List list = { 3, 5, 8, 13, 21 };
	//list.print();
	//list.print_reverse();

	for (DataContainers::List::Iterator it = list.begin(); it != list.end(); it++)
		std::cout << *it << "\t";
	std::cout << std::endl;

	DataContainers::List list2 = { 34,55,89 };
	for (DataContainers::List::Iterator it = list2.begin(); it != list2.end(); it++)
	{
		std::cout << *it << "\t";
	}
	std::cout << std::endl;
	std::cout << "\n----------------------------------------------------------------------\n";
	/*for (int i : list + list2)
	{
		std::cout << i << "\t";
	}
	std::cout << std::endl;*/

	DataContainers::List list3;
	list3 = list + list2;
	//list3.print();
	for (int i : list3)
	{
		std::cout << i << "\t";
	}
	//std::cout << std::endl;
	std::cout << "\n----------------------------------------------------------------------\n";
	for (DataContainers::List::ReverseIterator rit = list3.rbegin(); rit != list3.rend(); rit++)
	{
		std::cout << *rit << "\t";
	}
	std::cout << std::endl;
}