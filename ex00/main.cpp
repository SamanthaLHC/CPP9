#include "btc.hpp"

//__________________________________________________________________________________________________
// ifstream objects maintient un stream buffer pour lire et ecrire depuis un fichier,
// construit un object type ifstream à partir d'un filename et l'ouvre avec le mode spécifié
// filebuf::open est appelé, si open échoue failbit flag is set.
// in: open pour la lecture (in par défaut pour ifstream, voir si je delete le deuxieme param)
// si l'ouverture du fichier ecóue return un NULL ptr
//__________________________________________________________________________________________________

int main(int ac, char **av)
{
	if (ac != 2)
		ERROR("USAGE: ./btc  <filename>");
	else
	{
		std::ifstream input_file(av[1], std::ifstream::in);
		if (input_file.good())
			BitcoinExchange btc_exchange(input_file);
		else
			ERROR("Error: no file available for i/o.");
	}
}