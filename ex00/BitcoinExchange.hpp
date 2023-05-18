#ifndef BITCOINEXCHANGE
#define BITCOINEXCHANGE

#include <iostream>
#include <string>
#include <map>
#include <fstream>

class BitcoinExchange
{
public:
	// TODO //coplian form_____________________________________________________________

	BitcoinExchange();
	// BitcoinExchange(BitcoinExchange const &cpy);
	~BitcoinExchange();

	// BitcoinExchange &operator=(BitcoinExchange const &rhs);

	// function used in main____________________________________________________
	//  getters/setters

	void set_line(std::string const &line);
	std::string const &get_line();

private:
	//__________________________________members functions

	// parsing- error handlers

	bool line_format_is_valid();
	bool date_format_is_valid();
	bool value_is_valid(); // TODO // set en str et conv avec isstringstream //voir cpp6

	// get datas, set attributs

	void save_csv_data();
	void split_and_get_val();

	// finder/calculator
	void find_date();
	void calculate();

	// read file
	void exchange_calculator(std::ifstream *file);

	//__________________________________attribute members

	std::string _line;
	std::string _date;
	std::string _value;
	std::string _error_message;
	std::map<std::string, float> _data_csv;
};

#endif