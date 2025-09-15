#include "PMerge.hpp"

PMerge::PMerge() : pMergueDeque() , pMergueVector (), timeToStartDeque(0), timeToStartVector(0), timeToEndDeque(0), timeToEndVector(0) {}

PMerge::PMerge(const PMerge& other)
{
	if (this != &other)
	{
		this->pMergueDeque = other.pMergueDeque;
		this->pMergueVector = other.pMergueVector;
		this->timeToStartDeque = other.timeToStartDeque;
		this->timeToEndDeque = other.timeToEndDeque;
		this->timeToStartVector = other.timeToStartVector;
		this->timeToEndVector = other.timeToEndVector;
	}
}

PMerge& PMerge::operator=(const PMerge& other)
{
	if (this != &other)
	{
		this->pMergueDeque = other.pMergueDeque;
		this->pMergueVector = other.pMergueVector;
		this->timeToStartDeque = other.timeToStartDeque;
		this->timeToEndDeque = other.timeToEndDeque;
		this->timeToStartVector = other.timeToStartVector;
		this->timeToEndVector = other.timeToEndVector;
	}
	return *this;
}

PMerge::~PMerge() {}

void PMerge::addToVector(int value)
{
	pMergueVector.push_back(value);
}
void PMerge::addToDeque(int value)
{
	pMergueDeque.push_back(value);
}

void PMerge::printStart()
{
	size_t i = 0;
	std::cout << "Before: ";

	while (i < this->pMergueVector.size() && i < 5)
	{
		std::cout << this->pMergueVector[i] << " ";
		i++;
	}
	if (this->pMergueVector.size() <= 5)
		std::cout << std::endl;
	else
		std::cout << " [...]"<< std::endl;
	
}

template <typename T>
void PMerge::printEnd(const T& container)
{
	double timeInMs;
	
	if (typeid(container) == typeid(std::vector<int>))
	{
		this->timeToEndVector = clock();
		timeInMs = (static_cast<double>(timeToEndVector - timeToStartVector) / CLOCKS_PER_SEC) * 1000.0;
	}
	else
	{
		this->timeToEndDeque = clock();
		timeInMs = (static_cast<double>(timeToEndDeque - timeToStartDeque) / CLOCKS_PER_SEC) * 1000.0;
	}
	std::cout << "After: ";
	size_t i = 0;
	while (i < container.size() && i < 5) {
		std::cout << container[i] << " ";
		i++;
	}
	if (container.size() <= 5)
		std::cout << std::endl;
	else
		std::cout << "[...]" << std::endl;
	std::cout << "Time to process a range of " << container.size() << " elements with ";
	if (typeid(container) == typeid(std::vector<int>))
		std::cout << "std::vector";
	else
		std::cout << "std::deque";
	std::cout << " : " << timeInMs << " ms" << std::endl;
}


template<typename T>
int makePairsFromContainers(const T& cont, std::vector<std::pair<int,int> >& pares, bool& hasSobrante)
{
	int sobrante;

	pares.clear();
	size_t i = 0;
	while (i + 1 < cont.size())
	{
		if (cont[i] < cont[i + 1])
			pares.push_back(std::make_pair(cont[i], cont[i + 1]));
		else
			pares.push_back(std::make_pair(cont[i + 1], cont[i]));
		i += 2;
	}
	if (i < cont.size())
	{
		sobrante = cont[i];
		hasSobrante = true;
	}
	else
	{
		sobrante = 0;
		hasSobrante = false;
	}
	return (sobrante);
}


template<typename T>
static void fillLower(T& mayores, T& menores, const std::vector<std::pair<int, int> >& pares)
{
	size_t i = 0;

	while (i < pares.size())
	{
		menores.push_back(pares[i].first);
		mayores.push_back(pares[i].second);
		i++;
	}
}
template<typename T>
void insertMinors(T& mayores, const T& menores)
{
	typename T::iterator it;

	for (size_t i = 0; i < menores.size(); i++)
	{
		it = std::lower_bound(mayores.begin(), mayores.end(), menores[i]);
		mayores.insert(it, menores[i]);
	}
}

template<typename T>
static void sortMaxNums(T& maxNum)
{
	bool isSorted = true;
	size_t i = 0;
	int sobrante = 0;
	bool hasSobrante = false;
	std::vector<std::pair<int,int> > pares;
	T mayores;
	T menores;
	typename T::iterator it;

	while (i + 1 < maxNum.size())
	{
		if (maxNum[i] > maxNum[i + 1])
		{
			isSorted = false;
			break;
		}
		i++;
	}
	if (isSorted)
		return;
	sobrante = makePairsFromContainers(maxNum, pares, hasSobrante);
	fillLower(mayores, menores, pares);
	sortMaxNums(mayores);
	insertMinors(mayores, menores);
	if (hasSobrante)
	{
		it = std::lower_bound(mayores.begin(), mayores.end(), sobrante);
		mayores.insert(it, sobrante);
	}
	maxNum.clear();
	for (size_t j = 0; j < mayores.size(); ++j)
		maxNum.push_back(mayores[j]);
}


void PMerge::sortVector()
{
	printStart();
	int sobrante;
	bool hasSobrante = false;
	std::vector<std::pair<int,int> > pares;
	std::vector<int> mayores;
	std::vector<int> menores;
	std::vector<int>::iterator it;
	this->timeToStartVector = clock();

	sobrante = makePairsFromContainers(this->pMergueVector, pares, hasSobrante);
	fillLower(mayores, menores, pares);
	sortMaxNums(mayores);
	insertMinors(mayores, menores);
	if (hasSobrante)
	{
		it = std::lower_bound(mayores.begin(), mayores.end(), sobrante);
		mayores.insert(it, sobrante);
	}
	this->pMergueVector = mayores;
	printEnd(this->pMergueVector);
}

void PMerge::sortDeque()
{
	printStart();
	size_t sobrante;
	bool hasSobrante = false;
	std::vector<std::pair<int,int> > pares;
	std::deque<int> mayores;
	std::deque<int> menores;
	std::deque<int>::iterator it;
	this->timeToStartDeque = clock();

	sobrante = makePairsFromContainers(this->pMergueDeque, pares, hasSobrante);
	fillLower(mayores, menores, pares);
	sortMaxNums(mayores);
	insertMinors(mayores, menores);
	if (hasSobrante)
	{
		it = std::lower_bound(mayores.begin(), mayores.end(), sobrante);
		mayores.insert(it, sobrante);
	}
	this->pMergueDeque = mayores;
	printEnd(this->pMergueDeque);
}
