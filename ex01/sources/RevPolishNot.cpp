#include "rpn.hpp"

//==================================================================================================
//		constructors / destructors
//==================================================================================================
RevPolishNot::RevPolishNot() {} // non utilisé, mis en private

RevPolishNot::RevPolishNot(std::string const& arg) :
{
	
	
	//si ok calculer et output 
}

//TODO coplian form 
RevPolishNot::RevPolishNot(RevPolishNot const &cpy) :
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

// parsing- error handlers

// setters/getters
