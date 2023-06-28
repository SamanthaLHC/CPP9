#include "rpn.hpp"

//==================================================================================================
//		constructors / destructors
//==================================================================================================
RevPolishNot::RevPolishNot() {} // non utilisé, mis en private

RevPolishNot::RevPolishNot(std::string const &arg) : _operator(' '),
													 _term_a(0),
													 _term_b(0),
													 _result(0)
{
	process_sequence(arg);
}

RevPolishNot::RevPolishNot(RevPolishNot const &cpy) : _operator(cpy._operator),
													  _term_a(cpy._term_a),
													  _term_b(cpy._term_b),
													  _result(cpy._result)
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
		_operator = rhs._operator;
		_term_a = rhs._term_a;
		_term_b = rhs._term_b;
		_result = rhs._result;
	}
	return *this;
}

//==================================================================================================
//		members functions
//==================================================================================================

bool RevPolishNot::isoperator(char c)
{
	if (c == '*' || c == '/' || c == '+' || c == '-')
		return true;
	else
		return false;
}

void RevPolishNot::do_calcul()
{
	switch (_operator)
	{
	case '*':
		_result = _term_a * _term_b;
		break;

	case '/':
		_result = _term_a / _term_b;
		break;

	case '-': // idem
		_result = _term_a - _term_b;
		break;

	case '+':
		_result = _term_a + _term_b;
		break;
	}
}

// main loop
void RevPolishNot::process_sequence(std::string const &seq)
{
	size_t i = 0;
	size_t pos = 0;

	while (pos != std::string::npos)
	{
		pos = seq.find(' ', i);
		std::string token = seq.substr(i, (pos - i));

		if (token.empty() == true)
		{
			i++;
			continue;
		}

		if (token.size() == 1)
		{
			if (isoperator(token[0]))
			{
				_operator = token[0];
				if (_sequence.size() >= 2)
				{
					_term_b = _sequence.top();
					_sequence.pop();
					_term_a = _sequence.top();
					_sequence.pop();
					if (_operator == '/' && _term_b == 0)
					{
						ERROR("Error. Divide by zero impossible.");
						return;
					}
					do_calcul();
					_sequence.push(_result);
				}
				else
				{
					ERROR("Error. First elem is an operator.");
					return;
				}
			}

			else if (isdigit(token[0]))
			{
				std::istringstream str(token);
				int number = 0;
				if (str >> number)
					_sequence.push(number);
			}
		}
		else
		{
			// not a digit nor operator
			ERROR("Error. Not an integer < 10 nor an operator.");
			return;
		}
		i = pos + 1;
	}
	if (_sequence.size() == 1)
		PRINT(_sequence.top());
	else
	{
		ERROR("Error. Operator missing cannot fully calculate the sequence");
		INFO("Elements in stack are: ", "");
		for (size_t i = 0; i <= _sequence.size(); i++)
		{
			INFO("", _sequence.top());
			_sequence.pop();
		}
	}
}
