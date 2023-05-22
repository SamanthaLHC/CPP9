#include "btc.hpp"

//==================================================================================================
//		constructors / destructors
//==================================================================================================
BitcoinExchange::BitcoinExchange() {} // non utilisé, mis en private

BitcoinExchange::BitcoinExchange(std::ifstream &input_file) : _line(""),
															  _date(""),
															  _year(""),
															  _month(""),
															  _day(""),
															  _day_ok(false),
															  _value(""),
															  _value_nb(0),
															  _result(0),
															  _is_int(false),
															  _error_message("")
{
	save_csv_data();
	// print_map();
	exchange_calculator(input_file);
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &cpy) : _line(cpy._line),
															   _date(cpy._date),
															   _year(cpy._year),
															   _month(cpy._month),
															   _day(cpy._day),
															   _day_ok(cpy._day_ok),
															   _value(cpy._value),
															   _value_nb(cpy._value_nb),
															   _result(cpy._result),
															   _is_int(cpy._is_int),
															   _error_message(cpy._error_message)
{
	*this = cpy;
}

BitcoinExchange::~BitcoinExchange()
{
}

//==================================================================================================
//		operator overload
//==================================================================================================

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &rhs)
{
	if (this != &rhs)
	{
		_line = rhs._line;
		_date = rhs._date;
		_year = rhs._year;
		_month = rhs._month;
		_day = rhs._day;
		_day_ok = rhs._day_ok;
		_value = rhs._value;
		_value_nb = rhs._value_nb;
		_result = rhs._result;
		_is_int = rhs._is_int;
		_error_message = rhs._error_message;
	}
	return *this;
}

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

void BitcoinExchange::print_map()
{
	std::map<std::string, float>::iterator it = _data_csv.begin();
	for (; it != this->_data_csv.end(); it++)
	{
		std::cout << CYAN << "map content: " << it->first << " " << it->second << RES << std::endl;
	}
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
	// INFO("YEAR: ", _year);
	// INFO("MONTH: ", _month);
	// INFO("DAY: ", _day);
}

bool BitcoinExchange::check_year()
{
	int int_type = 0;
	if (_year.size() == 4)
	{
		std::istringstream str_to_conv(_year);
		str_to_conv >> int_type;
		if (int_type >= 2000 && int_type < 2030)
			return true;
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
				_day_ok = true;
			else
				return false;
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
				return true;
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
}

bool BitcoinExchange::date_format_is_valid()
{
	split_date_in_tokens();

	int ok = 0;

	if (check_year())
		ok += 1;
	if (check_month())
		ok += 1;
	if (_day_ok)
		ok += 1;
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
		_value_nb = float_type;
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
	// INFO("date is: ", _date);

	i = pos + 2; // saute le space
	_value = _line.substr((i), ((_line.size())) - i);
	// INFO("value is: ", _value);
}

// get datas and values_______________________________________________________________________________

void BitcoinExchange::split_in_pair(std::string const &entry_line)
{
	size_t pos;
	size_t i = 0;
	std::string key;
	std::string val;

	pos = entry_line.find(',', i);
	key = entry_line.substr(i, (pos - i));
	// INFO("key date is: ", key);

	i = pos + 1;
	val = entry_line.substr((i), ((entry_line.size())) - i);
	// INFO("value is: ", val);

	std::istringstream val_to_conv(val);
	float float_type;
	val_to_conv >> float_type;
	// INFO("value after conversion is: ", float_type);

	this->_data_csv[key] = float_type; // ds map: si a la pos [] il n'y a rien, la pair key val est inseree
}

void BitcoinExchange::save_csv_data()
{
	// get line avec ifstream
	std::string entry_line;
	std::ifstream csv_file("./data.csv", std::ifstream::in);

	if (csv_file.good())
	{
		while (!csv_file.eof())
		{
			std::getline(csv_file, entry_line);
			split_in_pair(entry_line); // ici save ds map
		}
	}
	else
	{
		ERROR("Error: cannot open and read csv file.");
		return;
	}
}

// output result_______________________________________________________________________________

void BitcoinExchange::find_date()
{
	std::map<std::string, float>::iterator it;
	it = _data_csv.find(_date);
	if (it == _data_csv.end())
	{
		it = _data_csv.lower_bound(_date);
		it--;

		// DEBUG_______________________________________________________________
		//  if (it != _data_csv.end())
		//  	std::cout << CYAN << "lower key is: " << it->first << RES << std::endl;
		//  else
		//  DEBUG("key not found", "");
		// FIN DU DEBUG_______________________________________________________
	}
	if (it != _data_csv.end())
	{
		_result = _value_nb * it->second;
		std::cout << WHITE << _date << " => " << _value << " = " << _result << RES << std::endl;
	}
}

// read file line by line in loop___________________________________________________________________
void BitcoinExchange::exchange_calculator(std::ifstream &input_file)
{
	while (!input_file.eof())
	{
		reset_tokens();
		std::getline(input_file, _line);
		// INFO(_line, "");

		if (line_format_is_valid())
			split_and_get_val();
		else
		{
			PRINT(_error_message);
			continue;
		}
		if (date_format_is_valid() && value_is_valid())
			find_date();
		else
		{
			PRINT(_error_message);
		}
	}
}
