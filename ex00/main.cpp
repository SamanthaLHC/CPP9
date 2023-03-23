#include "BitcoinExchange.cpp"

int main(int ac, char **av)
{
	if (ac < 2)
		std::cerr << RED << "Error: could not open file." << RES << std::endl;
	else
	{
		std::ifstream input_file(av[1], std::ifstream::in);
		BitcoinExchange btc(input_file);
	}
}

