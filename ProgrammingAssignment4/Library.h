#ifndef LIBRARY_H
#define LIBRARY_H

#include "sorted.h"
#include <fstream>
#include "unsorted.h"

using std::ifstream;
using std::ofstream;
using std::string;

class Library
{
private:
	SortedType TitleOrder;
	SortedType AuthorOrder;
	SortedType SubjectOrder;
	UnsortedType BookData;
public:
	void UserInput(ofstream&);
	void PrintItems(ofstream&);
	void ProcessItems(ifstream&);
	void NewBook(ofstream&);
	void DeleteBook(ofstream&);
	void SortByAuthor(ofstream&);
	void SortByTitle(ofstream&);
	void SortBySubject(ofstream&);
};

#endif
