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

void PmergeMe::print_sequence_paired(std::vector<std::pair<int, int> > _int_vector)
{
	std::vector<std::pair < int, int> >::iterator it = _int_vector.begin();
	for (; it != _int_vector.end(); it++)
	{
		std::cout << CYAN << " [ " << it->first << " " << it->second << " ] ";
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


bool compare_pair(const std::pair<int, int>& lhs, const std::pair<int, int>& rhs)
{
	return lhs.second < rhs.second;
}

void PmergeMe::sort_pairs(std::vector<std::pair<int, int> > &arr, size_t begin, size_t size)
{
	if (size <= 1)
		return;

	//sort in place
	int mid = size / 2;
	sort_pairs(arr, begin, mid);
	sort_pairs(arr, (begin + mid), (size - mid));

	//last1 et last2 excluded
	std::vector<std::pair< int, int> >::iterator current_begin = arr.begin() + begin;
	std::vector<std::pair< int, int> > tmp(size);
	std::merge(current_begin, current_begin + mid, current_begin + mid,
			   current_begin + size, tmp.begin(), compare_pair);
	arr.erase(current_begin, current_begin + size);
	arr.insert(current_begin, tmp.begin(), tmp.end());
}

// Fonction récursive
void PmergeMe::merge_insert_sort(std::vector<int> &arr)
{
	if (arr.size() <= 1)
		return;

	bool is_odd = arr.size() % 2 != 0;
	if (is_odd)
	{
		int last_int = arr.back();
		(void) last_int;
		arr.pop_back();
	}

	std::vector<std::pair<int, int> > tmp;
	for (size_t i = 0; i < arr.size(); i += 2)
	{
		tmp.push_back(std::make_pair(std::min(arr[i], arr[i + 1]), std::max(arr[i], arr[i + 1])));
	}
	print_sequence_paired(tmp);
	sort_pairs(tmp, 0, tmp.size());
	print_sequence_paired(tmp);




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
