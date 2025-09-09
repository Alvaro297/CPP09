# include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

bool is_digit(char c) {
	return c >= '0' && c <= '9';
}

bool dateIsCorrect(std::string date)
{
	int i = 0;

	while (date[i])
	{
		if (i != 4 && i != 7)
		{
			if (!is_digit(date[i]))
				return false;
		}
		else
			if (date[i] != '-')
				return false;
		i++;
	}
	if (i != 10)
		return false;
	return true;
}

bool isFloat(const std::string& str) {
	char* endptr;
	errno = 0;
	double val = strtod(str.c_str(), &endptr);

	// Comprobaciones:
	// 1. La conversión no debe haber fallado (no debe ser NULL)
	// 2. endptr no debe ser igual al inicio de la cadena (algo se pudo convertir)
	// 3. endptr debe apuntar al carácter nulo al final de la cadena (todo el string fue un número)
	return (errno == 0 && endptr != str.c_str() && *endptr == '\0'); 
}

void FormatIsOk(std::string date, std::string value)
{
	char* endptr;
	double valueInt;
	
	if (isFloat(value))
	{
		valueInt = strtod(value.c_str(), &endptr);
		if (!dateIsCorrect(date))
		{
			std::cout << "Date is not correct" << std::endl;
			return ;
		}
		if (valueInt < static_cast<double>(0) || valueInt > static_cast<double>(1000))
		{
			std::cout << "Error: not a positive number" << std::endl;
			return ;
		}
		BitcoinExchange btc(date, valueInt);

	}
}

void BitcoinExchangeStart(const std::string& file)
{
	std::ifstream fileOpen(file.c_str());
	std::string line, value, date;
	char delimiter = ',';

	if (!fileOpen.is_open())
		throw FileNotFound();
	getline(fileOpen, line);
	while (getline(fileOpen, line))
	{
		std::stringstream lineStream(line);
		if (getline(lineStream, date, delimiter) && getline(lineStream, value, delimiter))
			FormatIsOk(date, value);
		else
			if (!date.empty())
				std::cout << "Error: bad input => " << date << std::endl;
			else if (!value.empty())
				std::cout << "Error: bad input => " << value << std::endl;
	}
}

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		std::cout << "Wrong number of arguments" << std::endl;
		return 1;
	}
	BitcoinExchangeStart(argv[1]);
	return 0;
}