//Elad Sapir - 209479948 - 4.b

#include <iostream>
using namespace std;
#include <fstream>
using namespace std;
#include "CloseRemarkWithoutOpenRemarkException.h"
#include "UnclosedRemarkException.h"
#include <string>

void getRemarkEx(ofstream& outF, RemarkException* ex);//function that handles the exceptions
void checkLineRemark(ofstream& outF, int& remark, string line, int& lastLocRemark, int& maxPwrite);//function to check line
void fileNoteCheck();//function that goes on the file and removes the notes

int main()
{
	fileNoteCheck();//call the function that checks the file and fixes it
	cout << "Function ended." << endl;
	return 0;
}


void getRemarkEx(ofstream& outF, RemarkException* ex)//function that handles the exception - calls the print function
{
	try {
		throw ex;//throw the exception
	}
	catch (RemarkException* error)
	{
		error->printError(outF);//each class of exception has its own print function - call it
		delete ex;//delete the memory of the located exception
	}
}

void checkLineRemark(ofstream& outF, int& remark, string line, int& lastLocRemark, int& maxPwrite)
{//function that checks each line seperately 
	int doubleSlash = 0;// if got to "//" flag
	int errFlag = 0; //error flag
	int notemptyFlag = 0; // if the line is not empty flag
	if (line == "")
	{
		outF << endl;//if the line is empty - need to add enter 
	}
	else
	{
		for (int i = 0; i < (line.size() - 1); i++)//run on the line 
		{
			if (remark == 1)//if remark is 1 (already in note and dont need to copy)
			{
				if (line[i] == '*' && line[i + 1] == '/')//if got to close
				{
					remark = 0;//end of the note
					lastLocRemark = outF.tellp();//go to the end of output file
					i++;
					continue;
				}
				if (line[i] == '/' && line[i + 1] == '*')//if already in note and one more opens - error
				{
					errFlag = 1;//error flag 1
					i++;//points to '/' and want to jump on the '*'
					try
					{
						RemarkException* throwException = new UnclosedRemarkException;//exception of unclosed remark
						if (!throwException)//if fail to allocate memory for the exception
						{
							outF.close();//close the output file
							throw "Allocation error";//will get caught in the main
						}
						getRemarkEx(outF, throwException);//call the function that handles the exception
						continue;
					}
					catch (const char* ex)//if got here - allocation error threw
					{
						if (!strcmp(ex, "Allocation error"))//if its allocation error
						{
							outF.close();//close the output file
							cout << "Allocation failed, program stopped";//cant continue with the program - exit
							exit(1);//quit 
						}
					}
					continue;//continue to next char
				}
				continue;//continue to next char
			}
			else
			{
				if (line[i] == '/' && line[i + 1] == '/')//if got to "//"
				{
					doubleSlash = 1;//this flag is for "//" note
					notemptyFlag = 1;//even if the line contains only //note - its still a line - will know to add enter
					lastLocRemark = outF.tellp();
					break;//break because the rest of the line is note
				}
				if (line[i] == '/' && line[i + 1] == '*')//if got to /* and wasnt in a note
				{
					remark = 1;//flag to know that now its a note
					i++;// dont need the *
					continue;//continue to next char
				}
				if (line[i] == '*' && line[i + 1] == '/')//if got to */ and wasnt in a command - error
				{
					errFlag = 1;//error flag 
					outF.seekp(lastLocRemark);//go to the next place that note closed in the right way
					outF << endl;//add enter 
					try
					{
						RemarkException* ex = new ClosedRemarkWithoutOpenRemarkException;//allocate new exception - closed without opening
						if (!ex)//if allocation fail
						{
							outF.close();//close output file
							throw "Allocation error";//will get caught in the main
						}
						getRemarkEx(outF, ex);//call function that handles the exception
						continue;//continue to next char
					}
					catch (const char* ex)
					{
						if (!strcmp(ex, "Allocation error"))//tell the user the allocation failed and quit
						{
							cout << "Allocation failed, program stopped";
							exit(1);
						}
					}
					continue;//continue to next char
				}
				notemptyFlag = 1;//not in a note - can add the char to output file
				outF << line[i];//add char to output file
			}
		}
		if (remark == 0 && errFlag == 0 && doubleSlash == 0)//if its not in a note, its not an error , and not in double slash note
		{
			outF << line[line.size() - 1];
			notemptyFlag = 1;
		}
		if (notemptyFlag == 1)
		{
			outF << endl;//the loop dont get to the end of the line , if it was not empty - add down line
		}
	}
	if (maxPwrite < outF.tellp())
	{
		maxPwrite = outF.tellp();
	}
}

void fileNoteCheck()
{
	int remark = 0;
	int LastLocRemark = 0;
	int maxPlaceW = 0;
	try
	{
		string line;
		ofstream outFile("output.txt", ios::out);//open output file to write
		if (!outFile.is_open()) // opening check
		{
			throw "output.txt is not valid. Can not write to output file.";//opening check
		}
		ifstream inFile("input.txt", ios::in);//open input file to read
		if (!inFile.is_open())//opening check
		{
			outFile.close();//close output file
			throw "input.txt is not valid";
		}
		while (getline(inFile, line))//go on the input file - on each line 
		{
			checkLineRemark(outFile, remark, line, LastLocRemark, maxPlaceW);//call the function that checks each line
		}
		int lastPinFile = outFile.tellp();//last place in file output
		while (maxPlaceW > lastPinFile)
		{
			outFile << " ";
			lastPinFile++;
		}
		inFile.close();//close input file
		outFile.close();//close output file
	}
	catch (const char* ex)//catch exceptions
	{
		if (!strcmp(ex, "output.txt is not valid. Can not write to output file."))//if its problem with output
		{
			cout << ex << endl;//tell the user and quit
			exit(1);
		}
		if (!strcmp(ex, "input.txt is not valid"))//if its problem with input file
		{
			ofstream outFile("output.txt", ios::out);//if got here , the open already succeded
			outFile << ex << endl;//tell the user in the output file 
			outFile.close();//close output file
			exit(1);//quit
		}
		if (!strcmp(ex, "Allocation error"))//if its my allocation check - catch it
		{
			cout << "Allocation failed, program stopped";//tell the user on the error
			exit(1);//quit
		}
		cout << "Unexpected error. Program terminated." << endl;//other char* exceptions
		exit(1);//quit
	}
	catch (...)//catch any exception
	{
		cout << "Unexpected error. Program terminated." << endl;//other exceptions
		exit(1);//quit
	}
}

