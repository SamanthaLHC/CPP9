#ifndef GROUPIT_HPP
#define GROUPIT_HPP

#include "pmg.hpp"

////////////////////////////////////////////////////////////
// Iterator used to sort views of the collection

template <typename Iterator>
class group_iterator
{
private:
	group_iterator(){};

	Iterator _it;
	std::size_t _size;

public:
	////////////////////////////////////////////////////////////
	// Public types

	typedef std::random_access_iterator_tag iterator_category;
	typedef Iterator iterator_type;
	typedef typename std::iterator_traits<Iterator>::value_type value_type;
	typedef typename std::iterator_traits<Iterator>::difference_type difference_type;
	typedef typename std::iterator_traits<Iterator>::pointer pointer;
	typedef typename std::iterator_traits<Iterator>::reference reference;

	////////////////////////////////////////////////////////////
	// Constructors

	group_iterator(Iterator it, std::size_t size) : _it(it),
													_size(size)
	{
	}

	////////////////////////////////////////////////////////////
	// Members access

	iterator_type base() const
	{
		return _it;
	}

	std::size_t size() const
	{
		return _size;
	}

	////////////////////////////////////////////////////////////
	// Element access

	reference operator*() const
	{
		return _it[_size - 1];
	}

	pointer operator->() const
	{
		return &(operator*());
	}

	////////////////////////////////////////////////////////////
	// Increment/decrement operators

	group_iterator &operator++()
	{
		_it += _size;
		return *this;
	}

	group_iterator operator++(int)
	{
		group_iterator tmp = *this;
		operator++();
		return tmp;
	}

	group_iterator &operator--()
	{
		_it -= _size;
		return *this;
	}

	group_iterator operator--(int)
	{
		group_iterator tmp = *this;
		operator--();
		return tmp;
	}

	group_iterator &operator+=(std::size_t increment)
	{
		_it += _size * increment;
		return *this;
	}

	group_iterator &operator-=(std::size_t increment)
	{
		_it -= _size * increment;
		return *this;
	}

	////////////////////////////////////////////////////////////
	// Elements access operators

	value_type operator[](std::size_t pos)
	{
		std::cout << "Accessing iterator size=" << _size << " at pos=" << pos << std::endl;
		return _it[pos * _size + _size - 1];
	}

	value_type operator[](std::size_t pos) const
	{
		std::cout << "Const-Accessing iterator size=" << _size << " at pos=" << pos << std::endl;
		return _it[pos * _size + _size - 1];
	}

	bool operator<(int rhs) const
	{
		return *(this->base()) < rhs;
	}
};

template <typename Iterator1, typename Iterator2>
void iter_swap(group_iterator<Iterator1> lhs, group_iterator<Iterator2> rhs)
{
	std::swap_ranges(lhs.base(), lhs.base() + lhs.size(), rhs.base());
}

////////////////////////////////////////////////////////////
// Comparison operators

template <typename Iterator1, typename Iterator2>
bool operator==(const group_iterator<Iterator1> &lhs, const group_iterator<Iterator2> &rhs)
{
	return lhs.base() == rhs.base();
}

template <typename Iterator1, typename Iterator2>
bool operator!=(const group_iterator<Iterator1> &lhs, const group_iterator<Iterator2> &rhs)
{
	return lhs.base() != rhs.base();
}

////////////////////////////////////////////////////////////
// Relational operators

template <typename Iterator1, typename Iterator2>
bool operator<(const group_iterator<Iterator1> &lhs, const group_iterator<Iterator2> &rhs)
{
	return lhs.base() < rhs.base();
}

template <typename Iterator1, typename Iterator2>
bool operator<=(const group_iterator<Iterator1> &lhs, const group_iterator<Iterator2> &rhs)
{
	return lhs.base() <= rhs.base();
}

template <typename Iterator1, typename Iterator2>
bool operator>(const group_iterator<Iterator1> &lhs, const group_iterator<Iterator2> &rhs)
{
	return lhs.base() > rhs.base();
}

template <typename Iterator1, typename Iterator2>
bool operator>=(const group_iterator<Iterator1> &lhs, const group_iterator<Iterator2> &rhs)
{
	return lhs.base >= rhs.base();
}

template <typename Compare>
struct Comparator
{
	// For upper-bound
	bool operator()(const int &lhs, const group_iterator<std::vector<int>::iterator> &rhs)
	{
		Compare cmp;
		std::cout << "Comparing int lhs=" << lhs << " with group-it over rhs=" << *rhs << std::endl;
		return cmp(lhs, *rhs);
	}

	// For lower-bound
	bool operator()(const group_iterator<std::vector<int>::iterator> &lhs, const int &rhs)
	{
		Compare cmp;
		std::cout << "Comparing group it over lhs=" << *lhs << " with int rhs=" << rhs << std::endl;
		return cmp(*lhs, rhs);
	}
};

////////////////////////////////////////////////////////////
// Arithmetic operators

template <typename Iterator>
group_iterator<Iterator> operator+(group_iterator<Iterator> it, std::size_t size)
{
	return it += size;
}

template <typename Iterator>
group_iterator<Iterator> operator+(std::size_t size, group_iterator<Iterator> it)
{
	return it += size;
}

template <typename Iterator>
group_iterator<Iterator> operator-(group_iterator<Iterator> it, std::size_t size)
{
	return it -= size;
}

template <typename Iterator>
typename group_iterator<Iterator>::difference_type operator-(const group_iterator<Iterator> &lhs, const group_iterator<Iterator> &rhs)
{
	return (lhs.base() - rhs.base()) / lhs.size();
}

////////////////////////////////////////////////////////////
// Construction function

template <typename Iterator>
group_iterator<Iterator> make_group_iterator(Iterator it, std::size_t size)
{
	return group_iterator<Iterator>(it, size);
}

template <typename Iterator>
group_iterator<Iterator> make_group_iterator(group_iterator<Iterator> it, std::size_t size)
{
	return group_iterator<Iterator>(it.base(), size * it.size());
}

///////////////////////////////////////////////////////////
// Printing utilities

template <typename T>
void print_seq(const T &array)
{
	for (std::vector<int>::const_iterator it = array.begin(); it != array.end(); ++it)
	{
		if (it != array.begin())
			std::cout << " ";
		std::cout << *it;
	}
	std::cout << std::endl;
}

template <typename Iterator>
void print_group(group_iterator<Iterator> &it)
{
	for (size_t j = 0; j < it.size(); j++)
	{
		if (j == 0)
			std::cout << "[";
		else
			std::cout << " ";
		std::cout << it.base()[j];
		if (j == it.size() - 1)
			std::cout << "]";
	}
}

template <typename Iterator>
void print_groups(group_iterator<Iterator> &begin, group_iterator<Iterator> &end)
{
	for (group_iterator<Iterator> it = begin; it != end; ++it)
	{
		if (it != begin)
			std::cout << " ";
		print_group(it);
	}
	std::cout << std::endl;
}

template <typename T>
void print_chain(const T &chain)
{
	for (typename T::const_iterator it = chain.begin(); it != chain.end(); ++it)
	{
		if (it != chain.begin())
			std::cout << " ";
		group_iterator<std::vector<int>::iterator> git = *(it);
		print_group(git);
	}
	std::cout << std::endl;
}

template <typename Iterator>
void print_pend(Iterator &begin, const Iterator &end)
{
	for (Iterator it = begin; it != end; ++it)
	{
		if (it != begin)
			std::cout << " ";
		group_iterator<std::vector<int>::iterator> git = *(*(it));
		print_group(git);
	}
	std::cout << std::endl;
}

std::ostream &do_depth(int depth)
{
	const int indent = 4;
	for (int i = 0; i < depth * indent; ++i)
		std::cout << ((i % indent) ? " " : "|");
	std::cout << "{" << depth << "} ";
	return std::cout;
}

#endif