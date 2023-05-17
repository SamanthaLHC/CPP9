#ifndef BTC_HPP
# define BTC_HPP

#include <string>
#include <iostream>
#include "BitcoinExchange.hpp"

//colors____________________________________________________________________________________________

#define BLACK "\e[1;30m"
#define RED "\e[1;31m"
#define GREEN "\e[1;32m"
#define YELLOW "\e[1;33m"
#define BLUE "\e[1;34m"
#define MAGENTA "\e[1;35m"
#define CYAN "\e[1;36m"
#define WHITE "\e[1;37m"
#define RES "\e[0m"

//affichage_________________________________________________________________________________________

#define ERROR(str) std::cerr << RED << str << RES << std::endl;
#define DEBUG(str, var) std::cerr << GREEN << str << var << RES << std::endl;
#define PRINT(str, var) std::cerr << WHITE << str << var << RES << std::endl;

#endif