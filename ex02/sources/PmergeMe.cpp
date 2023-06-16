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
	std::vector<std::pair<int, int> >::iterator it = _int_vector.begin();
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

bool compare_pair(const std::pair<int, int> &lhs, const std::pair<int, int> &rhs)
{
	return lhs.second < rhs.second;
}

int PmergeMe::jacobsthal(int n)
{
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	return jacobsthal(n - 1) + 2 * jacobsthal(n - 2);
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

// sort
void PmergeMe::merge_insert_sort(std::vector<int> &arr, size_t begin, size_t size)
{
	if (size <= 1)
		return;

	// _____________________________________________________________________________________________
	// step1: Split the collection in n/2 pairs of 2 elements and order these elements pairwise. If
	// the number of elements is odd, the last element of the collection isn't paired with any element.
	// _____________________________________________________________________________________________

	bool is_odd = size % 2 != 0;
	size -= is_odd; // last elem mis de côté pour ne s'occuper que d'une collec paire.

	for (size_t i = begin; i < size; i += 2)
	{
		if (arr[i] > arr[i + 1])
			std::swap(arr[i], arr[i + 1]);
	}

	// _____________________________________________________________________________________________
	// step2: Recursively sort the pairs of elements by their highest value.
	// _____________________________________________________________________________________________

	int mid = size / 2;
	merge_insert_sort(arr, begin, mid);
	merge_insert_sort(arr, (begin + mid), mid);

	DEBUG("vector array: ", "");
	print_sequence(arr);


	std::vector<int> main_chain;
	std::vector<int> pend_low_value;

	for (size_t i = begin; i < size; i += 2)
	{
		main_chain.push_back(arr[i + 1]);
		pend_low_value.push_back(arr[i]);
	}

	if (is_odd)
		pend_low_value.push_back(arr[size]);

	DEBUG("is odd: ", is_odd);
	DEBUG("main chain: ", "");
	print_sequence(main_chain);
	DEBUG("pend elem chain: ", "");
	print_sequence(pend_low_value);

	// _____________________________________________________________________________________________
	// step3: Insert the pend elements into the main chain.
	// _____________________________________________________________________________________________

	// index jacobsthal pour inserer, calculé avec la dist entre les nombres de la suite en sautant 0, 1 ,1
	size_t jacob_prev = jacobsthal(2);

	std::vector<int>::iterator it_curr_chain = main_chain.begin(); // highest elem
	std::vector<int>::iterator it_curr_pend = pend_low_value.begin();

	for (size_t i = 3;; i++)
	{
		size_t jacob_curr = jacobsthal(i);
		int distance = jacob_prev - jacob_curr;
		jacob_prev = jacob_curr;

		if (distance >= std::distance(it_curr_pend, pend_low_value.end() - 1))
			break;

		std::vector<int>::iterator it_chain = it_curr_chain + 2 * distance;
		std::vector<int>::iterator it_pend = it_curr_pend + distance;

		// insere à reculon depui l'idx de jacobstal jusquà l'idx de jacobsthal précédent
		do
		{
			it_pend--;
			it_chain -= 2; // saute l'elem qui vient d'être inseré ou saute un elem de la main chain
			std::vector<int>::iterator insert_it =
				std::upper_bound(main_chain.begin(), it_chain, *it_pend);
			main_chain.insert(insert_it, *it_pend);
		} while (it_pend != it_curr_pend);

		it_curr_chain = it_curr_chain + 2 * distance;
		it_curr_pend = it_curr_pend + distance;
	}
	if (is_odd)
	{
		std::vector<int>::iterator insert_it =
			std::upper_bound(main_chain.begin(), main_chain.end(), pend_low_value.back());
		main_chain.insert(insert_it, pend_low_value.back());
	}
	arr.erase(arr.begin() + begin, arr.begin() + begin + size);
	arr.insert(arr.begin() + begin, main_chain.begin(), main_chain.end());

	clock_t end_time = clock();
	_vec_time = (end_time - _begin_vec) * 1000000 / CLOCKS_PER_SEC;
}

void PmergeMe::launch()
{
	merge_insert_sort(_int_vector, 0, _int_vector.size());
	// merge_insert_sort(_int_deque);
	print_result();
	print_time();
}
