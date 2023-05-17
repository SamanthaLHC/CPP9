// #include "BitcoinExchange.cpp"
#include "btc.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
		ERROR("USAGE: ./btc  <filename>")
	else
	{
		// ifstream objects maintient un stream buffer pour lire et ecrire depuis un fichier.
		// construit un object type ifstream à partir d'un filename et l'ouvre avec le mode spécifié
		// filebuf::open est appelé si open échoue failbit flag is set.
		// in: open pour la lecture (in par défaut pour ifstream, voir si je delete le deuxieme param)
		std::ifstream input_file(av[1], std::ifstream::in);
		if (input_file.fail() == true)
			ERROR("Error: no file available for i/o.")
		else
			BitcoinExchange btc(input_file);
	}
}
