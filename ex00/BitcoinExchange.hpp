#ifndef BITCOINEXCHANGE
#define BITCOINEXCHANGE

#include <iostream>
#include <string>
#include <vector>
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
	bool check_date_format(std::string const &date);
	bool bad_input(std::string const &line);
	bool not_pos(std::string const &value);
	bool too_large(std::string const &value);


	// getters/setters


	// read_line

	void process_and_save_data(std::ifstream &input_file);

	// finder/calculator

	//__________________________________attribute members

	std::string					_line;
	std::string					_date;
	float						_value;
	std::string					_error_message;
	std::vector<std::string>	_data_csv;
};

#endif