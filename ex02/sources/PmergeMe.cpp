#include "pmg.hpp"

//==================================================================================================
//		constructors / destructors
//==================================================================================================
PmergeMe::PmergeMe():	_count_elem(0),
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

}

//measure time

void PmergeMe::set_time_begin_vec(clock_t time)
{
	_begin_vec = time;
}

clock_t PmergeMe::get_time_begin_vec()
{
	return _begin_vec;
}

double  PmergeMe::get_vec_time()
{
	return _vec_time;
}


//sort
void PmergeMe::merge_sort(std::vector<int> &vector_arr, int start, int mid, int end)
{
	int size_first_half = mid - end + 1;
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
	_vec_time = (end_time - _begin_vec)  / double(CLOCKS_PER_SEC);
}

void PmergeMe::launch()
{
	sort(_int_vector, 0, _int_vector.size() - 1);
	print_result();
	
}


//TODO is sorted if oui affichage if no error
//TODO affichage complient