#ifndef PMERGE_HPP
# define PMERGE_HPP

# include <iostream>
# include <vector>
# include <deque>
# include <sstream>
# include <ctime>
#include <climits>
#include <cstdlib>
#include <typeinfo>

class PMerge
{
private:
	std::deque<int> pMergueDeque;
	std::vector<int> pMergueVector;
	unsigned int timeToStartDeque;
	unsigned int timeToStartVector;
	unsigned int timeToEndDeque;
	unsigned int timeToEndVector;
	void printStart();
	template <typename T>
	void printEnd(const T& container);
	void printTime();
public:
	PMerge();
	PMerge(const PMerge& other);
	PMerge& operator=(const PMerge& other);
	~PMerge();
	void addToVector(int value);
	void addToDeque(int value);
	void sortVector();
	void sortDeque();
};


class NotValidArgument : public std::exception
{
	public:
		const char* what() const throw() { return "The argument is not valid"; }
};

#endif