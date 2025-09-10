#include "BitcoinExchange.hpp"

bool BitcoinExchange::dateIsCorrect(std::string date)
{
	std::string yearStr;
	std::string monthStr;
	std::string dayStr;
	int daysInMonth;
	int year;
	int month;
	int day;

	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return false;
	yearStr = date.substr(0, 4);
	monthStr = date.substr(5, 2);
	dayStr = date.substr(8, 2);
	for (size_t i = 0; i < yearStr.length(); i++)
		if (!std::isdigit(yearStr[i]))
			return false;
	for (size_t i = 0; i < monthStr.length(); i++)
		if (!std::isdigit(monthStr[i]))
			return false;
	for (size_t i = 0; i < dayStr.length(); i++)
		if (!std::isdigit(dayStr[i]))
			return false;
	year = std::atoi(yearStr.c_str());
	month = std::atoi(monthStr.c_str());
	day = std::atoi(dayStr.c_str());
	(void) year;
	if (month < 1 || month > 12)
		return false;
	switch (month) 
	{
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			daysInMonth = 31;
			break;
		case 4: case 6: case 9: case 11:
			daysInMonth = 30;
			break;
		case 2:
			daysInMonth = 28;
			break;
		default:
			return false;
	}
	if (day < 1 || day > daysInMonth)
		return false;
	return true;
}

bool BitcoinExchange::isFloat(const std::string& str) {
	char* endptr;
	errno = 0;
	double val = strtod(str.c_str(), &endptr);

	(void)val;
	// Comprobaciones:
	// 1. La conversión no debe haber fallado (no debe ser NULL)
	// 2. endptr no debe ser igual al inicio de la cadena (algo se pudo convertir)
	// 3. endptr debe apuntar al carácter nulo al final de la cadena (todo el string fue un número)
	return (errno == 0 && endptr != str.c_str() && *endptr == '\0'); 
}

void BitcoinExchange::CalcInput(std::string date, double value)
{
	std::map<std::string, double>::iterator it;

	it = this->btc.lower_bound(date);

	if (it != this->btc.end() && it->first == date)
	{
		if (it->second != 0)
			std::cout << date << " => " << value << " = " << value * it->second << std::endl;
	}
	else if (it != this->btc.begin())
	{
		it--;
		if (it->second != 0)
			std::cout << date << " => " << value << " = " << value * it->second << std::endl;
	}
	else
		std::cout << "Error: no data available for " << date << std::endl;
}

std::string trim(const std::string &s)
{
	size_t start = s.find_first_not_of(" \t\r\n\v\f\r");
	size_t end = s.find_last_not_of(" \t\r\n\v\f\r");
	if (start == std::string::npos)
		return "";
	return s.substr(start, end - start + 1);
}

void BitcoinExchange::FormatIsOk(std::string date, std::string value)
{
	char* endptr;
	double valueDouble;
	
	date = trim(date);
	value = trim(value);
	if (isFloat(value))
	{
		valueDouble = strtod(value.c_str(), &endptr);
		if (!dateIsCorrect(date))
		{
			std::cout << "Error: bad input => " << date << std::endl;
			return ;
		}
		if (valueDouble < static_cast<double>(0) || valueDouble > 1000)
		{
			if (valueDouble > 1000)
				std::cout << "Error: too large a number." << std::endl;
			else
				std::cout << "Error: not a positive number" << std::endl;
			return ;
		}
		CalcInput(date, valueDouble);
	}
	else
		std::cout << "Error: not a number." << std::endl;
}

void BitcoinExchange::BitcoinExchangeStart(const std::string& file)
{
	std::ifstream fileOpen(file.c_str());
	std::string line, value, date;
	char delimiter = '|';

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

void BitcoinExchange::LoadDataInMap(const std::string& fileData)
{
	std::ifstream fileOpen(fileData.c_str());
	std::string line, exchangeRate, date;
	char delimiter = ',';
	double exchangeRateDouble;

	if (!fileOpen.is_open())
		throw FileNotFound();
	getline(fileOpen, line);
	while (getline(fileOpen, line))
	{
		std::stringstream lineStream(line);
		if (getline(lineStream, date, delimiter) && getline(lineStream, exchangeRate, delimiter))
		{
			exchangeRateDouble = std::atof(exchangeRate.c_str());
			this->btc.insert(std::make_pair(date, exchangeRateDouble));
		}
	}

}

BitcoinExchange::BitcoinExchange(std::string file)
{
	std::string fileData = "./data.csv";

	LoadDataInMap(fileData);
	BitcoinExchangeStart(file);
}

BitcoinExchange::~BitcoinExchange() {}