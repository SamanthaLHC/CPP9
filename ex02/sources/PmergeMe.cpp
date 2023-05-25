#include "pmg.hpp"

//==================================================================================================
//		constructors / destructors
//==================================================================================================
PmergeMe::PmergeMe() {} // non utilisé, mis en private

PmergeMe::PmergeMe(std::deque<int> int_array, std::list<int> int_list, int ac) : _int_deque(int_array),
																				 _int_list(int_list),
																				 _count_elem(ac)
{
	std::cout << WHITE << "Before: ";
	print_sequence();

	sort_in_deque();
	sort_in_list();
}

PmergeMe::PmergeMe(PmergeMe const &cpy) : _int_deque(cpy._int_deque),
										  _int_list(cpy._int_list),
										  _count_elem(cpy._count_elem)
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
		_int_deque = rhs._int_deque;
		_int_list = rhs._int_list;
		_count_elem = rhs._count_elem;
	}
	return *this;
}

//==================================================================================================
//		members functions
//==================================================================================================
// utils
void PmergeMe::print_sequence()
{
	std::deque<int>::iterator it = _int_deque.begin();
	for (; it != _int_deque.end(); it++)
	{
		std::cout << *it;
		std::cout << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::print_sequence_list()
{
	std::list<int>::iterator it = _int_list.begin();
	for (; it != _int_list.end(); it++)
	{
		std::cout << *it;
		std::cout << " ";
	}
	std::cout << std::endl;
}

//sort
void sort_in_deque()
{
	// if ac == odd , un elem non trié
	// make pairs
	// inside pairs sort 
	// sort pairs looking right element
	// 
}

void sort_in_list()
{

}

//measure time