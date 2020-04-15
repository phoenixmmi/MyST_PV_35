#include<iostream>

#define delimiter "\n----------------------------------------\n"
//static . -> (:: - Scope operator)
class Element
{
	int Data;		//Значение элемента
	Element* pNext;	//Адрес следующего элемента
	static int count;
public:
	const int getData()const
	{
		return Data;
	}
	const Element* getpNext()const
	{
		return pNext;
	}
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
#ifdef DEBUG
		std::cout << "EConstructor:\t" << this << std::endl;
#endif // DEBUG

	}
	~Element()
	{
		count--;
#ifdef DEBUG
		std::cout << "EDestructor:\t" << this << std::endl;
#endif // DEBUG

	}
	friend class ForwardList;
	friend class Iterator;
};

int Element::count = 0;

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp)
	{
		this->Temp = Temp;
	}
	~Iterator()
	{

	}

	int& operator*()
	{
		return Temp->Data;
	}
	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}
};

class ForwardList
{
	Element* Head;
	unsigned int Size;
public:
	const Element* get_head()const
	{
		return Head;
	}
	Element* get_head()
	{
		return Head;
	}
	unsigned int get_size()const
	{
		return Size;
	}
	ForwardList()
	{
		Head = nullptr;	//Если список пуст, то его голова указывает на 0;
		Size = 0;
		std::cout << "LConstructor:\t" << this << std::endl;
	}
	ForwardList(int size) :ForwardList()
	{
		while (size--)push_front(0);
	}
	ForwardList(const std::initializer_list<int>& il) :ForwardList()
	{
		for (const int* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		for (Element* Temp = other.Head; Temp != nullptr; Temp = Temp->pNext)
		{
			push_back(Temp->Data);
		}
		std::cout << "FLCopyConstructor:\t" << this << std::endl;
	}
	ForwardList(ForwardList&& other)
	{
		this->Head = other.Head;
		this->Size = other.Size;
		other.Head = nullptr;
		std::cout << "FLMoveConstructor:\t" << this << std::endl;
	}
	~ForwardList()
	{
		while (Head)pop_front();
		std::cout << "LDestructor:\t" << this << std::endl;
	}

	//			Operators:
	ForwardList& operator=(const ForwardList& other)
	{
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp != nullptr; Temp = Temp->pNext)
		{
			push_back(Temp->Data);
		}
		std::cout << "FLCopyAssignment:\t" << this << std::endl;
		return *this;
	}

	ForwardList& operator=(ForwardList&& other)
	{
		this->Head = other.Head;
		this->Size = other.Size;
		other.Head = nullptr;
		std::cout << "FLMoveAssignment:\t" << this << std::endl;
		return *this;
	}

	int& operator[](int index)
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
		return Temp->Data;
	}

	//			Adding elements:
	void push_front(int Data)
	{
		/*Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;*/
		Head = new Element(Data, Head);
		Size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)
		{
			push_front(Data);
			return;
		}
		Element* Temp = Head;
		while (Temp->pNext != nullptr)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = new Element(Data);
		Size++;
	}

	void insert(int Index, int Data)
	{
		if (Index > Size)
		{
			std::cout << "Error: Out of range" << std::endl;
			return;
		}
		if (Index == 0)
		{
			push_front(Data);
			return;
		}
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			Temp = Temp->pNext;
		}
		/*Element* New = new Element(Data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;*/
		Temp->pNext = new Element(Data, Temp->pNext);
		Size++;
	}

	//			Removing elements:
	void pop_front()
	{
		Element* buffer = Head;	//Запоминаем адрес удаляемого элемента
		Head = Head->pNext;	//Исключаем элемент из списка
		delete buffer;
		Size--;
	}
	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext != nullptr)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;
		Size--;
	}
	void erase(int index)
	{
		if (index >= this->Size)
		{
			throw std::exception("Error: Out of range when erasing.");
		}
		if (index == 0)
		{
			pop_front();
			return;
		}
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)	Temp = Temp->pNext;
		Element* buffer = Temp->pNext;	//save address of destructing element.
		Temp->pNext = Temp->pNext->pNext;//exclude destructing exement from list
		delete buffer;	//remove element from memory
		Size--;
	}

	//			Methods:
	void print()const
	{
		Element* Temp = Head;		//Итератор - это указатель, при помощи которого можно получить доступ 
									//к элементам структуры данных.
		while (Temp != nullptr)
		{
			std::cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << std::endl;
			Temp = Temp->pNext;	//Переход на следующий элемент
		}
		std::cout << "List size: " << Size << " elements.\n";
	}
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList buffer = left;
	//for (const Element* Temp = right.get_head(); Temp != nullptr; Temp = Temp->getpNext())
	for (const Element* Temp = right.get_head(); Temp != nullptr; Temp = Temp->getpNext())
		buffer.push_back(Temp->getData());
	return buffer;
}

//#define BASE_FUNCTIONS_CHECK
//#define CONSTRUCTORS_CHECK_1

void main()
{
	setlocale(LC_ALL, "");
	int n;
	std::cout << "Input list size: "; std::cin >> n;
#ifdef BASE_FUNCTIONS_CHECK
	//Element e(5);
	ForwardList fl;

	for (int i = 0; i < n; i++)
	{
		fl.push_back(rand() % 200);
	}
	//fl.push_back(1024);
	fl.print();
	std::cout << delimiter << std::endl;
	/*fl.pop_front();
	fl.pop_back();
	fl.print();*/

	/*ForwardList fl2;
	fl2.push_back(3);
	fl2.push_back(5);
	fl2.push_back(8);
	fl2.push_back(13);
	fl2.push_back(21);
	fl2.print();*/

	int index;
	int value;
	std::cout << "Input index: "; std::cin >> index;
	std::cout << "Input value: "; std::cin >> value;
	fl.insert(index, value);
	fl.print();

	//try
	//{
	//	std::cout << "Input index: "; std::cin >> index;
	//	fl.erase(index);
	//	fl.print();
	//}
	//catch (const std::exception& e)
	//{
	//	std::cerr << e.what() << std::endl;
	//	/*
	//	cin - Console Input;
	//	cout - Console Output;
	//	cerr - Console Error;
	//	*/
	//}

	/*int* pa = new int(2);
	delete[] pa;

	int* arr = new int[5] {3, 5, 8, 13, 21};
	delete arr;*/
#endif // BASE_FUNCTIONS_CHECK

#ifdef CONSTRUCTORS_CHECK_1
	ForwardList fl(n);
	fl.push_back(3);
	fl.push_back(5);
	fl.push_back(8);
	fl.push_back(13);
	fl.print();
	for (int i = 0; i < fl.get_size(); i++)
	{
		fl[i] = rand() % 100;
	}
	for (int i = 0; i < fl.get_size(); i++)
	{
		std::cout << fl[i] << "\t";
	}
	std::cout << std::endl;
#endif // CONSTRUCTORS_CHECK_1

	/*ForwardList list = { 3, 5, 8, 13, 21 };
	list.print();
	for (int i = 0; i < list.get_size(); i++)
		std::cout << list[i] << "\t";
	std::cout << std::endl;

	ForwardList list2 = { 34,55,89 };
	list2 = list;
	list2.print();
	ForwardList list3;
	list3 = list + list2;
	list3.print();*/


	ForwardList list(n);
	/*for (int i = 0; i < list.get_size(); i++)
	{
		list[i] = rand() % 100;
	}*/
	for (Iterator it = list.get_head(); it != nullptr; ++it)
	{
		*it = rand() % 100;
	}
	std::wcout << "List filled\n";
}