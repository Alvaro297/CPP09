#include "RPN.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "No enought arguments" <<std::endl;
		return ;
	}
	RPN rpnClass(argv[1]);
	std::cout << "Result: " << rpnClass.getResult() << std::endl;
}