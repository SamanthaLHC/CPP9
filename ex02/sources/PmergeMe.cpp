#include "pmg.hpp"

//==================================================================================================
//		constructors / destructors
//==================================================================================================
PmergeMe::PmergeMe() : _count_elem(0),
					   _vec_time(0),
					   _deque_time(0),
					   _begin_vec(0),
					   _begin_deq(0)
{
}

PmergeMe::PmergeMe(std::deque<int> _int_deque, std::vector<int> _int_vector, int ac) : _count_elem(ac),
																					   _int_deque(_int_deque),
																					   _int_vector(_int_vector)
{
	std::cout << WHITE << "Before:	";
	print_sequence(_int_vector);
	launch();
}

PmergeMe::PmergeMe(PmergeMe const &cpy) : _count_elem(cpy._count_elem),
										  _int_deque(cpy._int_deque),
										  _int_vector(cpy._int_vector)
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
		_int_vector = rhs._int_vector;
		_count_elem = rhs._count_elem;
	}
	return *this;
}

//==================================================================================================
//		members functions
//==================================================================================================

// print

// void PmergeMe::print_sequence(std::deque<int> _int_deque)
// {
// 	std::deque<int>::iterator it = _int_deque.begin();
// 	for (; it != _int_deque.end(); it++)
// 	{
// 		std::cout << WHITE << *it;
// 		std::cout << " ";
// 	}
// 	std::cout << RES << std::endl;
// }

void PmergeMe::print_sequence(std::vector<int> _int_vector)
{
	std::vector<int>::iterator it = _int_vector.begin();
	for (; it != _int_vector.end(); it++)
	{
		std::cout << WHITE << *it;
		std::cout << " ";
	}
	std::cout << RES << std::endl;
}

void PmergeMe::print_result()
{
	std::cout << WHITE << "After:	";
	print_sequence(_int_vector);
}

void PmergeMe::print_time()
{
	std::cout << WHITE << "Time to process a range of: " << _count_elem
			  << " elements with std::vector : " << _vec_time << " us" << RES << std::endl;

	std::cout << WHITE << "Time to process a range of: " << _count_elem
			  << " elements with std::deque : " << _deque_time << " us" << RES << std::endl;
}

// // measure time

void PmergeMe::set_time_begin_vec(clock_t time)
{
	_begin_vec = time;
}

clock_t PmergeMe::get_time_begin_vec()
{
	return _begin_vec;
}

double PmergeMe::get_vec_time()
{
	return _vec_time;
}

void PmergeMe::set_time_begin_deq(clock_t time)
{
	_begin_deq = time;
}

clock_t PmergeMe::get_time_begin_deq()
{
	return _begin_deq;
}

double PmergeMe::get_deq_time()
{
	return _deque_time;
}

// sort

int PmergeMe::jacobsthal(int n)
{
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	else
		return jacobsthal(n - 1) + 2 * jacobsthal(n - 2);
}



// Fonction récursive
void PmergeMe::merge_insert_sort(const std::vector<int> &input)
{
	if (input.size() <= 1)
	{
		return input;
	}

	std::vector<std::pair<int, int> > merged_pairs = merge(input);

	
	clock_t end_time = clock();
	_vec_time = (end_time - _begin_vec) * 1000000 / CLOCKS_PER_SEC;
}

void PmergeMe::launch()
{
	merge_insert_sort(_int_vector);
	// merge_insert_sort(_int_deque);
	print_result();
	print_time();
}
