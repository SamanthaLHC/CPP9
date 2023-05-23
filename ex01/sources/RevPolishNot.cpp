#include "rpn.hpp"

//==================================================================================================
//		constructors / destructors
//==================================================================================================
RevPolishNot::RevPolishNot() {} // non utilisé, mis en private

RevPolishNot::RevPolishNot(std::string const &arg)
{
	split_in_tokens(arg);
	calculate_and_print_result();
}

// TODO coplian form
RevPolishNot::RevPolishNot(RevPolishNot const &cpy)
{
	*this = cpy;
}

RevPolishNot::~RevPolishNot()
{
}

//==================================================================================================
//		operator overload
//==================================================================================================

RevPolishNot &RevPolishNot::operator=(RevPolishNot const &rhs)
{
	if (this != &rhs)
	{
	}
	return *this;
}

//==================================================================================================
//		members functions
//==================================================================================================

// utils
void RevPolishNot::print_sequence()
{
	for (size_t i = 0; i < _sequence.size(); i++)
	{
		std::cout << CYAN << "deque content: " << _sequence.top() << RES << std::endl;
	}
}

// parsing- error handlers
void RevPolishNot::split_in_tokens(std::string const &seq)
{
	size_t pos = 0;
	size_t i = 0;

	pos = seq.find(' ', i);
	std::string token = seq.substr(i, (pos - i));
	_sequence.push_back(seq.substr(i, (pos - i)));
	while (pos != std::string::npos)
	{
		i = pos + 1;
		pos = seq.find(' ', i);
		_sequence.push_back(seq.substr(i, (pos - i)));
		//TODO trim les espaces
	}
	// DEBUG
	// print_sequence();
}

bool RevPolishNot::isoperator(char c)
{
	if (c == '*' || c == '/' || c == '+' || c == '-')
		return true;
	else
		return false;
}

bool RevPolishNot::last_elem_is_operator()
{
	if (_sequence.back().size() == 1)
	{
		if (isoperator(_sequence.back()[0]))
			return true;
		else
			return false;
	}
	else
		return false;
}

bool RevPolishNot::sequence_is_valid()
{
	size_t i = 0;

	for (; i < _sequence.size(); i++)
	{
		if (_sequence[i].size() == 1)
		{
			char c = _sequence[i][0];
			if (!(isdigit(c) || isoperator(c)))
				return false;
		}
		else
			return false;
	}
	return true;
}

// main loop
void RevPolishNot::calculate_and_print_result()
{
	if (sequence_is_valid() && last_elem_is_operator())
	{
		INFO("sequence valid ok", "");
		// convertir les int pour calculer
		//  boucle de calcul => tant que deque chercher operand si operand prendre les nb presents avant etc.
		//   mettre le result au debut de la sequence pour recalucler avec l'operand suivant
	}
	else
		PRINT("Error.");
}

//TODO gérer les priorité de calcul (deux operands se succedent)
// exemple: 2 5 6 + * == 2 * (5 + 6)