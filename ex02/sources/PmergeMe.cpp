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
	if (n == 1)
		return 1;

	int a = 0;
	int b = 1;

	for (int i = 2; i <= n; i++)
	{
		int tmp = b;
		b = a + 2 * b;
		a = tmp;
	}

	return b;
}

void PmergeMe::insertion_sort(std::vector<int> &arr, int start, int end)
{
	for (int i = start + 1; i <= end; i++)
	{
		int key = arr[i];
		int j = i - 1;

		while (j >= start && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j--;
		}

		arr[j + 1] = key;
	}
}
void PmergeMe::merge_insertion_sort(std::vector<int> &arr)
{
	int size = arr.size();
	if (size <= 1)
		return;

	int middle = size / 2;

	std::vector<int> left(arr.begin(), arr.begin() + middle);
	std::vector<int> right(arr.begin() + middle, arr.end());

	merge_insertion_sort(left);
	merge_insertion_sort(right);

	insertion_sort(arr, 0, middle - 1);
	insertion_sort(arr, middle, size - 1);

	std::vector<int> tmp;

	size_t i = 0;
	size_t j = 0;

	while (i < left.size() && j < right.size())
	{
		if (left[i] <= right[j])
		{
			tmp.push_back(left[i]);
			i++;
		}
		else
		{
			tmp.push_back(right[j]);
			j++;
		}
	}

	while (i < left.size())
	{
		tmp.push_back(left[i]);
		i++;
	}

	while (j < right.size())
	{
		tmp.push_back(right[j]);
		j++;
	}

	// Copy sorted elements back to original array
	for (size_t k = 0; k < tmp.size(); k++)
	{
		arr[k] = tmp[k];
	}

	clock_t end_time = clock();
	_vec_time = (end_time - _begin_vec) * 1000000 / CLOCKS_PER_SEC;
}


void PmergeMe::insertion_sort(std::deque<int> &arr, int start, int end)
{
	for (int i = start + 1; i <= end; i++)
	{
		int key = arr[i];
		int j = i - 1;

		while (j >= start && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j--;
		}

		arr[j + 1] = key;
	}
}
void PmergeMe::merge_insertion_sort(std::deque<int> &arr)
{
	int size = arr.size();
	if (size <= 1)
		return;

	int middle = size / 2;

	std::deque<int> left(arr.begin(), arr.begin() + middle);
	std::deque<int> right(arr.begin() + middle, arr.end());

	merge_insertion_sort(left);
	merge_insertion_sort(right);

	insertion_sort(arr, 0, middle - 1);
	insertion_sort(arr, middle, size - 1);

	std::deque<int> tmp;

	size_t i = 0;
	size_t j = 0;

	while (i < left.size() && j < right.size())
	{
		if (left[i] <= right[j])
		{
			tmp.push_back(left[i]);
			i++;
		}
		else
		{
			tmp.push_back(right[j]);
			j++;
		}
	}

	while (i < left.size())
	{
		tmp.push_back(left[i]);
		i++;
	}

	while (j < right.size())
	{
		tmp.push_back(right[j]);
		j++;
	}

	// Copy sorted elements back to original array
	for (size_t k = 0; k < tmp.size(); k++)
	{
		arr[k] = tmp[k];
	}

	clock_t end_time = clock();
	_deque_time = (end_time - _begin_deq) * 1000000 / CLOCKS_PER_SEC;
}



void PmergeMe::launch()
{
	merge_insertion_sort(_int_vector);
	merge_insertion_sort(_int_deque);
	print_result();
	print_time();
}
