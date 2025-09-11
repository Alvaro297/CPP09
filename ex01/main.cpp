#include "RPN.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "No enought arguments" <<std::endl;
		return 1;
	}
	try
	{
		RPN rpnClass(argv[1]);
		std::cout << "Result: " << rpnClass.getResult() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << '\n';
		return 1;
	}
	
	
	return 0;
}