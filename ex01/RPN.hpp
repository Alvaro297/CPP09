#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <stack>

class RPN
{
private:
	int result;
	int resultRPN(std::string RPN);
public:
	RPN(std::string RPNStart);
	RPN(const RPN& copyRPN);
	RPN& operator=(const RPN& oldRPN);
	int getResult() const;
	~RPN();
};


#endif