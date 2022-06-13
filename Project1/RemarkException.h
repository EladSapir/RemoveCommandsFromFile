//Elad Sapir - 209479948 - 4.b

#pragma once
#ifndef REMARKEXCEPTION_H
#define REMARKEXCEPTION_H
#include <iostream>
using namespace std;
#include <fstream>
using namespace std;

class RemarkException//there is no cpp file - there are no implementations for the functions
{//this class has no cpp file - none of the methods needs implementation
protected:
public:
	RemarkException(){};//ctor
	RemarkException(const RemarkException& remarkT){};//copy constructor
	virtual void printError(ofstream& outFileT)=0;//virtual print error
	~RemarkException() {};//distructor
};



#endif // !REMARKEXCEPTION_H
