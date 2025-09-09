#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <string>


class BitcoinExchange
{
private:
	std::string date;
	int value;
public:
	BitcoinExchange(std::string date, int value);
	~BitcoinExchange();



};

class FileNotFound : public std::exception
{
	public:
		const char* what() const throw() { return "Not file in rute"; };
};

#endif