#ifndef BITCOINEXCHANGE
#define BITCOINEXCHANGE

class BitcoinExchange
{
public:
	// TODO //coplian form_____________________________________________________________

	BitcoinExchange(std::ifstream &input_file);
	// BitcoinExchange(BitcoinExchange const &cpy);
	~BitcoinExchange();

	// BitcoinExchange &operator=(BitcoinExchange const &rhs);

	// function used in main____________________________________________________

private:
	//__________________________________members functions
	BitcoinExchange();

	// utils
	void reset_tokens();

	// parsing- error handlers
	bool line_format_is_valid();
	bool date_format_is_valid();
	void split_date_in_tokens();
	bool check_year();
	bool check_month();
	bool check_day(int month);
	bool is_bissextile();
	bool value_is_valid();

	// get datas, set attributs
	void save_csv_data();
	void split_and_get_val();

	// finder/calculator
	void find_date();
	void calculate();

	// read file
	void exchange_calculator(std::ifstream &input_file);

	//__________________________________attribute members

	std::string _line;
	std::string _date;
	std::string _year;
	std::string _month;
	std::string _day;
	bool		_day_ok;
	std::string _value;
	float 		_value_nb;
	bool 		_is_int;
	std::string _error_message;
	std::map<std::string, float> _data_csv;

};

#endif