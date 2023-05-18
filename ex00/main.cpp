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
		ERROR("USAGE: ./btc  <filename>")
	else
	{
		std::ifstream input_file(av[1]);
		if (input_file)
		{
			while (!input_file.eof())
			{
				std::string line;
				BitcoinExchange btc_exchange;
				getline(input_file, line);
				btc_exchange.set_line(line);
			}
		}
		else
		{
			ERROR("Error: no file available for i/o.");
		}
	}
}