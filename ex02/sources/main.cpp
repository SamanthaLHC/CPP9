#include "pmg.hpp"

int main(int ac, char **av)
{
	if (ac < 2)
	{
		ERROR("USAGE: ./PmergeMe  <numeric sequence>");
		return 1;
	}
	else
	{
		int i = 1;
		std::deque<int> int_deque;
		std::vector<int> int_vector;

		while (i < ac)
		{
			std::istringstream str_to_conv(av[i]);
			int elem_to_check;

			if ((str_to_conv >> elem_to_check && str_to_conv.rdbuf()->in_avail() == 0) && (elem_to_check >= 0))
			{
				clock_t begin_vec = clock();
				PmergeMe pmg_init_time = PmergeMe();
				pmg_init_time.set_time_begin_vec(begin_vec);
				int_vector.push_back(elem_to_check);
				int_deque.push_back(elem_to_check);
			}
			else
			{
				PRINT("Error: invalid sequence. Only positives integers required.", "");
				return 1;
			}
			i++;
		}
		PmergeMe pmg(int_deque, int_vector, ac - 1);
	}
	return 0;
}
