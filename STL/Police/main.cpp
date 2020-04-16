#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<list>

void print_full_base(const std::map<std::string, std::list<std::string>>& base);
void save(const std::map<std::string, std::list<std::string>>& base);

void main()
{
	setlocale(LC_ALL, "");
	//map - это контейнер, который хранит данные в виде Бинарного дерева. 
	//Каждый элемент этого дерева представляет собой ПАРУ: key - value.
	std::map<std::string, std::list<std::string>> base =
	{
		std::pair<std::string, std::list<std::string>>("BI 0000 BI", {"привышение скорости", "вождение в нетрезвом состоянии"}),
		std::pair<std::string, std::list<std::string>>("BI 0001 BI", {"езда по встречке"}),
		std::pair<std::string, std::list<std::string>>("BI 0002 BI", {"парковка в неположенном месте"}),
		std::pair<std::string, std::list<std::string>>("BI 0003 BI", {"проезд на красный", "привышение скорости", "плюнул в полицейского"})
	};
#define delimiter "\n------------------------------------\n"
	print_full_base(base);
	save(base);
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
		fout << "\b;\n";
	}
	fout.close();
	system("notepad base.txt");
}