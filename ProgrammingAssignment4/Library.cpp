#include "Library.h"
#include <iostream>
#include <string>
#include "ItemType.h"
#include <algorithm>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::getline;

/*****************************************************************************************
*  function Name: UserInput(ofstream& outFile)
*  Parameters: inFile
*  Return Value: none
*  Purpose: function that asks the user whether to insert a book, delete, arrange the library or quit
*****************************************************************************************/

void Library::UserInput(ofstream& outFile)
{
	string input;
	string Sort;
	/* do loop that loops until the user types quit */
	do
	{
		/* input validation for user input. converts user input to all caps */
		do
		{
			cout << "Type Insert to insert a new book's info.\nType Delete to delete a book's info.\nType List to organize all of the books.\nType quit to save the program and exit. ";
			cin >> input;
			cout << endl;
			transform(input.begin(), input.end(), input.begin(), toupper);

		} while (!(input == "INSERT" || input == "DELETE" || input == "LIST" || input == "QUIT"));

		/* if the user types insert, it will run the insert function */
		if (input == "INSERT")
		{
			NewBook(outFile);
		}

		/* if the user types delete, it will run the delete function */
		else if (input == "DELETE")
		{
			DeleteBook(outFile);
		}

		/*If the user types list, it will begin to arrage lists */
		else if (input == "LIST")
		{

			/* input validation for asking the user how they would like to sort the lists */
			do
			{
				cout << "How would you like to sort by? Title, Author, or Subject: ";
				cin >> Sort;
				transform(Sort.begin(), Sort.end(), Sort.begin(), toupper);
			} while (!(Sort == "TITLE" || Sort == "AUTHOR" || Sort == "SUBJECT"));

			/* if the user types title, it will sort the data by title */
			if (Sort == "TITLE")
			{
				cout << endl;
				SortByTitle(outFile);
			}

			/* if the user types author, it will sort the data by author */
			else if (Sort == "AUTHOR")
			{
				cout << endl;
				SortByAuthor(outFile);
			}

			/* if the user types subject, it will sort the data by subject */
			else if (Sort == "SUBJECT")
			{
				cout << endl;
				SortBySubject(outFile);
			}
		}
	} while (input != "QUIT");
	/* command that onces the file ends, it will say the file was saved */
	outFile << "The file was successfully saved.";
}

/*****************************************************************************************
*  function Name: ProcessItems(ifstream& inFile)
*  Parameters: inFile
*  Return Value: none
*  Purpose: process all data from the library text file
*****************************************************************************************/

void Library::ProcessItems(ifstream& inFile)
{
	string CurrentTitle;
	string CurrentAuthor;
	string CurrentSubject;
	ItemType New;
	ItemType Title;
	ItemType Author;
	ItemType Subject;

	/* makes the unsorted list empty */
	BookData.MakeEmpty();

	/* do loop that will loop until the library is full */
	do
	{
		/* loops until the end of the file */
		while (!inFile.eof())
		{
			/* get line that stores the title, author and subject from the text file */
			getline(inFile, CurrentTitle);
			getline(inFile, CurrentAuthor);
			getline(inFile, CurrentSubject);

			/* if function that says if the title is not a white space, it will put the data into the sorted lists */
			if (CurrentTitle != "")
			{
				/* initializes the data and puts it into a unsorted inventory list */
				New.Initialize(CurrentTitle, CurrentAuthor, CurrentSubject);
				BookData.PutItem(New);

				/* initializes the current title and puts it into a sorted list for titles */
				New.Initialize2(CurrentTitle);
				TitleOrder.PutItem(New);

				/* initializes the current author and puts it into a sorted list for author */
				New.Initialize2(CurrentAuthor);
				AuthorOrder.PutItem(New);

				/* initializes the current subject and puts it into a sorted list for subject */
				New.Initialize2(CurrentSubject);
				SubjectOrder.PutItem(New);

				/* if the inventory list is full, it will write and error message */
				if (BookData.IsFull())
				{
					cout << "The Library is full!\n";
				}
			}
		}
		/* if the list is not full and the file is empty, it will break the loop to continue */
		break;
	} while (!BookData.IsFull());
}

/*****************************************************************************************
*  function Name: PrintItems(ofstream& outFile)
*  Parameters: outFile
*  Return Value: none
*  Purpose: prints all data within the inventory list back to the text file
*****************************************************************************************/

void Library::PrintItems(ofstream& outFile)
{
	BookData.ResetList();
	ItemType item;
	for (int count = 0; count < BookData.GetLength(); count++)
	{
		item = BookData.GetNextItem();
		item.Print(outFile);
	}
}

/*****************************************************************************************
*  function Name: PrintItems(ofstream& outFile)
*  Parameters: outFile
*  Return Value: none
*  Purpose: contains all data to insert new books to the lists
*****************************************************************************************/

void Library::NewBook(ofstream& outFile)
{
	string CurrentTitle;
	string CurrentAuthor;
	string CurrentSubject;
	string First;
	string Last;
	int LengthTitle;
	int LengthAuthor;
	int LengthSubject;
	ItemType New;
	ItemType Book2;

	/* resets all 3 lists */
	TitleOrder.ResetList();
	AuthorOrder.ResetList();
	SubjectOrder.ResetList();

	/* asks the user for the title */
	cout << "What is the book's title? ";
	cin.ignore();
	getline(cin, CurrentTitle);

	/* asks the user for the author's first name */
	cout << "What is the author's first name? ";
	cin >> First;

	/* asks the user for the author's last name */
	cout << "What is the author's last name? ";
	cin >> Last;

	/* converts the author to format last, first */
	CurrentAuthor = Last + ", " + First;
	cin.ignore();

	/* asks the user for the subject of the book */
	cout << "What is the subject of the book? ";
	getline(cin, CurrentSubject);

	/* initializes the variables */
	New.Initialize(CurrentTitle, CurrentAuthor, CurrentSubject);

	/* function that capitalizes every first letter of every word of the title and the author */
	New.CapitalizeLetters();

	/* sets the title and author to the capitalized version */
	CurrentTitle = New.ReturnTitle();
	CurrentAuthor = New.ReturnAuthor();

	/* puts the data into the inventory file */
	BookData.PutItem(New);

	/* initializes the title and puts it into the title list */
	New.Initialize2(CurrentTitle);
	TitleOrder.PutItem(New);

	/* loops through to figure out which position the title was inserted into the list */
	for (int i = 0; i < TitleOrder.GetLength(); i++)
	{
		Book2 = TitleOrder.GetNextItem();
		if (Book2.ReturnTitle() == CurrentTitle)
		{
			LengthTitle = i + 1;
		}
	}

	/* initializes the author and puts it into the author list */
	New.Initialize2(CurrentAuthor);
	AuthorOrder.PutItem(New);

	/* loops through to figure out which position the author was inserted into the list */
	for (int i = 0; i < AuthorOrder.GetLength(); i++)
	{
		Book2 = AuthorOrder.GetNextItem();
		if (Book2.ReturnAuthor() == CurrentAuthor)
		{
			LengthAuthor = i + 1;
		}
	}

	/* initializes the subject and puts it into the subject list */
	New.Initialize2(CurrentSubject);
	SubjectOrder.PutItem(New);

	/* loops through to figure out which position the subject was inserted into the list */
	for (int i = 0; i < SubjectOrder.GetLength(); i++)
	{
		Book2 = SubjectOrder.GetNextItem();
		if (Book2.ReturnSubject() == CurrentSubject)
		{
			LengthSubject = i + 1;
		}
	}

	cout << endl << CurrentTitle << " has been added.\n\n";

	/* sets command to log file that inputs which place each piece of data was inputted into the lists */
	outFile << CurrentTitle << " has been inserted into the library.\n" << CurrentTitle << " has been inserted into the position in the title list " << LengthTitle << endl;
	outFile << CurrentAuthor << " has been inserted into the position in the Author list " << LengthAuthor << endl;
	outFile << CurrentSubject << " has been inserted into the position in the Subject list " << LengthSubject << endl << endl;

}

/*****************************************************************************************
*  function Name: DeleteBook(ofstream& outFile)
*  Parameters: outFile
*  Return Value: none
*  Purpose: contains all data to delete books from the lists
*****************************************************************************************/

void Library::DeleteBook(ofstream& outFile)
{
	string CurrentTitle;
	string CurrentAuthor;
	string CurrentSubject;
	int LengthTitle;
	int LengthAuthor;
	int LengthSubject;
	ItemType Book;
	ItemType Book2;
	bool found;
	

	/* do loop that loops until the user inputs a book that is found */
	do
	{
		/* asks the user what book they would like to delete */
		cout << "What is the book you would like to delete? ";
		cin.ignore();
		getline(cin, CurrentTitle);

		/* initializes the title */
		Book.Initialize2(CurrentTitle);

		/* capitalzies the user's input to match the records */
		Book.CapitalizeLetters();

		/* sets the title to the capitalized version*/
		CurrentTitle = Book.ReturnTitle();

		/* tries to find the book in the list and stores it to the itemtype book */
		Book = BookData.GetItem(Book, found);
		if (found)
		{
			/* resets all 3 lists */
			TitleOrder.ResetList();
			AuthorOrder.ResetList();
			SubjectOrder.ResetList();

			/* gets title variable */
			Book.ReturnTitle();

			/* loops through to find the position of the book title being deleted */
			for (int i = 0; i < TitleOrder.GetLength(); i++)
			{
				Book2 = TitleOrder.GetNextItem();
				if (Book2.ReturnTitle() == CurrentTitle)
				{
					LengthTitle = i + 1;
				}
			}

			/* deletes the book from the inventory files */
			BookData.DeleteItem(Book);

			/* deletes the title from the title list */
			TitleOrder.DeleteItem(Book);

			/* gets the author */
			CurrentAuthor = Book.ReturnAuthor();

			/* initializes the author */
			Book.Initialize2(CurrentAuthor);

			/* loops through to find the position of the book author being deleted */
			for (int i = 0; i < AuthorOrder.GetLength(); i++)
			{
				Book2 = AuthorOrder.GetNextItem();
				if (Book2.ReturnAuthor() == CurrentAuthor)
				{
					LengthAuthor = i + 1;
				}
			}

			/* deletes the title from the author list */
			AuthorOrder.DeleteItem(Book);

			/* gets the subject */
			CurrentSubject = Book.ReturnSubject();

			/* initializes the subject */
			Book.Initialize2(CurrentSubject);

			/* loops through to find the position of the book subject being deleted */
			for (int i = 0; i < SubjectOrder.GetLength(); i++)
			{
				Book2 = SubjectOrder.GetNextItem();
				if (Book2.ReturnSubject() == CurrentSubject)
				{
					LengthSubject = i + 1;
				}
			}

			/* deletes the title from the subject list */
			SubjectOrder.DeleteItem(Book);

		}
		/* error saying the book is not found*/
		else
		{
			cout << "\nThat book is not found\n\n";
		}
	} while (!found);

	/* commands for log file that says the position of each data being deleted */
	outFile << CurrentTitle << " has been removed from the library.\n" << CurrentTitle << " has been removed from position in the title list " << LengthTitle << endl;
	outFile << CurrentAuthor << " has been removed from position in the Author list " << LengthAuthor << endl;
	outFile << CurrentSubject << " has been removed from position in the Subject list " << LengthSubject << endl << endl;
	cout << endl << CurrentTitle << " has been deleted.\n\n";
}

/*****************************************************************************************
*  function Name: SortByAuthor(ofstream& outFile)
*  Parameters: outFile
*  Return Value: none
*  Purpose: contains all data to sort by author
*****************************************************************************************/

void Library::SortByAuthor(ofstream& outFile)
{
	string CurrentAuthor;
	ItemType item;
	ItemType item2;

	/* resets the author list */
	AuthorOrder.ResetList();

	/* loops through the author list */
	for (int i = 0; i < AuthorOrder.GetLength(); i++)
	{
		/* resets the book inventory */
		BookData.ResetList();

		/* gets next item in the list */
		item = AuthorOrder.GetNextItem();

		/* cout message for the author */
		cout << "Author: " << item.ReturnAuthor() << endl;
		outFile << "Author: " << item.ReturnAuthor() << endl;

		/* loops through the inventory file to find the title and subject associated with the author */
		for (int i = 0; i < BookData.GetLength(); i++)
		{
			item2 = BookData.GetNextItem();
			if (item.ReturnAuthor() == item2.ReturnAuthor())
			{
				cout << " Title: " << item2.ReturnTitle() << endl;
				outFile << " Title: " << item2.ReturnTitle() << endl;

				cout << " Subject: " << item2.ReturnSubject() << endl << endl;
				outFile << " Subject: " << item2.ReturnSubject() << endl << endl;
			}
		}

	}
	outFile << "The library was sorted by Author.\n\n";
}

/*****************************************************************************************
*  function Name: SortByTitle(ofstream& outFile)
*  Parameters: outFile
*  Return Value: none
*  Purpose: contains all data to sort by title
*****************************************************************************************/

void Library::SortByTitle(ofstream& outFile)
{
	string CurrentTitle;
	ItemType item;
	ItemType item2;

	/* resets the title list */
	TitleOrder.ResetList();

	/* loops through the title list */
	for (int i = 0; i < TitleOrder.GetLength(); i++)
	{
		/* resets the book inventory */
		BookData.ResetList();

		/* gets next item in the list */

		/* cout message for the title */
		item = TitleOrder.GetNextItem();
		cout << "Title: " << item.ReturnTitle() << endl;
		outFile << "Title: " << item.ReturnTitle() << endl;

		/* loops through the inventory file to find the author and subject associated with the title */
		for (int i = 0; i < BookData.GetLength(); i++)
		{
			item2 = BookData.GetNextItem();
			if (item.ReturnTitle() == item2.ReturnTitle())
			{
				cout << " Author: " << item2.ReturnAuthor() << endl;
				outFile << " Author: " << item2.ReturnAuthor() << endl;

				cout << " Subject: " << item2.ReturnSubject() << endl << endl;
				outFile << " Subject: " << item2.ReturnSubject() << endl << endl;
			}
		}

	}
	outFile << "The library was sorted by title.\n\n";
}

/*****************************************************************************************
*  function Name: SortBySubject(ofstream& outFile)
*  Parameters: outFile
*  Return Value: none
*  Purpose: contains all data to sort by subject
*****************************************************************************************/

void Library::SortBySubject(ofstream& outFile)
{
	string CurrentSubject;
	ItemType item;
	ItemType item2;

	/* resets the title list */
	SubjectOrder.ResetList();

	/* loops through the subject list */
	for (int i = 0; i < SubjectOrder.GetLength(); i++)
	{
		/* resets the book inventory */
		BookData.ResetList();

		/* gets next item in the list */
		item = SubjectOrder.GetNextItem();

		/* cout message for the subject */
		cout << "Subject: " << item.ReturnSubject() << endl;
		outFile << "Subject: " << item.ReturnSubject() << endl;

		/* loops through the inventory file to find the title and author associated with the subject */
		for (int i = 0; i < BookData.GetLength(); i++)
		{
			item2 = BookData.GetNextItem();
			if (item.ReturnSubject() == item2.ReturnSubject())
			{
				cout << " Title: " << item2.ReturnTitle() << endl;
				outFile << " Title: " << item2.ReturnTitle() << endl;

				cout << " Author: " << item2.ReturnAuthor() << endl << endl;
				outFile << " Author: " << item2.ReturnAuthor() << endl << endl;
			}
		}

	}
	outFile << "The library was sorted by Subject.\n\n";
}

	