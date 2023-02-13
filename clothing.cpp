#include "clothing.h"
#include <cctype>
#include <cstring>

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, string size, string brand)
 : Product(category, name, price, qty), size_(size), brand_(brand)
{}

Clothing::~Clothing()
{}

set<string> Clothing::keywords() const
{

	set<string> allKeywords;

	// break up product name by custom keyword def

	set<string> productNameKW = parseStringToWords(getName()); 

	set<string>::iterator it;

	for (it = productNameKW.begin(); it != productNameKW.end(); it++)
	{
		string temp = convToLower(*it);
		
		allKeywords.insert(temp); // add lowercase KW from product name
	}

	// break up brand name by custom keyword def

	set<string> productBrandKW = parseStringToWords(getBrand()); 

	for (it = productBrandKW.begin(); it != productBrandKW.end(); it++)
	{
		string temp = convToLower(*it);
		
		allKeywords.insert(temp); // add lowercase KW from brand name
	}

	return allKeywords;

}

std::string Clothing::displayString() const
{

	stringstream ss;

	ss << getName() << endl << "Size: " << getSize() << " Brand: " << getBrand() << endl << getPrice() << " " << getQty() << " left.";

	return ss.str();

}

void Clothing::dump(std::ostream& os) const
{
	Product::dump(os);
	os << size_ << "\n" << brand_ << endl;

}

std::string Clothing::getSize() const
{
	return size_;
}

std::string Clothing::getBrand() const
{
	return brand_;
}

