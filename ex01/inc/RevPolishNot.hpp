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
	bool isoperator(char c);
	// bool last_elem_is_operator();

	// calculs et print
	void do_calcul();
	void process_sequence(std::string const& sequence);

	//__________________________________attribute members

	char _operator;
	int _term_a;
	int _term_b;
	int _result;
	std::stack<int, std::vector<int> > _sequence;
};

#endif