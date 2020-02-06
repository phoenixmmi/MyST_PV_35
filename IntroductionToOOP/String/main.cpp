#include<iostream>

class String;
String operator+(const String& left, const String& right);

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
	char* get_str()
	{
		return str;
	}

	/*String()
	{
		this->size = 80;
		this->str = new char[size] {};
		std::cout << "DefaultConstruct:" << this << std::endl;
	}*/
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
	String(String&& other)
	{
		this->size = other.size;
		this->str = other.str;
		other.str = nullptr;
		std::cout << "MoveConstructor:\t" << this << std::endl;
	}

	~String()
	{
		delete[] this->str;
		std::cout << "Destructor:\t" << this << std::endl;
	}

	//			Operators:

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

	String& operator+=(const String& other)
	{
		return *this = *this + other;
	}

	const char& operator[](int i)const
	{
		return str[i];
	}

	char& operator[](int i)
	{
		return str[i];
	}

	//			Methods:
	void print()
	{
		std::cout << size << "\t" << str << std::endl;
	}
};

String operator+(const String& left, const String& right)
{
	String cat = left.get_size() + right.get_size() - 1;

	/*for (int i = 0; i < left.get_size(); i++)cat.get_str()[i] = left.get_str()[i];
	for (int i = 0; i < right.get_size(); i++)
		cat.get_str()[i + left.get_size() - 1] = right.get_str()[i];*/

	for (int i = 0; i < left.get_size(); i++)cat[i] = left[i];
	for (int i = 0; i < right.get_size(); i++)
		cat[i + left.get_size() - 1] = right[i];

	return cat;
}

std::ostream& operator<<(std::ostream& os, const String& obj)
{
	return os << obj.get_str();
}

//#define CONSTRUCTORS_CHECK

void main()
{
#ifdef CONSTRUCTORS_CHECK
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
#endif // CONSTRUCTORS_CHECK

	String str1 = "Hello";
	String str2 = "World";
	std::cout << "\n----------------------------------\n";
	String str3 = str1 + str2;
	std::cout << "\n----------------------------------\n";
	std::cout << str3 << std::endl;
	//str1 += str2;
	//std::cout << str1 << std::endl;
}