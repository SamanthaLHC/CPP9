#include "pmg.hpp"

void print_stepped(const std::vector<int> &_int_vector, size_t step)
{
	for (size_t idx=0; idx < _int_vector.size(); idx++)
	{
		std::cout << WHITE;
		if (idx % (step*2) == 0)
			std::cout << "(";
		if (idx % step == 0)
			std::cout << "[";
		std::cout << _int_vector[idx];
		if (idx % (step * 2) == (step * 2 - 1))
			std::cout << "]) ";
		else if (idx % step == (step - 1))
			std::cout << "] ";
		else
			std::cout << " ";
	}
	if (_int_vector.size() % step != 0)
		std::cout << "?])";
	std::cout << RES << std::endl;
}


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

std::vector<int>::iterator find_upper_bound(std::vector<int>::iterator first, std::vector<int>::iterator last, int val, size_t step)
{
	std::vector<int>::iterator it;
	int count, gap;
	count = std::distance(first, last) / step; // nombre d'unités
	while (count > 0)
	{
		it = first;
		gap = count / 2;
		std::advance(it, gap * step);
		if (!(val < *(it + step - 1))) // or: if (!comp(val,*it)), for version (2)
		{
			it += step;
			first = it;
			count -= gap + 1;
		}
		else
			count = gap;
	}
	return first;
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
// param step = le pas, le nombre d'elem pris en compte comme une unité
// size = le nombre d'elem restant selon le step
void PmergeMe::merge_insert_sort(std::vector<int> &arr, size_t step, size_t size)
{
	if (size <= 1)
		return;

	// _____________________________________________________________________________________________
	// step1: Split the collection in n/2 pairs of 2 elements and order these elements pairwise. If
	// the number of elements is odd, the last element of the collection isn't paired with any element.
	// _____________________________________________________________________________________________

	bool is_odd = size % 2 != 0;
	size -= is_odd; // last elem mis de côté pour ne s'occuper que d'une collec paire.
	size_t offset = step - 1;

	for (size_t i = 0; i < (step * size); i += 2 * step)
	{
		if (arr[i + offset] > arr[i + step + offset])
			std::swap_ranges(arr.begin() + i, arr.begin() + step + i, arr.begin() + step + i);
	}
	// _____________________________________________________________________________________________
	// step2: Recursively sort the pairs of elements by their highest value.
	// _____________________________________________________________________________________________

	merge_insert_sort(arr, step * 2, size / 2);

	std::vector<int> main_chain;
	std::vector<int> pend_low_value;

	// Insert the first "pair"
	INFO("Building Chain & Pend from:", "");
	print_stepped(arr, step);
	main_chain.insert(main_chain.end(), arr.begin(), arr.begin() + 2 * step); // on push les 2 premieres unités
	for (size_t i = step * 2; i < step * size; i += 2 * step)
	{
		// DEBUG("IN MAIN CHAIN_____ --> index: ", i + step + offset);
		// DEBUG("IN MAIN CHAIN_____ --> val: ", *(arr.begin() + i + step + offset));
		main_chain.insert(main_chain.end(), arr.begin() + i + step, arr.begin() + i + 2 * step); // on push l'unité la plus forte de la paire
		// DEBUG("IN PEND_____ --> index: ", i + offset);
		// DEBUG("IN PEND_____ --> val: ", *(arr.begin() + i + offset));
		pend_low_value.insert(pend_low_value.end(), arr.begin() + i, arr.begin() + i + step);	 // on push l'unité la plus faible
	}

	if (is_odd)
		pend_low_value.insert(pend_low_value.end(), arr.begin() + size * step, arr.end()); // on push odd one

	DEBUG("Main chain", "");
	print_sequence(main_chain);
	DEBUG("Pend elements: ", "");
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
		int distance = jacob_curr - jacob_prev;

		jacob_prev = jacob_curr;

		int dist_step = std::distance(it_curr_pend, pend_low_value.end() - 1) / step;

		if (distance >= dist_step)
			break;

		std::vector<int>::iterator it_chain = it_curr_chain + 2 * step * distance;
		std::vector<int>::iterator it_pend = it_curr_pend + step * distance;

		// insere à reculon depui l'idx de jacobstal jusquà l'idx de jacobsthal précédent
		do
		{
			it_pend -= step;

			it_chain -= 2 * step; // saute l'unité qui vient d'être inseré ou saute un elem de la main chain
			std::vector<int>::iterator insert_it =
				find_upper_bound(main_chain.begin(), it_chain, *(it_pend + offset), step);
			main_chain.insert(insert_it, it_pend, it_pend + step);
		} while (it_pend != it_curr_pend);

		it_curr_chain = it_curr_chain + 2 * step * distance;
		it_curr_pend = it_curr_pend + step * distance;
	}
	//	if (it_curr_pend != pend_low_value.end())
	//		it_curr_pend++;
	DEBUG("Remains elemnts in pend: ", std::distance(it_curr_pend, pend_low_value.end()));
	print_stepped(arr, step);
	print_sequence(main_chain);
	while (it_curr_pend != pend_low_value.end())
	{
		DEBUG("running for extr INSERTS", "");
		std::vector<int>::iterator insert_it =
			find_upper_bound(main_chain.begin(), main_chain.end(), *(it_curr_pend + offset), step);
		main_chain.insert(insert_it, it_curr_pend, it_curr_pend + step);
		if (std::distance(it_curr_pend, pend_low_value.end()) < static_cast<int>(step))
		{
			DEBUG("Remains elemnts in pend: ", std::distance(it_curr_pend, pend_low_value.end()));
			break;
		}
		it_curr_pend += step;
		DEBUG("Remains elemnts in pend: ", std::distance(it_curr_pend, pend_low_value.end()));
	}
	INFO("pre-erase", "");
	arr.erase(arr.begin(), arr.end()); // begin() + (size + is_odd) * step);
	arr.insert(arr.begin(), main_chain.begin(), main_chain.end());

	INFO("as sorted when leaving step: ", step);
	print_stepped(arr, step);
	clock_t end_time = clock();
	_vec_time = (end_time - _begin_vec) * 1000000 / CLOCKS_PER_SEC;
}

void PmergeMe::launch()
{
	merge_insert_sort(_int_vector, 1, _int_vector.size());
	// merge_insert_sort(_int_deque);
	print_result();
	print_time();
}
