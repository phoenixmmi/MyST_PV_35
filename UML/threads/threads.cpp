#include <iostream>
#include<thread>

using namespace std::literals::chrono_literals;
static bool finish = false;

void Print1()
{
	while (!finish)
	{
		std::cout << "1";
		std::this_thread::sleep_for(1s);
	}
}

void Print2()
{
	while (!finish)
	{
		std::cout << "0";
		std::this_thread::sleep_for(1s);
	}
}

int main()
{
	/*while (true)
	{
		std::cout << "Hello";
	}*/
	std::thread thread1(Print1);
	std::thread thread2(Print2);

	std::cin.get();
	finish = true;

	thread2.join();
	thread1.join();
	//std::cout << Print1 << std::endl;
}

