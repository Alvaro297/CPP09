#include "RPN.hpp"

int RPN::add(int a, int b) { return a + b; }
int RPN::sub(int a, int b) { return a - b; }
int RPN::mul(int a, int b) { return a * b; }
int RPN::div(int a, int b) { return a / b; }

int RPN::resultRPN(std::string startRPN)
{
	std::stack <int> stackRPN;
	std::string nextNumber;
	int a = 0;
	int b = 0;
	int res = 0;
	const char ops[] = {'+', '-', '*', '/'};
	OpFunc funcs[] = {&RPN::add, &RPN::sub, &RPN::mul, &RPN::div};

	std::stringstream inputStringstream(startRPN);
	while (getline(inputStringstream, nextNumber, ' '))
	{
		if (nextNumber.length() >= 2)
			throw GreaterThanTwoException();
		else if (std::isdigit(nextNumber[0]))
			stackRPN.push((std::atoi(nextNumber.c_str())));
		else if (nextNumber.length() == 1 &&
				(nextNumber[0] == '+' || nextNumber[0] == '-' ||
				nextNumber[0] == '*' || nextNumber[0] == '/'))
		{
			if (stackRPN.size() < 2)
				throw NotEnoughtNumbers();

			for (int i = 0; i < 4; ++i)
			{
				if (nextNumber[0] == ops[i])
				{
					b = stackRPN.top(); 
					stackRPN.pop();
					a = stackRPN.top();
					stackRPN.pop();
					if (ops[i] == '/' && b == 0)
						throw DivisionByZeroException();
					res = (this->*funcs[i])(a, b);
					stackRPN.push(res);
					break ;
				}
			}
		}
		else
			throw NoFoundException();
	}
	if (stackRPN.size() != 1)
		throw NoFoundException();
	return stackRPN.top();
}

RPN::RPN(std::string RPNStart) : result(resultRPN(RPNStart)) {}

RPN::RPN(const RPN& copyRPN)
{
	if (this != &copyRPN)
		this->result = copyRPN.result;
}

RPN& RPN::operator=(const RPN& oldRPN)
{
	if (this != &oldRPN)
		this->result = oldRPN.result;
	return *this;
}

RPN::~RPN() {}

int RPN::getResult() const { return this->result; }