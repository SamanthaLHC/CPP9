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

		const char *BitcoinExchange::BadValue::what() const throw()
		{
			return "Error: bad value. Value must be a positiv float or a positiv integer between 0 and 1000.";
		}

		const char *BitcoinExchange::WrongFile::what() const throw()
		{
			return "Error: bad date format.";
		}
		
		const char *BitcoinExchange::BadPairFormatFile::what() const throw()
		{
			return "Error: bad file format. Each line must be a pair : date | value";
		}

//==================================================================================================
//		members functions
//==================================================================================================

		//void ? int? bool ??
		bool BitcoinExchange::check_file(std::ifstream& input_file)
		{
			if (!check_healthy_file(input_file))
				throw WrongFile();
			if (!check_file_format(input_file))
				throw BadPairFormatFile();
			if (!check_date(input_file))
				throw BadDateFormat();
			if (!check_value(input_file))
				throw BadValue();
			else
				return true;
		}
