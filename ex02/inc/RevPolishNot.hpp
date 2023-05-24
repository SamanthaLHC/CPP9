#ifndef PMERGEME
#define PMERGEME

class PmergeMe
{
public:
	// coplian form_____________________________________________________________

	PmergeMe(std::string const &arg);
	PmergeMe(PmergeMe const &cpy);
	~PmergeMe();

	PmergeMe &operator=(PmergeMe const &rhs);

private:
	//__________________________________members functions
	// useless constructor
	PmergeMe();

	// utils


	//__________________________________attribute members


};

#endif