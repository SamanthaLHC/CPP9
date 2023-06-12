#ifndef PMERGEME_HPP
#define PMERGEME_HPP

class PmergeMe
{
public:
	// coplian form_____________________________________________________________

	PmergeMe(std::deque<int> int_deque, std::vector<int> int_vector, int ac);
	PmergeMe(PmergeMe const &cpy);
	~PmergeMe();

	PmergeMe &operator=(PmergeMe const &rhs);

private:
	//__________________________________members functions
	// useless constructor
	PmergeMe();

	// utils
	void print_pairs();
	void print_sequence(std::vector<int> int_vector);
	void print_sequence(std::deque<int> int_deque);

		// sort algo
	void make_pairs();
	void merge_sort(std::vector<int> &vector, int start, int end);
	void insert_sort(std::vector<int> &vector, int start, int end);
	void insert_sort(std::vector<int> &vector, int start, int end);
	void merge(std::vector<int> &vector, int start, int mid, int end);
	void sort(std::vector<int> int_vector);

	// measure time

	//__________________________________attribute members

	int					_count_elem;
	std::deque<int>		_int_deque;
	std::vector<int>	_int_vector;
};

#endif