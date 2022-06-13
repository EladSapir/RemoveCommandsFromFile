//Elad Sapir - 209479948 - 4.b

#include "CloseRemarkWithoutOpenRemarkException.h"

void ClosedRemarkWithoutOpenRemarkException::printError(ofstream& outFileT)
{//function print - gets the output file and writes the error msg -
	outFileT << endl << "Error, encounter a close remark character without a preceding open remark character."<<endl;//error msg to output file
}