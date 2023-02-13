#include <iomanip>
#include "movie.h"
#include "util.h"
#include <cctype>

using namespace std;

Movie::Movie(const std::string category, const std::string name, const double price, const int qty, const string genre, const string rating)
	: Product(category, name, price, qty), genre_(genre), rating_(rating)
{}

Movie::~Movie()
{}

set<string> Movie::keywords() const
{

	set<string> allKeywords;

	string tempGenre = convToLower(genre_);

	allKeywords.insert(tempGenre); // include LC genre as keyword

	// break up product name by custom keyword def

	set<string> productNameKW = parseStringToWords(getName()); 

	set<string>::iterator it;

	for (it = productNameKW.begin(); it != productNameKW.end(); it++)
	{
		string temp = convToLower(*it);
		
		allKeywords.insert(temp); // add lowercase KW from product name
	}

	return allKeywords;

}

string Movie::displayString() const
{

	stringstream ss;

	ss << getName() << endl << "Genre: " << getGenre() << " Rating: " << getRating() << endl << getPrice() << " " << getQty() << " left.";

	return ss.str();

}

void Movie::dump(ostream& os) const
{
	Product::dump(os);
	os << genre_ << endl;
	os << rating_ << endl;
}

std::string Movie::getGenre() const
{
	return genre_;
}

std::string Movie::getRating() const
{
	return rating_;
}


