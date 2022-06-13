//Elad Sapir - 209479948 - 4.b

#include "UnclosedRemarkException.h"

void UnclosedRemarkException::printError(ofstream& outFileT)
{//function print - gets the output file and writes the error msg -
	outFileT << "Error, encounter an unclosed remark." << endl << endl;//write error msg
}