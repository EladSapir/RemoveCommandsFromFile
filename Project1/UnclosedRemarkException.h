//Elad Sapir - 209479948 - 4.b

#pragma once
#ifndef UNCLOSEDREMARKEXCEPTION_H
#define UNCLOSEDREMARKEXCEPTION_H
#include "RemarkException.h"
//class of unclosed remark exception - inheritance with Remark exception class
class UnclosedRemarkException : public RemarkException
{
public:
	UnclosedRemarkException() {};//constructor - does nothing - no data members
	UnclosedRemarkException(const UnclosedRemarkException& remarkT) {};//copy constructor
	virtual void printError(ofstream& outFileT);//print to output function
	~UnclosedRemarkException() {};//distructor
};

#endif // UNCLOSEDREMARKEXCEPTION_H
