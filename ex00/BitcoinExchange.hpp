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
		
//__________________________________exceptions class

		class BadDateFormat: public std::exception
		{
			const char *what() const throw();
		};

		class NotPositiv: public std::exception
		{
			const char *what() const throw();
		};

		class TooLargeNumber: public std::exception
		{
			const char *what() const throw();
		};

		class BadPairFormatFile: public std::exception
		{
			const char *what() const throw();
		};

		class WrongFile: public std::exception
		{
			const char *what() const throw();
		};

//__________________________________members functions

		//parsing input file

		bool check_file(std::ifstream& input_file);
		bool check_healthy_file(std::ifstream& input_file);
		bool check_file_format(std::ifstream& input_file);
		bool check_date(std::ifstream& input_file);
		bool check_pos_value(std::ifstream& input_file);
		bool check_limit_value(std::ifstream& input_file);

		//getters/setters
		
		// void set_data_infile();
		// void get_data_infile();


		//finder/calculator



//__________________________________attribute members

		// std::vector<std::string> _data_from_infile;

};


#endif