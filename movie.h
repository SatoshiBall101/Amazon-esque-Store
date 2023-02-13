#ifndef MOVIE_H
#define MOVIE_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"

class Movie : public Product
{
	public:

		Movie(const std::string category, const std::string name, const double price, int qty, const std::string genre, const std::string rating);
		virtual ~Movie();
		std::set<std::string> keywords() const;
		std::string displayString() const;
		void dump(std::ostream& os) const;

		// Accessors
	
		std::string getGenre() const;
		std::string getRating() const;

	private:

		std::string genre_;
		std::string rating_;

};
#endif