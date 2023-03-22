#ifndef BITCOINEXCHANGE
#define BITCOINEXCHANGE

#include <iostream>
#include <string>

class BitcoinExchange
{
	public:

		BitcoinExchange();
		BitcoinExchange(ici mettre des parametres);
		BitcoinExchange(BitcoinExchange const &cpy);
		~BitcoinExchange();

		BitcoinExchange &opérator=(BitcoinExchange const &rhs);

	private:

};


#endif