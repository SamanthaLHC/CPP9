#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include "pmg.hpp"

class PmergeMe
{
public:
	// coplian form_____________________________________________________________

	PmergeMe();
	PmergeMe(std::deque<int> int_deque, std::vector<int> int_vector, int ac);
	PmergeMe(PmergeMe const &cpy);
	~PmergeMe();

	PmergeMe &operator=(PmergeMe const &rhs);

	// measure time
	void set_time_begin_vec(clock_t time);
	clock_t get_time_begin_vec();
	double get_vec_time();

	void set_time_begin_deq(clock_t time);
	clock_t get_time_begin_deq();
	double get_deq_time();

private:
	//__________________________________members functions
	// useless constructor

	// utils
	void print_sequence(std::vector<int> int_vector);
	void print_sequence(std::deque<int> int_deque);
	void print_result();
	void print_time();
	void launch();
	int jacobsthal(int n);

	// sort algo
	std::vector<std::pair<int, int> > merge(const std::vector<int> &input);

	void merge_insert_sort(std::vector<int> &input_list);

	//__________________________________attribute members

	int _count_elem;
	std::deque<int> _int_deque;
	std::vector<int> _int_vector;
	double _vec_time;
	double _deque_time;
	clock_t _begin_vec;
	clock_t _begin_deq;
};

#endif