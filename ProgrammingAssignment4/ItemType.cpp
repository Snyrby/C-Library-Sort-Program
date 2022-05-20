// The following definitions go into file ItemType.cpp. 
#include <fstream>
#include <iostream>
#include "ItemType.h"

using std::string;
using std::cout;
using std::endl;
using std::cin;


ItemType::ItemType()
{ 
  value = "";
  Author = "";
  Subject = "";
}

RelationType ItemType::ComparedTo(ItemType otherItem) const 
{
  if (value < otherItem.value)
    return LESS;
  else if (value > otherItem.value)
    return GREATER;
  else return EQUAL;
}

/* initializes function */
void ItemType::Initialize(string CurrentTitle, string CurrentAuthor, string CurrentSubject) 
{
  value = CurrentTitle;
  Author = CurrentAuthor;
  Subject = CurrentSubject; 
}

/* initializes function */
void ItemType::Initialize2(string CurrentTitle)
{
	value = CurrentTitle;
}

/* print function to place back in input file */
void ItemType::Print(std::ostream& out) const 
// pre:  out has been opened.
// post: value has been sent to the stream out.
{
	out << value << endl;
	out << Author << endl;
	out << Subject << endl;
}

/* function that capitalizes every first letter of every word */
void ItemType::CapitalizeLetters()
{
	int LengthAuthor = Author.length();
	int LengthTitle = value.length();
	


	Author[0] = toupper(Author[0]);
	value[0] = toupper(value[0]);


	for (int i = 1; i < LengthAuthor; i++)
	{
		if (Author[i - 1] == ' ')
		{
			Author[i] = toupper(Author[i]);
		}
	}
	for (int i = 1; i < LengthTitle; i++)
	{
		if(value[i - 1] == ' ')
		{
			value[i] = toupper(value[i]);
		}
		else
		{
			value[i] = tolower(value[i]);
		}
	}
}

/* returns author */
string ItemType::ReturnAuthor()
{
	return Author;
}

/* returns title */
string ItemType::ReturnTitle()
{
	return value;
}

/* returns subject */
string ItemType::ReturnSubject()
{
	return Subject;
}

