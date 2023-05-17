#ifndef BITCOINEXCHANGE
#define BITCOINEXCHANGE

#include <iostream>
#include <string>
#include <map>
#include <fstream>

class BitcoinExchange
{
public:
	BitcoinExchange(std::ifstream &input_file);
	// BitcoinExchange(BitcoinExchange const &cpy);
	~BitcoinExchange();

	// BitcoinExchange &operator=(BitcoinExchange const &rhs);

private:
	//__________________________________useless constructor

	BitcoinExchange();

	//__________________________________members functions

	//parsing- error handlers

	bool parsing(std::string const& line);
	bool date_format_is_valid(std::string const &date);
	bool line_format_is_valid(std::string const &date);
	bool value_is_valid(std::string const &date);

	// getters/setters


	// read_line


	// finder/calculator

	//__________________________________attribute members

	std::string							_line;
	std::string							_date;
	float								_value;
	std::string							_error_message;
	std::map<std::string, std::string>	_data_csv;
};

#endif