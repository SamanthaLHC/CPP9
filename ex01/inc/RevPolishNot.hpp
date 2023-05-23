#ifndef REVPOLISHNOT
#define REVPOLISHNOT

class RevPolishNot
{
public:
	// coplian form_____________________________________________________________

	RevPolishNot(std::string const &arg);
	RevPolishNot(RevPolishNot const &cpy);
	~RevPolishNot();

	RevPolishNot &operator=(RevPolishNot const &rhs);

private:
	//__________________________________members functions
	// useless constructor
	RevPolishNot();

	// utils
	void print_sequence();

	// parsing- error handlers
	void split_in_tokens(std::string const &sequence);
	bool isoperator(char c);
	bool last_elem_is_operator();
	bool sequence_is_valid();

	// calculs et print
	void calculate_and_print_result();

	//__________________________________attribute members
	std::deque<std::string> _sequence;
};

#endif