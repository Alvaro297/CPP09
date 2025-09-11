#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <stack>
# include <sstream>
# include <cstdlib>

class RPN
{
private:
	int result;
	int resultRPN(std::string RPN);
	typedef int (RPN::*OpFunc)(int, int);
	int add(int a, int b);
	int sub(int a, int b);
	int mul(int a, int b);
	int div(int a, int b);
public:
	RPN(std::string RPNStart);
	RPN(const RPN& copyRPN);
	RPN& operator=(const RPN& oldRPN);
	int getResult() const;
	~RPN();

	class GreaterThanTwoException : public std::exception
	{
		public:
			const char* what() const throw() { return "The lenght is more than 2"; }
	};

	class NoFoundException : public std::exception
	{
		public:
			const char* what() const throw() { return "The value of the char is not the correct"; }
	};

	class NotEnoughtNumbers : public std::exception
	{
		public:
			const char* what() const throw() { return "The stack has only one number"; }
	};

	class DivisionByZeroException : public std::exception
	{
		public:
			const char* what() const throw() { return "Cant divide in 0"; }
	};
};


#endif