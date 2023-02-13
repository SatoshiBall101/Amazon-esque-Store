#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <vector>
#include <algorithm>
#include "util.h"
#include "product.h"

class Book : public Product
{
	public:

		Book(const std::string category, const std::string name, const double price, const int qty, const std::string isbn, const std::string author);
		virtual ~Book();
		virtual std::set<std::string> keywords() const;
		virtual std::string displayString() const;
		virtual void dump(std::ostream& os) const;

		// Accessors
	
		std::string getISBN() const;
		std::string getAuthor() const;

	protected:

		std::string isbn_;
		std::string author_;

};
#endif