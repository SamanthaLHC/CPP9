#include "btc.hpp"

//==================================================================================================
//		constructors / destructors
//==================================================================================================
BitcoinExchange::BitcoinExchange() {} // non utilisé, mis en private

BitcoinExchange::BitcoinExchange(std::ifstream & input_file) : _line(""), _date(""), _value(""), _error_message("")
{
	DEBUG("constructor called: ", &input_file);
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

// parsing input file_______________________________________________________________________________

void BitcoinExchange::set_line(std::string const &line)
{
	DEBUG("line is: ", line);
	this->_line = line;
}

std::string const & BitcoinExchange::get_line()
{
	return this->_line;
}
// parsing input file_______________________________________________________________________________

bool BitcoinExchange::line_format_is_valid()
{
	DEBUG("Here, line_format_is valid :", _line);
	return true;
}

bool BitcoinExchange::date_format_is_valid()
{
	DEBUG("Here, line_format_is valid :", _date);
	return true;
}

bool BitcoinExchange::value_is_valid()
{
	DEBUG("Here, line_format_is valid :", _value);
	return true;
}

void BitcoinExchange::split_and_get_val()
{
	DEBUG("Here, split and get values", "");
}

// get datas and values_______________________________________________________________________________

void BitcoinExchange::save_csv_data()
{
	DEBUG("Here, save csv datas", "");
}

// output result_______________________________________________________________________________

void BitcoinExchange::find_date()
{
	DEBUG("Here, find date in map csv data", "");
}

void BitcoinExchange::calculate()
{
	DEBUG("Here, calculate and print", "");
}

// read file line by line in loop___________________________________________________________________

void BitcoinExchange::exchange_calculator(std::ifstream& input_file)
{
	save_csv_data(); // save in map
	while (!input_file.eof())
	{
		while (std::getline())
		{
			DEBUG("line is: ", _line);
			if (line_format_is_valid())
			{
				split_and_get_val();
			}
			else
				PRINT(_error_message);
			if (date_format_is_valid() && value_is_valid())
			{
				find_date();
				calculate();
			}
			else
				PRINT(_error_message);
		}
	}
}
