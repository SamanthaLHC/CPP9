#ifndef PMERGEME_HPP
#define PMERGEME_HPP

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

private:
	//__________________________________members functions
	// useless constructor

	// utils
	void print_sequence(std::vector<int> int_vector);
	void print_result();
	void print_time();

	// void print_sequence(std::deque<int> int_deque);

	// sort algo
	void launch();
	void sort(std::vector<int> &vector, int start, int end);
	void merge_sort(std::vector<int> &vector, int start, int mid, int end);
	void insert_sort(std::vector<int> &vector, int start, int end);

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