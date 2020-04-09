#include<iostream>
#include<array>

/*
-----------------------------------------------------------------------------------
STL - Standard Template Library.
Container - это объект, который организует хранение других объектов в памяти.

1. Sequence containers:
	array;
	vector;
	deque;
	forward_list;
	list;
2. Associative containers:
	map;
	multimap;
	set;
	multiset;
3. Container adaptors:
	stack;
	queue - очередь;
	priority_queue - очередь с приоритетами;

-----------------------------------------------------------------------------------
*/

#define ARRAY

const int SIZE = 5;

void print(const std::array<int, SIZE>& arr)
{
	for (std::array<int, SIZE>::const_iterator it = arr.begin(); it != arr.end(); it++)
	{
		//(*it)++;
		std::cout << *it << "\t";
	}
	std::cout << std::endl;
}

void main()
{

#ifdef ARRAY
	//array - это контейнер, который хранит объекты в статическом массиве.
	std::array<int, SIZE> arr = { 3, 5, 8 };
	try
	{
		for (int i = 0; i < SIZE * 2; i++)
		{
			std::cout << arr.at(i) << "\t";
		}
		std::cout << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	for (std::array<int, SIZE>::iterator it = arr.begin(); it != arr.end(); it++)
	{
		std::cout << *it << "\t";
	}
	std::cout << std::endl;

	for (std::array<int, SIZE>::reverse_iterator rit = arr.rbegin(); rit != arr.rend(); rit++)
	{
		std::cout << *rit << "\t";
	}
	std::cout << std::endl;

	print(arr);
#endif // ARRAY

}
