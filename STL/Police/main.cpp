#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<list>
#include<Windows.h>
#include <conio.h>
//#include"D:\Install\Dev\boost_1_72_0\boost\algorithm\string.hpp"
#include<boost/algorithm/string.hpp>


std::map<std::string, std::list<std::string>> init();
void print_full_base(const std::map<std::string, std::list<std::string>>& base);
void save(const std::map<std::string, std::list<std::string>>& base);
void load(std::map<std::string, std::list<std::string>>& base);
void insert(std::map<std::string, std::list<std::string>>& base);
void find(std::map<std::string, std::list<std::string>>& base);
int choice(int iterator);
void menu();

void main()
{
	setlocale(LC_ALL, "");
	/*
	//map - это контейнер, который хранит данные в виде Бинарного дерева. 
	//Каждый элемент этого дерева представляет собой ПАРУ: key - value.
	//std::cout << typeid(std::string("Hello").c_str()).name() << std::endl;
	std::map<std::string, std::list<std::string>> base;// = init();
	load(base);
	print_full_base(base);
	insert(base);
	print_full_base(base);
	save(base);*/
#define delimiter "\n------------------------------------\n"
	menu();
}

std::map<std::string, std::list<std::string>> init()
{
	std::map<std::string, std::list<std::string>> base =
	{
		std::pair<std::string, std::list<std::string>>("BI 0000 BI", {"привышение скорости", "вождение в нетрезвом состоянии"}),
		std::pair<std::string, std::list<std::string>>("BI 0001 BI", {"езда по встречке"}),
		std::pair<std::string, std::list<std::string>>("BI 0002 BI", {"парковка в неположенном месте"}),
		std::pair<std::string, std::list<std::string>>("BI 0003 BI", {"проезд на красный", "привышение скорости", "плюнул в полицейского"})
	};
	return base;
}

void print_full_base(const std::map<std::string, std::list<std::string>>& base)
{
	/*for (std::map<std::string, std::list<std::string>>::iterator m_it = base.begin(); m_it != base.end(); m_it++)
	{
		std::cout << m_it->first << ":\n";
		for (std::list<std::string>::iterator l_it = m_it->second.begin(); l_it != m_it->second.end(); l_it++)
		{
			std::cout << " - " << l_it->c_str() << ";\n";
		}
		std::cout << delimiter;
	}*/

	/*int arr[] = { 3,5,8,13,21 };
	for (int i : arr)
	{
		std::cout << arr[i] << "\t";
	}
	std::cout << std::endl;*/

	for (std::pair<std::string, std::list<std::string>> i : base)
	{
		std::cout << i.first << ":\n";
		for (std::string j : i.second)
		{
			std::cout << " - " << j << ";\n";
		}
		std::cout << delimiter;
	}
}

void save(const std::map<std::string, std::list<std::string>>& base)
{
	std::ofstream fout("base.txt");
	//CSV - Comma Separated values;
	for (std::pair<std::string, std::list<std::string>> i : base)
	{
		fout << i.first << ":";
		for (std::string j : i.second)
		{
			fout << j << ",";
		}
		fout.seekp(-1, std::ios::cur); //сдвигаем курсор на одну позицию влево.
		fout << ";\n";
	}
	fout.close();
	system("start notepad base.txt");
}

void load(std::map<std::string, std::list<std::string>>& base)
{
	base.clear();
	print_full_base(base);
	/*std::cout << "After clearing\n";
	system("PAUSE");*/
	std::string license_plate;
	std::string violation;
	std::list<std::string> violation_list;

	std::ifstream fin("base.txt");

	if (fin.is_open())
	{
		//std::istream& stream = fin;
		//std::cout << fin.tellg() << std::endl;;
		//SetConsoleCP(1251);
		while (!fin.eof())
		{
			//fin.getline(license_plate.c_str(), 20, ":");
			std::getline(fin, license_plate, ':');
			if (license_plate == "")break;
			std::getline(fin, violation, '\n');
			std::cout << license_plate << " - " << violation << std::endl;
			
			boost::algorithm::split(violation_list, violation, boost::is_any_of(","));
			//base.insert(std::pair <std::string, std::list<std::string>>(license_plate, violation_list));
			
			/*std::cout << license_plate << ":";
			for (std::string i : violation_list)std::cout << i << ", "; std::cout << ";\n";*/
			/*print_full_base(base);
			system("PAUSE");*/
		}
		//SetConsoleCP(866);
	}
	else
	{
		std::cerr << "Error: file not found" << std::endl;
	}

	fin.close();
}

void insert(std::map<std::string, std::list<std::string>>& base)
{
	std::string license_plate;
	std::string violation;

	std::cout << "Введите номер автомобиля:"; //std::cin >> license_plate;
	SetConsoleCP(1251);	std::getline(std::cin, license_plate);	SetConsoleCP(866);

	std::cout << "Введите правонарушение:  "; //std::cin >> violation;
	SetConsoleCP(1251);	std::getline(std::cin, violation);		SetConsoleCP(866);

	if (license_plate.size() == 0 || violation.size() == 0)return;

	std::map<std::string, std::list<std::string>>::iterator offender = base.find(license_plate);
	if (offender != base.end())
	{
		//ЕСЛИ номер уже есть в базе, то добавляем нарушение к существующему номеру:
		offender->second.push_back(violation);
	}
	else
	{
		//Создаем нового нарушителя в базе:
		base.insert(std::pair<std::string, std::list<std::string>>(license_plate, { violation }));
	}
}
void find(std::map<std::string, std::list<std::string>>& base)
{
	std::string license_plate;

	std::cout << "Введите номер автомобиля: ";
	SetConsoleCP(1251);	std::getline(std::cin, license_plate);	SetConsoleCP(866);

	//std::map<std::string, std::list<std::string>>::iterator offender = base.find(license_plate);
	std::cout << license_plate << " - ";
	for (std::list<std::string>::iterator it = base.find(license_plate)->second.begin(); it != base.find(license_plate)->second.end(); it++)
	{
		std::cout << *it << ",";
	}
	std::cout << "\b;\n";
}
int choice(int iterator)
{
	int choice = _getch();
	system("cls");
	std::cout << choice << std::endl;
	if (choice == 224)choice = _getch();
	if (choice == 72)
	{
		if (iterator > 1)iterator--;
		else iterator = 4;
	}
	else if (choice == 80/*choice==224*/)
	{
		if (iterator < 4)iterator++;
		else iterator = 1;
	}
	else if (choice != 13) std::cout << "Неверный ввод" << std::endl;
	else
	{
		std::cout << "Error";
	}

	std::cout << "Сделайте Ваш выбор: " << std::endl;
	(iterator == 1) ? std::cout << "==>" : std::cout << "   ";
	std::cout << "Загрузка базы из файла" << std::endl;
	(iterator == 2) ? std::cout << "==>" : std::cout << "   ";
	std::cout << "Сохранение базы в файл" << std::endl;
	(iterator == 3) ? std::cout << "==>" : std::cout << "   ";
	std::cout << "Вывод базы на экран" << std::endl;
	(iterator == 4) ? std::cout << "==>" : std::cout << "   ";
	std::cout << "Вывод правонарушений по указанному номеру" << std::endl;
	std::cout << delimiter;
	return{ iterator };
};


void menu()
{
	int iterator = 1;
	std::map<std::string, std::list<std::string>> base = init();
	do
	{
		iterator = choice(iterator);
		//std::cout << choice;
	} while (_getch() != 13);
	if (iterator == 1)
	{
		load(base);
	}
	else if (iterator == 2)//сохранение базы в файл
	{
		save(base);
	}
	else if (iterator == 3)//вывод базы на екран
	{
		print_full_base(base);
	}
	else if (iterator == 4)//вывод правонарушений по указанному номеру
	{
		find(base);
	}
}