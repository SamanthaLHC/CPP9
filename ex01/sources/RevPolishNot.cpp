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
		DEBUG("result of the operation is: ", _result);
		break;

	case '/': // TODO // void s'il faut faire une condition pour diviser le plus grand par le plus petit
		_result = _term_a / _term_b;
		DEBUG("result of the operation is: ", _result);
		break;

	case '-': // idem
		_result = _term_a - _term_b;
		DEBUG("result of the operation is: ", _result);
		break;

	case '+':
		_result = _term_a + _term_b;
		DEBUG("result of the operation is: ", _result);
		break;
	}
}

// main loop
void RevPolishNot::process_sequence(std::string const &seq)
{
	int i = 0;
	size_t pos = 0;

	while (pos != std::string::npos)
	{
		pos = seq.find(' ', i);
		std::string token = seq.substr(i, (pos - i));
		DEBUG("token is : ", token);

		if (token.size() == 1)
		{
			if (isoperator(token[0]))
			{
				_operator = token[0];
				INFO("operator is : ", _operator);
				if (_sequence.size() >= 2)
				{
					_term_b = _sequence.top();
					DEBUG("_term_a is: ", _term_b);
					_sequence.pop();
					_term_a = _sequence.top();
					_sequence.pop();
					DEBUG("_term_b is: ", _term_a);

					if(!_sequence.empty())
						INFO("term remaining in stack: ", _sequence.top());
					do_calcul();
					_sequence.push(_result);
				}
				else
					return;
			}

			if (isdigit(token[0]))
			{
				DEBUG("elem is digit: ", token[0]);

				std::istringstream str(token);
				int number;
				if (str >> number)
				{
					_sequence.push(number);
					INFO("elem in stack: ", _sequence.top());
				}
			}
		}
		else
		{
			PRINT("Error.");
			return;
		}
		i = pos + 1;
	}
	PRINT(_sequence.top());
}
