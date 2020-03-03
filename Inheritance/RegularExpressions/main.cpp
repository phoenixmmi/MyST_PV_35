#include<iostream>
#include<string>
#include<regex>

//#define REGEX_EMAIL
//#define REGEX_PHONE
#define CONVERT_PHONE

void main()
{
	setlocale(LC_ALL, "");
#ifdef REGEX_EMAIL
	std::string email = "vsya@gmail.jks.ua";
	//std::cout << "Input E-mail: "; std::cin >> email;
	std::regex rgx("\\w{3,50}@[a-z]{1,20}[.][a-z]{2,3}(.[a-z]{2})?");
	std::cout << std::regex_match(email.c_str(), rgx, std::regex_constants::match_default) << std::endl;
#endif // REGEX_EMAIL

#ifdef REGEX_PHONE
	std::string phone = "+38(099)123-45-67";
	//std::regex rgx("\\+\\d{2}\\(\\d{3}\\)\\d{3}(-\\d{2}){2}");
	std::regex rgx(R"(\+\d{2}\(\d{3}\)\d{3}(-\d{2}){2})");
	std::cout << std::regex_match(phone, rgx, std::regex_constants::match_default) << std::endl;
#endif

#ifdef CONVERT_PHONE
	std::string phone = "380991234567";
	std::regex rgx("\\d{12}");
	if (std::regex_match(phone, rgx, std::regex_constants::match_default))
	{
		phone.insert(0, "+");
		phone.insert(phone.size() - 10, "(");
		phone.insert(phone.size() - 7, ")");
		phone.insert(phone.size() - 4, "-");
		phone.insert(phone.size() - 2, "-");
		std::cout << phone << std::endl;
	}

#endif // CONVERT_PHONE

}