#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <string>
# include <map>
# include <fstream>
# include <sstream>
# include <stdexcept>
# include <algorithm>

class BitcoinExchange
{
private:
	std::map<std::string, double> btc;
	bool dateIsCorrect(std::string date);
	bool isFloat(const std::string& str);
	void FormatIsOk(std::string date, std::string value);
	void CalcInput(std::string date, double value);
public:
	BitcoinExchange(std::string file);
	~BitcoinExchange();

	void LoadDataInMap(const std::string& fileData);
	void BitcoinExchangeStart(const std::string& file);
};

class FileNotFound : public std::exception
{
	public:
		const char* what() const throw() { return "Not file in rute"; };
};

#endif