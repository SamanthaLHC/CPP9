#include "pmg.hpp"

//==================================================================================================
//		constructors / destructors
//==================================================================================================
PmergeMe::PmergeMe() {} // non utilisé, mis en private

PmergeMe::PmergeMe(std::deque<int> _int_deque, std::vector<int> _int_vector, int ac) : _last_int(0),
																					   _count_elem(ac),
																					   _int_deque(_int_deque),
																					   _int_vector(_int_vector)
{

	sort(_int_deque);
	sort(_int_vector);
}

PmergeMe::PmergeMe(PmergeMe const &cpy) : _last_int(cpy._last_int),
										  _count_elem(cpy._count_elem),
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
		_last_int = rhs._last_int;
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

void PmergeMe::print_sequence(std::deque<std::pair<int, int> >)
{
	std::deque<std::pair<int, int> >::iterator it = _deque_pairs.begin();
	for (; it != _deque_pairs.end(); it++)
	{
		std::cout << it->first;
		std::cout << " ";
		std::cout << it->second;
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

void PmergeMe::print_sequence(std::vector<std::pair<int, int> >)
{
	std::vector<std::pair<int, int> >::iterator it = _vector_pairs.begin();
	for (; it != _vector_pairs.end(); it++)
	{
		std::cout << it->first;
		std::cout << " ";
		std::cout << it->second;
	}
	std::cout << std::endl;
}

void PmergeMe::print_pairs()
{
	int i = 0;
	for (; i < _deque_pairs.size(); i++)
	{
		std::cout << CYAN << "[ " << _deque_pairs[i].first << " "
				  << _deque_pairs[i].second << " ]" << RES << std::endl;
	}
}

// sort

void PmergeMe::make_pairs()
{
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

		if (cell.first > cell.second)
			std::swap(cell.first, cell.second);
		_deque_pairs.push_back(cell);
	}
}

void PmergeMe::merge(std::vector<std::pair<int, int> > _vector_pairs, int start, int mid, int end)
{
	std::vector<std::vector<int> > first_half;
	std::vector<std::vector<int> > second_half;


}

void PmergeMe::merge_sort(std::deque<std::pair<int, int> > _deque_pairs, int start, int end)
{
	(void)start;
	(void)end;

	if (_deque_pairs.empty())
		print_sequence(_deque_pairs);
	// declarer end
	// declarer start
	// declarer une nouvelle deque sorting_deque
	// calculer mid
}

void PmergeMe::merge_sort(std::vector<std::pair<int, int> > _vector_pairs, int start, int end)
{
	if (start >= end)
		return;
	int mid = (start + end) / 2;
	merge_sort(_vector_pairs, start, mid);
	merge_sort(_vector_pairs, mid + 1, end);
	merge(_vector_pairs, start, mid, end);
}

void PmergeMe::sort(std::vector<int> _int_vector)
{
	DEBUG("here sort vector: ", "");
	std::cout << WHITE << "Before: ";
	print_sequence(_int_vector);
	make_pairs();
	print_pairs();
	print_sequence(_vector_pairs);
	merge_sort(_vector_pairs, 0, _vector_pairs.size() - 1);
}

void PmergeMe::sort(std::deque<int> _int_deque)
{
	DEBUG("here sort deque: ", "");
	print_sequence(_int_deque);
}
