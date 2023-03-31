#include "BitcoinExchange.hpp"
#include "colors.h"

//==================================================================================================
//		constructors / destructors
//==================================================================================================

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(std::ifstream &input_file) : _error_message("")
{

	if (input_file)
	{
		process_and_save_data(input_file);
	}
	else
	{
		std::cout << RED << "Error: could not open file." << RES << std::endl;
		return;
	}
}

// BitcoinExchange::BitcoinExchange(BitcoinExchange const &cpy)
// {

// }

BitcoinExchange::~BitcoinExchange()
{
}

//==================================================================================================
//		operator overload
//==================================================================================================

// BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &rhs)
// {

// }

//==================================================================================================
//		members functions
//==================================================================================================

// getters/setters__________________________________________________________________________________

// parsing input file_______________________________________________________________________________

bool BitcoinExchange::check_date_format(std::string const &date)
{
}

// verif l'existence de la pair date-value
bool BitcoinExchange::bad_input(std::string const &line)
{
	// appel de la fonction check_date_format();

	// ici split_in_pair
}

bool BitcoinExchange::not_pos(std::string const& value) // cast en real type ?? float-int // recup avant avec std::pair??
{
}

bool BitcoinExchange::too_large(std::string const& value)
{

}

// return true si la ligne est complient false s'il y a un pb	
bool BitcoinExchange::parsing()
{
	if (bad_input())
	{
		this->_error_message = "Error: bad input =>" += BitcoinExchange::get_curr_line();
		// voir avec std::pair comment associer cette str avec le bad format (ex: 2001-42-42)
		return false;
	}
	else
	{
		split_in_pair(_line);
		if(check_date_format())
		{
			this->_error_message = 
		}
		
		if (not_pos())
		{
			std::cout << RED << "Error: not a positive number." << RES << std::endl;
			return false;
		}
		if (too_large())
		{
			{
				this->_error_message = "Error: too large a number.";
				return false;
			}
		}
		return true;
	}
}

// read file line by line in loop___________________________________________________________________

void BitcoinExchange::process_and_save_data(std::ifstream &input_file)
{
	while (std::getline(input_file, _line))
	{
		if (parsing(_line))
		{
			//find_date();
			//calculate();
			//print_line(); //???
		}
		
	}
}

// finder/calculator________________________________________________________________________________