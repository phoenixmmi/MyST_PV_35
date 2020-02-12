#include<iostream>

class String;
String operator+(const String& left, const String& right);

class String
{
	int size;	//Number of Bytes
	char* str;
public:
	const int get_size()const
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

	void set_str(const char* str)
	{
		delete[] this->str;
		this->size = strlen(str) + 1;
		this->str = new char[size] {};
		strcpy(this->str, str);
	}

	/*String()
	{
		this->size = 80;
		this->str = new char[size] {};
		std::cout << "DefaultConstruct:" << this << std::endl;
	}*/
	explicit String(int size = 80) :size(size), str(new char[size] {})
	{
		//this->size = size;
		//this->str = new char[size] {};
		std::cout << "DefaultConstruct:" << this << std::endl;
	}
	String(const char* str) :String(strlen(str) + 1)
	{
		/*this->size = strlen(str) + 1;
		this->str = new char[size] {};*/
		for (int i = 0; i < size; i++)this->str[i] = str[i];
		std::cout << "Constructor:\t" << this << std::endl;
	}

	String(const String& other) :String(other.str)
	{
		/*this->size = other.size;
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)this->str[i] = other.str[i];*/
		//strcpy_s(this->str, size, other.str);
		std::cout << "CopyConstructor:" << this << std::endl;
	}
	String(String&& other):size(other.size),str(other.str)
	{
		/*this->size = other.size;
		this->str = other.str;*/
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
	String cat(left.get_size() + right.get_size() - 1);

	/*for (int i = 0; i < left.get_size(); i++)cat.get_str()[i] = left.get_str()[i];
	for (int i = 0; i < right.get_size(); i++)
		cat.get_str()[i + left.get_size() - 1] = right.get_str()[i];*/

	for (int i = 0; i < left.get_size(); i++)cat[i] = left[i];
	for (int i = 0; i < right.get_size(); i++)
		cat[i + left.get_size() - 1] = right[i];

	return cat;
}

bool operator==(const String& left, const String& right)
{
	if (strlen(left.get_str()) != strlen(right.get_str()))return false;
	for (int i = 0; left[i]; i++)
	{
		if (left[i] != right[i])return false;
	}
	return true;
}

bool operator!=(const String& left, const String& right)
{
	return !(left == right);
}

bool operator<(const String& left, const String& right)
{
	/*if (strcmp(left.get_str(), right.get_str()) < 0)return true;
	else return false;*/

	return strcmp(left.get_str(), right.get_str()) < 0 ? true : false;
}

std::ostream& operator<<(std::ostream& os, const String& obj)
{
	return os << obj.get_str();
}

std::istream& operator>>(std::istream& is, String& obj)
{
	char* sz_str = new char[USHRT_MAX] {};
	is >> sz_str;
	sz_str = (char*)realloc(sz_str, strlen(sz_str) + 1);
	obj.set_str(sz_str);
	delete[] sz_str;
	return is;
}

//#define CONSTRUCTORS_CHECK
#define OPERATOR_PLUS_CHECK
//#define INPUT_CHECK

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

#ifdef OPERATOR_PLUS_CHECK
	String str1 = "Hello";
	String str2 = "World";
	std::cout << "\n----------------------------------\n";
	String str3 = str1 + " " + str2;
	std::cout << "\n----------------------------------\n";
	std::cout << str3 << std::endl;
	//str1 += str2;
	//std::cout << str1 << std::endl;  
#endif // OPERATOR_PLUS_CHECK

#ifdef INPUT_CHECK
	String str = "Hello";
	//std::cout << "Input string: ";
	std::cout << str << std::endl;
	std::cin >> str;
	std::cout << str << std::endl;
#endif // INPUT_CHECK

	/*String str1 = "Hello";
	String str2 = "World";
	std::cout << (str1 < str1) << std::endl;

	String str(5);*/
}