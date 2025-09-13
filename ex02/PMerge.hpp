#ifndef PMERGE_HPP
# define PMERGE_HPP

# include <iostream>
# include <vector>
# include <deque>
# include <sstream>
# include <ctime> 


class PMerge
{
private:
	std::deque<int> pMergueDeque;
	std::vector<int> pMergueVector;
	unsigned int timeToStart;
	unsigned int timeToEnd;
public:
	PMerge();
	~PMerge();
	void addToVector(long value);
	void addToDeque(long value);
};


class NotValidArgument : public std::exception
{
	public:
		const char* what() const throw() { return "The argument is not valid"; }
};

#endif