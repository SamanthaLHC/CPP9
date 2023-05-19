#include "btc.hpp"

//==================================================================================================
//		constructors / destructors
//==================================================================================================
BitcoinExchange::BitcoinExchange() {} // non utilisé, mis en private

BitcoinExchange::BitcoinExchange(std::ifstream &input_file) : _line(""), _date(""), _value(""), _value_nb(0), _is_int(false), _error_message("")
{
	save_csv_data(); // TODO save in map
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

// utils

void BitcoinExchange::reset_tokens()
{
	_line = "";
	_value = "";
	_date = "";
	_year = "";
	_month = "";
	_day = "";
	_value_nb = 0;
	_is_int = false;
	_error_message = "";
}

// parsing input file_______________________________________________________________________________

bool BitcoinExchange::line_format_is_valid()
{
	if (_line.find("|") == std::string::npos)
	{
		this->_error_message = "Error: bad input => " + _line;
		return false;
	}

	size_t pos;
	pos = _line.find("|");
	if (_line[pos - 1] != ' ' || _line[pos + 1] != ' ')
	{
		this->_error_message = "Error: bad input => " + _line;
		return false;
	}
	return true;
}

void BitcoinExchange::split_date_in_tokens()
{
	size_t pos = 0;
	size_t i = 0;

	std::string tmp_date = _date;

	int count_step = 0;

	while (pos != std::string::npos)
	{
		pos = tmp_date.find('-', i);
		if (count_step == 0)
			_year = tmp_date.substr(i, (pos - i));
		else if (count_step == 1)
			_month = tmp_date.substr(i, (pos - i));
		else if (count_step == 2)
			_day = tmp_date.substr(i, (pos - i));
		tmp_date.erase(tmp_date.begin(), tmp_date.begin() + (pos + 1));
		count_step += 1;
	}

	// DEBUG("YEAR: ", _year);
	// DEBUG("MONTH: ", _month);
	// DEBUG("DAY: ", _day);
}

bool BitcoinExchange::check_year()
{
	int int_type = 0;
	if (_year.size() == 4)
	{
		std::istringstream str_to_conv(_year);
		str_to_conv >> int_type;
		if (int_type >= 2000 && int_type < 2030) // TODO verifier si ça correspond au comportement attendu par le prog
		{
			return true;
		}
		else
		{
			this->_error_message = "Error: bad input => " + _date;
			return false;
		}
	}
	else
	{
		this->_error_message = "Error: bad input => " + _date;
		return false;
	}
}

bool BitcoinExchange::check_month()
{
	int int_type = 0;
	if (_month.size() == 2)
	{
		std::istringstream str_to_conv(_month);
		str_to_conv >> int_type;
		if (int_type >= 1 && int_type < 13)
		{
			if (check_day(int_type))
			{
				
				_day_ok = true;

			}
			return true;
		}
		else
		{
			this->_error_message = "Error: bad input => " + _date;
			return false;
		}
	}
	else
	{
		this->_error_message = "Error: bad input => " + _date;
		return false;
	}
}

bool BitcoinExchange::is_bissextile()
{
	int int_type = 0;
	std::istringstream str_to_conv(_year);
	str_to_conv >> int_type;

	if ((int_type % 4 == 0) || (int_type % 100 == 0) || (int_type % 400 == 0))
		return true;
	else
		return false;
}

// FIXME  NOT WORKING dans le check affiné des dates
bool BitcoinExchange::check_day(int month)
{
	int int_day = 0;
	if (_day.size() == 2)
	{
		std::istringstream str_to_conv(_day);
		str_to_conv >> int_day;

		if (month == 4 || month == 6 || month == 9 || month == 11)
		{
			if (int_day >= 1 && int_day <= 30)
			{
				return true;
			}
			else
			{
				this->_error_message = "Error: bad input, day must be between 1 and 30 => " + _date;
				return false;
			}
		}
		else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
		{
			if (int_day >= 1 && int_day <= 31)
				return true;
			else
			{
				this->_error_message = "Error: bad input, day must be between 1 and 31 => " + _date;
				return false;
			}
		}
		else
		{
			if (is_bissextile())
			{
				if (int_day >= 1 && int_day <= 29)
					return true;
				else
				{
					this->_error_message = "Error: bad input, day must be between 1 and 29 => " + _date;
					return false;
				}
			}
			else
			{
				if (int_day >= 1 && int_day <= 28)
					return true;
				else
				{
					this->_error_message = "Error: bad input, day must be between 1 and 28 => " + _date;
					return false;
				}
			}
		}
	}
	else
	{
		this->_error_message = "Error: bad input => " + _date;
		return false;
	}
	// return true;
}

bool BitcoinExchange::date_format_is_valid()
{
	split_date_in_tokens();

	int ok = 0; // si ok == 3 return true sinon return false

	if (check_year())
	{
		ok += 1;
	}
	if (check_month())
	{

		ok += 1;
	}
	if (_day_ok)
	{
		ok += 1;
	}
	if (ok == 3)
		return true;
	else
		return false;
}

bool BitcoinExchange::value_is_valid()
{
	if (_value.find('.') == std::string::npos)
		_is_int = true;

	float float_type = 0;
	std::istringstream str_to_conv(_value);

	if (str_to_conv >> float_type)
	{
		_value_nb = float_type;
	}
	else
	{

		this->_error_message = "Error: bad input => " + _line;
		return false;
	}

	if (_is_int)
	{

		if (_value_nb < 0)
		{
			_error_message = "Error: not a positive number.";
			return false;
		}
		else if (_value_nb > 1000)
		{
			_error_message = "Error: too large a number.";
			return false;
		}
	}
	return true;
}

void BitcoinExchange::split_and_get_val()
{
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
	while (!input_file.eof())
	{
		reset_tokens();
		std::getline(input_file, _line);
		ERROR(_line);

		if (line_format_is_valid())
			split_and_get_val();
		else
		{
			PRINT(_error_message);
			continue;
		}
		if (date_format_is_valid() && value_is_valid())
		{
			find_date(); // TODO
			calculate(); // TODO attention bien utiliser la var _value_nb pour les calculs !!
		}
		else
		{
			PRINT(_error_message);
		}
	}
}

// TODO vérifier que les lignes vides ont disparu apres avoir codé calculate and print
// hint: cela vient  de reset token?
