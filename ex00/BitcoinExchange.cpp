#include "BitcoinExchange.hpp"
#include "colors.h"

//==================================================================================================
//		constructors / destructors
//==================================================================================================
		
		BitcoinExchange::BitcoinExchange(){}

		BitcoinExchange::BitcoinExchange(std::ifstream& input_file)
		{
			try
			{
				check_file(input_file);
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << '\n';
			}
			// set_data_from_infile();
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
//		exceptions handler
//==================================================================================================

		const char *BitcoinExchange::BadDateFormat::what() const throw()
		{
			return "Error: bad date format. Date format must be: Year-Month-Day.";
		}

		const char *BitcoinExchange::NotPositiv::what() const throw()
		{
			return "Error: not a positive number.";
		}

		const char *BitcoinExchange::TooLargeNumber::what() const throw()
		{
			return "Error: too large number.";
		}

		const char *BitcoinExchange::WrongFile::what() const throw()
		{
			return "Error: could not open file.";
		}
		
		const char *BitcoinExchange::BadPairFormatFile::what() const throw()
		{
			return "Error: bad input. =>";
		}

//==================================================================================================
//		members functions
//==================================================================================================


		bool BitcoinExchange::check_healthy_file(std::ifstream& input_file)
		{
			if(input_file.goodbit == true)
				return true;
		}

		bool BitcoinExchange::check_file_format(std::ifstream& input_file)
		{
			// récupérer une ligne et vérifier une chaine avec 4digits un tiret
			// 2 digits tiret 2digits un '|' un int 
		}

		bool BitcoinExchange::check_date(std::ifstream& input_file)
		{

		}

		bool BitcoinExchange::check_pos_value(std::ifstream& input_file)
		{

		}

		bool BitcoinExchange::check_limit_value(std::ifstream& input_file)
		{

		}

		bool BitcoinExchange::check_file(std::ifstream& input_file)
		{
			if (!check_healthy_file(input_file))
				throw WrongFile();
			if (!check_file_format(input_file))
				throw BadPairFormatFile();
			if (!check_date(input_file))
				throw BadDateFormat();
			if (!check_pos_value(input_file))
				throw NotPositiv();
			if (!check_limit_value(input_file))
				throw TooLargeNumber();
			else
				return true;
		}
