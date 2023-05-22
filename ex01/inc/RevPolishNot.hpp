#ifndef REVPOLISHNOT
#define REVPOLISHNOT

class RevPolishNot
{
public:
	// coplian form_____________________________________________________________

	RevPolishNot();
	RevPolishNot(std::string const &arg);
	RevPolishNot(RevPolishNot const &cpy);
	~RevPolishNot();

	RevPolishNot &operator=(RevPolishNot const &rhs);

private:
	//__________________________________members functions

	// utils
	void print_sequence();

	// parsing- error handlers
	void split_in_tokens(std::string const &sequence); // and save in deque //TODO
	// split sur espace
	//  push back ds deque

	bool sequence_is_valid();
	// iterer sur deque pour voir si
	bool check_number();  // verifie aussi s'il n'y a pas de chat intrus //TODO
	// 1) tous les num sont < 10
	// 4) pas de symboles autres (parenthese, quote , virgule point etc)
	bool check_operand(); // dedans et à la fin //TODO
	// 2) s'il y a un operand ds l'expression
	// 3) si la sequence se termine sur un operand


	// calculs et print
	void calculate_and_print_result(); // main loop ici //TODO //ONGOING

	//__________________________________attribute members

	std::deque<int> _sequence;
};

#endif