//Elad Sapir - 209479948 - 4.b

#pragma once
#ifndef CLOSEREMARKWITHOUTOPRNREMARKEXCEPTION_H
#define CLOSEREMARKWITHOUTOPRNREMARKEXCEPTION_H
#include "RemarkException.h"

//class of closed remark without opening - inheritence with Remark exception class
class ClosedRemarkWithoutOpenRemarkException:public RemarkException
{
public:
	ClosedRemarkWithoutOpenRemarkException() {};//constructor - does nothing - no data members
	ClosedRemarkWithoutOpenRemarkException(const ClosedRemarkWithoutOpenRemarkException& remarkT) {};//copy constructor
	~ClosedRemarkWithoutOpenRemarkException() {};//distructor - empty
	virtual void printError(ofstream& outFileT);//virtual function to write the error msg
};

#endif // !CLOSEREMARKWITHOUTOPRNREMARKEXCEPTION
