#include "PMerge.hpp"

void	parseString(std::string argString, PMerge &pushSwapMergue)
{
	std::stringstream lineStream(argString);
	std::string nmbr;

	while (getline(lineStream, nmbr, ' '))
		if (!nmbr.empty())
			convertToInt(nmbr, pushSwapMergue);
}

void	convertToInt(std::string argString, PMerge &pushSwapMergue)
{
	long	nmbr;

	if (argString.empty())
		throw NotValidArgument();
	for (size_t i = 0; i < argString.length(); i++)
		if (!std::isdigit(argString[i]))
			throw NotValidArgument();
	nmbr = std::atol(argString.c_str());
	if (nmbr < 0 || nmbr > INT32_MAX)
		throw NotValidArgument();
	pushSwapMergue.addToDeque(nmbr);
	pushSwapMergue.addToVector(nmbr);
}

void parsingArguments(char **argv)
{
	unsigned int i = 0;
	PMerge pushSwapMergue;

	while (argv[i])
	{
		std::string argString(argv[i]);
		if (argString.find(" ") != std::string::npos)
			parseString(argString, pushSwapMergue);
		else
			convertToInt(argString, pushSwapMergue);
		i++;
	}
	
}


int	main(int argc, char **argv)
{
	if (argc < 2)
		return 1;
	try
	{
		parsingArguments(++argv);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}