#ifndef PMERGEME_HPP
#define PMERGEME_HPP

class PmergeMe
{
public:
	// coplian form_____________________________________________________________

	PmergeMe(std::deque<int> int_deque, std::list<int> int_list, int ac);
	PmergeMe(PmergeMe const &cpy);
	~PmergeMe();

	PmergeMe &operator=(PmergeMe const &rhs);

private:
	//__________________________________members functions
	// useless constructor
	PmergeMe();

	// utils
	void print_sequence();
	void print_pairs();
	void print_sequence_list();

	// sort algo
	void sort_in_deque();
	void make_pairs_in_deque();
	void merge_sort();
	void merge();
	void sort_in_list();

	//measure time


	//__________________________________attribute members

	int												_last_int;
	std::deque<int>									_int_deque;
	std::list<int>									_int_list;
	int 											_count_elem;
	std::deque<std::pair<int, int> >				_deque_pairs;


};

#endif