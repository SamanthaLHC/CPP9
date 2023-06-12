#include "pmg.hpp"

//==================================================================================================
//		constructors / destructors
//==================================================================================================
PmergeMe::PmergeMe() {} // non utilisé, mis en private

PmergeMe::PmergeMe(std::deque<int> _int_deque, std::vector<int> _int_vector, int ac) : _count_elem(ac),
																					   _int_deque(_int_deque),
																					   _int_vector(_int_vector)
{

	launch(_int_vector);
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

// utils/debugg
void PmergeMe::print_sequence(std::deque<int> _int_deque)
{
	std::deque<int>::iterator it = _int_deque.begin();
	for (; it != _int_deque.end(); it++)
	{
		std::cout << *it;
		std::cout << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::print_sequence(std::vector<int> _int_vector)
{
	std::vector<int>::iterator it = _int_vector.begin();
	for (; it != _int_vector.end(); it++)
	{
		std::cout << *it;
		std::cout << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::merge_sort(std::vector<int> &vector, int start, int mid, int end)
{
	int size_first_half = start - end + 1;
	int size_second_half = mid - start;
	std::vector<int> first_half(vector.begin() + end, vector.begin() + start + 1);
	std::vector<int> second_half(vector.begin() + start + 1, vector.begin() + mid + 1);
	int first_arr_idx = 0;
	int second_arr_idx = 0;
	for (int i = end; i < mid - end + 1; i++)
	{
		if (second_arr_idx == size_second_half)
		{
			vector[i] = first_half[first_arr_idx];
			first_arr_idx++;
		}
		else if (first_arr_idx == size_first_half)
		{
			vector[i] = second_half[second_arr_idx];
			second_arr_idx++;
		}
		else if (second_half[second_arr_idx] > first_half[first_arr_idx])
		{
			vector[i] = first_half[first_arr_idx];
			first_arr_idx++;
		}
		else
		{
			vector[i] = second_half[second_arr_idx];
			second_arr_idx++;
		}
	}
}

void PmergeMe::insert_sort(std::vector<int> &vector, int start, int end)
{
}

void PmergeMe::sort(std::vector<int> &vector, int start, int end)
{
	//clock begin
	if (end - start > (vector.size() / 2))
	{
		int mid = ((start + end) / 2);
		sort(vector, start, end);
		sort(vector, start + 1, end);
		merge_sort(vector, start, mid, end);
	}
	else
		insert_sort(vector, start, end);

	//clock end
}

void PmergeMe::launch()
{
	sort(_int_vector, 0, _int_vector.size() - 1);
	// PRINT(time_vector_sort);
}
