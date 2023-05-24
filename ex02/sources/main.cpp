#include "rpn.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		ERROR("USAGE: ./btc  <numeric sequence>");
		return 1;
	}
	else
		PmergeMe pmg(av[1]);
	return 0;
}