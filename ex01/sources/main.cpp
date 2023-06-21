#include "rpn.hpp"

bool isoperator(char c)
{
	if (c == '*' || c == '/' || c == '+' || c == '-')
		return true;
	else
		return false;
}

int main(int ac, char **av)
{
	if (ac != 2)
	{
		ERROR("USAGE: ./RPN  <inverted Polish mathematical expression with numbers < 10 >");
		return 1;
	}
	else
	{
		std::string seq(av[1]);
		if ((seq.find("*") == std::string::npos) && (seq.find("+") == std::string::npos) && (seq.find("-") == std::string::npos) && (seq.find("/") == std::string::npos))
		{
			PRINT("Error. No operator in this sequence.");
			return 1;
		}
		size_t last_pos = seq.size() - 1;
		if (!isoperator(seq[last_pos]))
		{
			PRINT("Error. Not a RPN sequence (no operator at the end).");
			return 1;
		}

		RevPolishNot rpn(av[1]);
	}
	return 0;
}