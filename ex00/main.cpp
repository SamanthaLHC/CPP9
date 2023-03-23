#include "BitcoinExchange.cpp"

int main(int ac, char **av)
{
	if (ac < 2)
		std::cerr << RED << "Error: could not open file." << RES << std::endl;
	else
	{
		BitcoinExchange btc(av[1]);
	}
}

