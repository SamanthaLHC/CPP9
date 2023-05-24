#include "pmg.hpp"

//==================================================================================================
//		constructors / destructors
//==================================================================================================
PmergeMe::PmergeMe() {} // non utilisé, mis en private

PmergeMe::PmergeMe(std::deque<int> int_array, std::list<int> int_list, int ac) : _count_elem(ac)
{
	(void)int_array;
	(void)int_list;
	(void)ac;
}

PmergeMe::PmergeMe(PmergeMe const &cpy)
{
	*this = cpy;
}

PmergeMe::~PmergeMe()
{
}

//==================================================================================================
//		operator overload
//==================================================================================================

PmergeMe &PmergeMe::operator=(PmergeMe const &rhs)
{
	if (this != &rhs)
	{
	}
	return *this;
}

//==================================================================================================
//		members functions
//==================================================================================================
// parsing and check


