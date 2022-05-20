/*****************************************************************************************
*  Program Name: ProgrammingAssignment4
*  Created Date: 4/18/19
*  Created By: Shawn Ruby
*  Purpose: Creates a library database
*  Acknowledgements: None
*****************************************************************************************/

#include <iostream>
#include <fstream>
#include "Library.h"
#include <stdio.h>

using std::ifstream;
using std::ofstream;
using std::cerr;
using std::endl;
using std::exception;
int main()
{
	try
	{
		ifstream inFile; //Get an input file of data to process
		inFile.open("BookInfo.txt"); //Get file ready to read input


		ofstream outFile; //Get an output file to write data out to
		outFile.open("Results.txt"); // opens log file

		Library myLibrary;
		myLibrary.ProcessItems(inFile); //Read and process all data from the file
		myLibrary.UserInput(outFile); //user input
		outFile.close(); // closes log file
		outFile.open("BookInfo2.txt"); //Get file ready to write data to write data back to file
		myLibrary.PrintItems(outFile); //Print out all book info back to input file
		


		inFile.close(); //Need to close our input and output files
		outFile.close();
		remove("BookInfo.txt"); // removes the original file name
		rename("BookInfo2.txt", "BookInfo.txt"); // renames secondary file as the original file
	}
	catch (exception& ex) //Catch any errors that occure and display them in the console to the user
	{
		cerr << "An error occured: " << ex.what() << endl;
		system("pause");
		return 1;
	}

	return 0;
}