#include<iostream>
#include<thread>
#include<conio.h>
using namespace std::chrono_literals;
class Tank
{
	unsigned int volume;       //характеризует объект, показывает какой он (объкт), меняться не может.
	double fuel_level;         //состояние объекта, которое может меняться. 
public:
	const unsigned int get_volume()const
	{
		return volume;
	}
	const double get_fuel_level()const
	{
		return fuel_level;
	}

	Tank(unsigned int volume)
	{
		this->volume = volume < 20 ? 20 : volume > 100 ? 100 : volume;
		this->fuel_level = 0;
		std::cout << "Tank ready: \t" << this << std::endl;
	}
	~Tank()
	{
		std::cout << "Tank destroyed:\t" << this << std::endl;
	}


	void fill(double fuel)
	{
		if (fuel < 0)return;
		if (fuel_level + fuel <= volume)
		{
			this->fuel_level += fuel;
		}
		else
		{
			fuel_level = volume;
		}
	}

	double give_fuel(double amount)
	{
		fuel_level -= amount;
		if (fuel_level < 0)fuel_level = 0;
		return fuel_level;
	}

	void info()const
	{
		std::cout << "Tank volume: " << volume << "\tliters.\t";
		std::cout << "Fuel level: " << fuel_level << "\tliters" << std::endl;
	}
};

class Engine
{
	double consumption;
	double consumption_per_second;

	bool is_started;
public:
	const double get_consumption()const
	{
		
		return consumption;
	}
	const double get_consumption_per_second()const
	{
		return consumption_per_second;
	}
	void set_comsumption_per_second(double consumption_per_second)
	{
		//if (consumption_per_second > .0001 && consumption_per_second < .009)
			this->consumption_per_second = consumption_per_second;
	}

	Engine(double consumption)
	{
		this->consumption = consumption < 3 ? 3 : consumption > 20 ? 20 : consumption;
		this->consumption_per_second = this->consumption / 10000;

		is_started = false;
		std::cout << "Engine is ready:\t" << this << std::endl;
	}
	~Engine()
	{
		std::cout << "Engine is over:\t" << this << std::endl;
	}
	void start()
	{
		is_started = true;
	}
	void stop()
	{
		is_started = false;
	}
	bool started()const
	{
		return is_started;
	}
	void info()const
	{
		std::cout << "Engine consumption:\t" << get_consumption() << " liters per 100 km" << std::endl;
		std::cout << "Consumption per sec:\t" << get_consumption_per_second() << " liters per second " << std::endl;
		std::cout << "Engine is " << (is_started ? "started" : "stopperd") << ".\n";
	}
};

class Car
{
	Engine engine;
	Tank tank;
	bool driver_inside;
	unsigned int speed;
	unsigned int max_speed;
	struct ControlPanel
	{
		//поток (thread) - это последовательность комнад процессора. В потоке запускается выполнение какой-то функции.
		std::thread* main_thread;		//Это основной поток, он создаётся при создании машины, и существует столько, сколько существует машина.
										//этот поток принимает команды пользователя, позволяет зайди и выйти из машины , а следовательно, порождает и останавливает остальные потоки. 
		std::thread* panel_thread;		//панель приборов. Мы видим панель приборов и можем на неё влиять только тогда, когда мы находимся внутри.
										//Этот поток, независимый от работы двигателя. Он существует только тогда, когда водитель находится внутри.
										//этот поток отслеживает состояние, в том числе и бака.
		std::thread* idle_thread;		//холостой ход двигателя. Создаётся когда мы заводим машину, и удаляется когда мы останавливаем двигатель.
										//этот поток вляет на состояние бака
		std::thread* wheeling_thread = nullptr;
	}control_panel;
public:
	Car(double tank_volume, double engine_consumption, unsigned max_speed = 250)
		:tank(tank_volume), engine(engine_consumption), driver_inside(false), speed(0), max_speed(max_speed)
	{
		control_panel.main_thread = new std::thread(&Car::control, this);
		std::cout << "Your car is ready to go." << std::endl;

	}
	~Car()
	{
		if (control_panel.main_thread->joinable())control_panel.main_thread->join();
		std::cout << "Your car is over" << std::endl;
	}
	//Functions:
	void get_in()
	{
		driver_inside = true;
		control_panel.panel_thread = new std::thread(&Car::panel, this);
	}
	void get_out()
	{
		driver_inside = false;
		control_panel.panel_thread->join();
		system("CLS");
		std::cout << "You are in the street, press enter to get in your car." << std::endl;
	}
	bool is_driver_inside()const
	{
		return driver_inside;
	}
	void fill(double fuel)
	{
		tank.fill(fuel);
	}
	void start()
	{
		if (!tank.get_fuel_level())
		{
			std::cout << "No fuel.\n";
			return;
		}
		if (driver_inside)
		{
			engine.start();
			control_panel.idle_thread = new std::thread(&Car::idle, this);
		}
	}
	void stop()
	{
		engine.stop();
		change_consumption();
		if (control_panel.idle_thread->joinable())control_panel.idle_thread->join();
	}
	void panel()const
	{
		while (driver_inside)
		{
			system("CLS");
			for (int i = 0; i < speed / 2; i++)
			{
				if (i > 140)break;
				std::cout << "|";
			}
			std::cout << std::endl;

			std::cout << "Engine is " << (engine.started() ? "started." : "stopped.") << std::endl;
			std::cout << "Fuel:\t" << tank.get_fuel_level() << " leters.\t" << std::endl;
			if (tank.get_fuel_level() < 5) std::cout << "LOW FUEL" << std::endl;
			std::cout << speed << " km/h.\n";

			std::cout << "Consumption per second: " << engine.get_consumption_per_second() << std::endl;

			using namespace std::chrono_literals;
			std::this_thread::sleep_for(1s);
		}
	}
	void idle()
	{
		using namespace std::chrono_literals;
		while (engine.started() && tank.give_fuel(engine.get_consumption_per_second()))
		{
			change_consumption();
			std::this_thread::sleep_for(1s);
		}
		engine.stop();
	}
	void control()
	{
		std::cout << " Press enter to get in." << std::endl;
		char key = 0;
		do
		{
			key = _getch();
			switch (key)
			{
				//case 'E':
			case 13:
				if (!is_driver_inside())get_in();
				else get_out();
				break;
			case 'F':
			case 'f':
				if (!driver_inside)
				{
					double amount;
					std::cout << "How much?"; std::cin >> amount;
					fill(amount);
				}
				else {
					std::cout << "Get out of car! " << std::endl;
				}
				break;
			case 'I':
			case 'i':
				if (!engine.started())
				{
					start();
				}
				else
				{
					stop();
				}
				break;
			case 'W':
			case 'w':
				if (engine.started())
				{
					speed += 10;
					if (speed > max_speed)speed = max_speed;
					std::this_thread::sleep_for(1s);
				}
					break;
			case 'S':
			case 's':
				if (speed > 20)speed -= 20;
				else if (speed > 10)speed -= 10;
				else if (speed > 5)speed -= 5;
				else speed = 0;
				std::this_thread::sleep_for(1s);
				break;
			}
			std::this_thread::sleep_for(1ms);
			if (speed > 0 && control_panel.wheeling_thread == nullptr)
				control_panel.wheeling_thread = new std::thread(&Car::free_wheeling, this);
			else if (speed == 0 && control_panel.wheeling_thread && control_panel.wheeling_thread->joinable())
			{
				control_panel.wheeling_thread->join();
				control_panel.wheeling_thread=nullptr;
			}
			change_consumption();
		} while (key != 27);
	}
	//////////////////////////////DRIVING/////////////////////////////
	
	void free_wheeling()
	{
		using namespace std::chrono_literals;
		while (speed > 0)
		{
			speed--;
			std::this_thread::sleep_for(1s);
		}
	}
	void change_consumption()
	{
		if (engine.started())
		{
			if (speed > 0 && speed <= 60)engine.set_comsumption_per_second(.02);
			else if (speed > 60 && speed <= 100)engine.set_comsumption_per_second(.014);
			else if (speed > 100 && speed <= 140)engine.set_comsumption_per_second(.02);
			else if (speed > 140 && speed <= 200)engine.set_comsumption_per_second(.025);
			else if (speed > 200 && speed <= 250)engine.set_comsumption_per_second(.03);
			else engine.set_comsumption_per_second(engine.get_consumption() / 10000);
		}
		else 
		{
			engine.set_comsumption_per_second(0);
		}
	}
};

//#define TANK_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef TANK_CHECK
	Tank tank(40);
	tank.info();
	tank.fill(20);
	tank.info();
	tank.fill(30);
	tank.info();
#endif

	Car bmw(60, 8);

}

