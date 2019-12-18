#include<iostream>

//Структура - это тип данных.
//Класс - это тип данных.

class Point
{
	double x;
	double y;
public:
	double get_x() const
	{
		return x;
	}
	double get_y() const
	{
		return y;
	}
	void set_x(double x)
	{
		if (/*x >= -100 && x <= 100*/ abs(x)<=100)
		{
			this->x = x;
		}
		else
		{
			this->x = 0;
		}
		//if отфильтровывает некорректные значения
	}
	void set_y(double y)
	{
		this->y = y;
	}
};

//#define BASICS
#define ENCAPSULATION

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASICS
	int a;	//Объявление переменной 'a', типа 'int'.
	Point A;//Объявление переменной 'A', типа 'Point'.
			//Создание (объявление) объекта 'A' типа 'Point'.
	A.x = 5;
	A.y = 2;
	std::cout << A.x << "\t" << A.y << std::endl;

	Point* pA = &A;
	std::cout << pA->x << "\t" << pA->y << std::endl;
	std::cout << (*pA).x << "\t" << (*pA).y << std::endl;

	/*

	. - Оператор прямого доступа (Point operator),
		используется для обращения к полям (членам) объекта по имени объекта.
	-> - Оператор косвенного доступа (Arrow operator),
		используется для обращения к полям объекта, по адресу объекта.
		Часто возникают ситуации, когда имя обекта узать невозможно,
		но мы всегда можем узнать адрес объекта при помощи 'this'.

	*/
#endif // BASICS

#ifdef ENCAPSULATION
	Point A;
	A.set_x(5);
	A.set_y(3);
	std::cout << A.get_x() << "\t" << A.get_y() << std::endl;
#endif // ENCAPSULATION

}