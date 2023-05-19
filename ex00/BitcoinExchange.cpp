#include "btc.hpp"

//==================================================================================================
//		constructors / destructors
//==================================================================================================
BitcoinExchange::BitcoinExchange() {} // non utilisé, mis en private

BitcoinExchange::BitcoinExchange(std::ifstream &input_file) : _line(""), _date(""), _value(""), _error_message("")
{
	DEBUG("constructor called: ", &input_file);
	exchange_calculator(input_file);
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

bool BitcoinExchange::line_format_is_valid()
{
	INFO("Here, line_format_is valid :", _line);

	for (size_t i = 0; i < _line.size(); i++)
	{
		if (_line.find("|") == std::string::npos)
		{
			this->_error_message = "Error: bad input => ";
			this->_error_message += _line;
			return false;
		}
	}
	// TODO check la presence de space avant et apres pipe
	return true;
}

bool BitcoinExchange::date_format_is_valid()
{
	INFO("Here, date_format_is valid :", _date);
	return true;
}

bool BitcoinExchange::value_is_valid()
{
	INFO("Here, value_is valid :", _value);
	
	return true;
}

void BitcoinExchange::split_and_get_val()
{
	INFO("Here, split and get values", "");
	size_t pos;
	size_t i = 0;

	pos = _line.find('|', i);
	_date = _line.substr(i, (pos - i - 1));
	DEBUG("date is: ", _date);
	i = pos + 2; // saute le space
	_value = _line.substr((i), ((_line.size())) - i);
	DEBUG("value is: ", _value);
}

// get datas and values_______________________________________________________________________________

void BitcoinExchange::save_csv_data()
{
	INFO("Here, save csv datas", "");
}

// output result_______________________________________________________________________________

void BitcoinExchange::find_date()
{
	INFO("Here, find date in map csv data", "");
}

void BitcoinExchange::calculate()
{
	INFO("Here, calculate and print", "");
}

// read file line by line in loop___________________________________________________________________
void BitcoinExchange::exchange_calculator(std::ifstream &input_file)
{
	save_csv_data(); // save in map
	while (!input_file.eof())
	{
		std::getline(input_file, _line);

		DEBUG("line is: ", _line);
		if (line_format_is_valid())
			split_and_get_val();
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
