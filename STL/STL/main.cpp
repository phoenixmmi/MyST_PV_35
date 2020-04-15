#include<iostream>
#include<array>
#include<vector>

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

//#define ARRAY
#define VECTOR

const int SIZE = 5;

#ifdef ARRAY
void print(const std::array<int, SIZE>& arr)
{
	for (std::array<int, SIZE>::const_iterator it = arr.begin(); it != arr.end(); it++)
	{
		//(*it)++;
		std::cout << *it << "\t";
	}
	std::cout << std::endl;
}
#endif // ARRAY


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

#ifdef VECTOR
	//vector - это контейнер, который хранит данные в виде динамического массива.
	std::vector<int> vec{ 0,1,1,2,3,5,8,13,21,34};
	vec.push_back(55);
	try
	{
		for (int i = 0; i < vec.size(); i++)
		{
			//std::cout << vec[i] << "\t";
			std::cout << vec.at(i) << "\t";
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	std::cout << std::endl;
	std::cout << "vector size:\t" << vec.size() << std::endl;
	std::cout << "vector capacity:" << vec.capacity() << std::endl;
	std::cout << "vector max size:" << vec.max_size() << std::endl;

	int index;
	int value;
	std::cout << "Type index: "; std::cin >> index;
	std::cout << "Type value: "; std::cin >> value;
	std::vector<int>::iterator position = vec.begin() + index;
	//vec.insert()
#endif
}
