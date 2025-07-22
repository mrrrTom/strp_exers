#include <iostream>
#include <string.h>

int main()
{
	
	bool flag = false;
	char symbol = 'q';
	int integerNumber = 1;
	double doubleNumber = 33.2;
	std::string word = "hello";
	
	std::cin >> std::boolalpha;
	std::cout << "insert boolean: ";
	std::cin >> flag;
	std::cout << std::endl;

	std::cout << "insert char: ";
	std::cin >> symbol;
	std::cout << std::endl;

	std::cout << "insert int: ";
	std::cin >> integerNumber;
	std::cout << std::endl;

	std::cout << "insert double: ";
	std::cin >> doubleNumber;
	std::cout << std::endl;

	std::cout << "insert string: ";
	std::cin >> word;

	std::cout << std::boolalpha;
	std::cout << std::endl << std::endl << "You inserted:" << std::endl;
	std::cout << "bool: " << flag << std::endl;
	std::cout << "char: " << symbol << std::endl;
	std::cout << "int: " << integerNumber << std::endl;
	std::cout << "double: " << doubleNumber << std::endl;
	std::cout << "string: " << word << std::endl;
	return 0;
}

