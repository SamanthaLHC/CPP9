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
	void print_sequence(std::deque<std::pair<int, int> >);
	void print_sequence(std::deque<int> int_deque);
	void print_sequence(std::vector<std::pair<int, int> >);

		// sort algo
	void make_pairs();
	// trouver un param pour faire un overload
	//  void make_pairs();

	void merge_sort(std::vector<std::pair<int, int> >, int start, int end);
	void merge_sort(std::deque<std::pair<int, int> >, int start, int end);

	void merge(std::vector<std::pair<int, int> > _vector_pairs, int start, int mid, int end);

	void sort(std::vector<int> int_vector);
	void sort(std::deque<int> int_deque);

	// measure time

	//__________________________________attribute members

	int								_last_int;
	int								_count_elem;

	std::deque<int> 				 _int_deque;
	std::deque<std::pair<int, int> > _deque_pairs;
	std::deque<std::pair<int, int> > _deque_merged;

	std::vector<int> 				  _int_vector;
	std::vector<std::pair<int, int> > _vector_pairs;
	std::vector<std::pair<int, int> > _vector_merged;
	std::vector<int> 				  _vector_result;
};

#endif