#include<iostream>

class String
{
	int size;	//Number of Bytes
	char* str;
public:
	int get_size()const
	{
		return size;
	}
	const char* get_str()const
	{
		return str;
	}

	String(int size = 80)
	{
		this->size = size;
		this->str = new char[size] {};
		std::cout << "DefaultConstruct:" << this << std::endl;
	}
	String(const char* str)
	{
		this->size = strlen(str) + 1;
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)this->str[i] = str[i];
		std::cout << "Constructor:\t" << this << std::endl;
	}

	String(const String& other)
	{
		this->size = other.size;
		this->str = new char[size] {};
		//for (int i = 0; i < size; i++)this->str[i] = other.str[i];
		strcpy_s(this->str, size, other.str);
		std::cout << "CopyConstructor:" << this << std::endl;
	}

	~String()
	{
		delete[] this->str;
		std::cout << "Destructor:\t" << this << std::endl;
	}

	String& operator=(const String& other)
	{
		if (this == &other)return *this;
		delete[] this->str;
		this->size = other.size;
		this->str = new char[size] {};
		//for (int i = 0; i < size; i++)this->str[i] = other.str[i];
		strcpy_s(this->str, size, other.str);
		std::cout << "CopyAssignment:" << this << std::endl;
		return *this;
	}

	//			Methods:
	void print()
	{
		std::cout << size << "\t" << str << std::endl;
	}
};

std::ostream& operator<<(std::ostream& os, const String& obj)
{
	return os << obj.get_str();
}

void main()
{
	String str1;
	str1.print();

	String str2 = "Hello";
	str2.print();

	String str3 = str2;	//Copy constructor
	str3.print();

	str1 = str2;	//Copy assignment
	str1.print();

	str1 = str1;
	str1.print();

	std::cout << str1 << std::endl;
}