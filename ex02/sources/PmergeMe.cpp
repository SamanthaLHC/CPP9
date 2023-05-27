#include "pmg.hpp"

//==================================================================================================
//		constructors / destructors
//==================================================================================================
PmergeMe::PmergeMe() {} // non utilisé, mis en private

PmergeMe::PmergeMe(std::deque<int> int_array, std::list<int> int_list, int ac) : _last_int(0),
																				 _int_deque(int_array),
																				 _int_list(int_list),
																				 _count_elem(ac)
{
	std::cout << WHITE << "Before: ";
	print_sequence();

	sort_in_deque();
	sort_in_list();
}

PmergeMe::PmergeMe(PmergeMe const &cpy) : _last_int(cpy._last_int),
										  _int_deque(cpy._int_deque),
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
		_last_int = rhs._last_int;
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

void PmergeMe::print_pairs()
{
	size_t i = 0;
	for (; i < _deque_pairs.size(); i++)
	{
		std::cout << CYAN << "[ " << _deque_pairs[i].first << " "
				  << _deque_pairs[i].second << " ]" << RES << std::endl;
	}
}

// sort
void PmergeMe::sort_in_deque()
{

	// make pairs
	DEBUG("last elem in deque ", _int_deque.back());
	DEBUG("count elem: ", _count_elem);
	if (_count_elem % 2 == 0)
		PRINT("elem count is not odd", "");
	else
		PRINT("elems odd", "");
	
	if (!(_count_elem % 2 == 0))
	{
		_last_int = _int_deque.back();
		_int_deque.pop_back();
	}
	while (_int_deque.size() > 0)
	{
		std::pair<int, int> cell;
		cell.first = _int_deque.front();
		_int_deque.pop_front();
		cell.second = _int_deque.front();
		_int_deque.pop_front();
		_deque_pairs.push_back(cell);
	}
	print_pairs();
	DEBUG("last elem saved if odd ", _last_int);
	// inside pairs sort
	// sort pairs looking right element
	//
}

void PmergeMe::sort_in_list()
{
}
