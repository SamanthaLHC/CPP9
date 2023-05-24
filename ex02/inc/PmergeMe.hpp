#ifndef PMERGEME_HPP
#define PMERGEME_HPP

class PmergeMe
{
public:
	// coplian form_____________________________________________________________

	PmergeMe(std::deque<int> int_array, std::list<int> int_list, int ac);
	PmergeMe(PmergeMe const &cpy);
	~PmergeMe();

	PmergeMe &operator=(PmergeMe const &rhs);

private:
	//__________________________________members functions
	// useless constructor
	PmergeMe();

	// utils
	
	//parsing and check


	// sort algo

	//measure time


	//__________________________________attribute members

	int _count_elem;


};

#endif