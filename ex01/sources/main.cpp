#include "rpn.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		ERROR("USAGE: ./btc  <filename>");
		return 1;
	}
	else
	{
		RevPolishNot rpn();

	}
	return 0;
}