#ifndef ITEMTYPE_H
#define ITEMTYPE_H
// The following declarations and definitions go into file 
// ItemType.h. 

#include <fstream>
#include <string>
const int MAX_ITEMS = 500;
enum RelationType  {LESS, GREATER, EQUAL};
using std::string;

class ItemType 
{ 
public:
  ItemType();
  RelationType ComparedTo(ItemType) const;
  void Print(std::ostream&) const;
  void Initialize(string, string, string);
  void Initialize2(string);
  void CapitalizeLetters();
  string ReturnAuthor();
  string ReturnTitle();
  string ReturnSubject();
private:
  string value;
  string Author;
  string Subject;
};
 
#endif