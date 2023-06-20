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
																					   _int_vector(_int_vector),
																					   _begin_vec(0),
																					   _begin_deq(0)
{
	std::cout << WHITE << "Before:	";
	print_sequence(_int_vector);
	launch();
}

PmergeMe::PmergeMe(PmergeMe const &cpy) : _count_elem(cpy._count_elem),
										  _int_deque(cpy._int_deque),
										  _int_vector(cpy._int_vector),
										  _begin_vec(cpy._begin_vec),
										  _begin_deq(cpy._begin_deq)

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
		_begin_vec = rhs._begin_vec;
		_begin_deq = rhs._begin_deq;
	}
	return *this;
}

//==================================================================================================
//		members functions
//==================================================================================================

// print

void PmergeMe::print_sequence(std::deque<int> _int_deque)
{
	std::deque<int>::iterator it = _int_deque.begin();
	for (; it != _int_deque.end(); it++)
	{
		std::cout << WHITE << *it;
		std::cout << " ";
	}
	std::cout << RES << std::endl;
}

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
	// print_sequence(_int_vector);
	print_sequence(_int_deque);
}

void PmergeMe::print_time()
{
	std::cout << WHITE << "Time to process a range of: " << _count_elem
			  << " elements with std::vector : " << _vec_time << " us" << RES << std::endl;
	std::cout << WHITE << "Time to process a range of: " << _count_elem
			  << " elements with std::deque : " << _deque_time << " us" << RES << std::endl;
}

// measure time

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

// sort__________vector

void PmergeMe::insert_sort(std::vector<int> &vector_arr, int start, int end)
{
	for (int i = start; i < end; i++)
	{
		int tmp = vector_arr[i + 1];
		int j = i + 1;
		while (j > start && vector_arr[j - 1] > tmp)
		{
			vector_arr[j] = vector_arr[j - 1];
			j--;
		}
		vector_arr[j] = tmp;
	}
	std::vector<int> tmp(vector_arr.begin() + start, vector_arr.begin() + end - 1);
}

void PmergeMe::merge_sort(std::vector<int> &vector_arr, int start, int mid, int end)
{
	int size_first_half = mid - start + 1;
	int size_second_half = end - mid;
	std::vector<int> first_half(vector_arr.begin() + start, vector_arr.begin() + mid + 1);
	std::vector<int> second_half(vector_arr.begin() + mid + 1, vector_arr.begin() + end + 1);
	int first_arr_idx = 0;
	int second_arr_idx = 0;
	for (int i = start; i < end - start + 1; i++)
	{
		if (second_arr_idx == size_second_half)
		{
			vector_arr[i] = first_half[first_arr_idx];
			first_arr_idx++;
		}
		else if (first_arr_idx == size_first_half)
		{
			vector_arr[i] = second_half[second_arr_idx];
			second_arr_idx++;
		}
		else if (second_half[second_arr_idx] > first_half[first_arr_idx])
		{
			vector_arr[i] = first_half[first_arr_idx];
			first_arr_idx++;
		}
		else
		{
			vector_arr[i] = second_half[second_arr_idx];
			second_arr_idx++;
		}
	}
}

void PmergeMe::sort(std::vector<int> &vector_arr, int start, int end)
{
	int size = vector_arr.size() / 2;
	if (end - start > size)
	{
		int mid = ((start + end) / 2);
		sort(vector_arr, start, mid);
		sort(vector_arr, mid + 1, end);
		merge_sort(vector_arr, start, mid, end);
	}
	else
		insert_sort(vector_arr, start, end);

	clock_t end_time = clock();
	_vec_time = (end_time - _begin_vec) * 1000000 / CLOCKS_PER_SEC;
}



// sort__________deque

void PmergeMe::insert_sort(std::deque<int> &deque_arr, int start, int end)
{
	for (int i = start; i < end; i++)
	{
		int tmp = deque_arr[i + 1];
		int j = i + 1;
		while (j > start && deque_arr[j - 1] > tmp)
		{
			deque_arr[j] = deque_arr[j - 1];
			j--;
		}
		deque_arr[j] = tmp;
	}
	std::deque<int> tmp(deque_arr.begin() + start, deque_arr.begin() + end - 1);
}

void PmergeMe::merge_sort(std::deque<int> &deque_arr, int start, int mid, int end)
{
	int size_first_half = mid - start + 1;
	int size_second_half = end - mid;
	std::deque<int> first_half(deque_arr.begin() + start, deque_arr.begin() + mid + 1);
	std::deque<int> second_half(deque_arr.begin() + mid + 1, deque_arr.begin() + end + 1);
	int first_arr_idx = 0;
	int second_arr_idx = 0;
	for (int i = start; i < end - start + 1; i++)
	{
		if (second_arr_idx == size_second_half)
		{
			deque_arr[i] = first_half[first_arr_idx];
			first_arr_idx++;
		}
		else if (first_arr_idx == size_first_half)
		{
			deque_arr[i] = second_half[second_arr_idx];
			second_arr_idx++;
		}
		else if (second_half[second_arr_idx] > first_half[first_arr_idx])
		{
			deque_arr[i] = first_half[first_arr_idx];
			first_arr_idx++;
		}
		else
		{
			deque_arr[i] = second_half[second_arr_idx];
			second_arr_idx++;
		}
	}
}

void PmergeMe::sort(std::deque<int> &deque_arr, int start, int end)
{
	int size = deque_arr.size() / 2;
	if (end - start > size)
	{
		int mid = ((start + end) / 2);
		sort(deque_arr, start, mid);
		sort(deque_arr, mid + 1, end);
		merge_sort(deque_arr, start, mid, end);
	}
	else
		insert_sort(deque_arr, start, end);

	clock_t end_time = clock();
	_deque_time = (end_time - _begin_deq) * 1000000 / CLOCKS_PER_SEC;
}

void PmergeMe::launch()
{
	sort(_int_vector, 0, _int_vector.size() - 1);
	sort(_int_deque, 0, _int_deque.size() - 1);
	print_result();
	print_time();
}