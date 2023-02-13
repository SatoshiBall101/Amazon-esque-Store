#include "book.h"
#include <cctype>
#include <iomanip>

using namespace std;

Book::Book(const std::string category, const std::string name, const double price, const int qty, const string isbn, string author)
 : Product(category, name, price, qty), isbn_(isbn), author_(author)
{}

Book::~Book()
{}

set<string> Book::keywords() const
{

	set<string> allKeywords;

	string tempISBN = convToLower(isbn_);

	allKeywords.insert(tempISBN); // include lowercase ISBN as keyword

	// break up product name by custom keyword def

	set<string> productNameKW = parseStringToWords(getName()); 

	set<string>::iterator it;

	for (it = productNameKW.begin(); it != productNameKW.end(); it++)
	{
		string temp = convToLower(*it);
		
		allKeywords.insert(temp); // add lowercase KW from product name
	}

	// break up author name by custom keyword def

	set<string> authorKW = parseStringToWords(getAuthor()); 

	for (it = authorKW.begin(); it != authorKW.end(); it++)
	{
		string temp = convToLower(*it);
		
		allKeywords.insert(temp); // add lowercase KW from author name
	}

	return allKeywords;

}

std::string Book::displayString() const
{

	stringstream ss;

	ss << getName() << endl << "Author: " << getAuthor() << " ISBN: " << getISBN() << endl << fixed << setprecision(2) << getPrice();
	ss << " " << getQty() << " left.";

	return ss.str();

}


void Book::dump(std::ostream& os) const
{
	Product::dump(os);
	os << isbn_ << endl;
	os << author_ << endl;
}

std::string Book::getISBN() const
{
	return isbn_;
}

std::string Book::getAuthor() const
{
	return author_;
}

