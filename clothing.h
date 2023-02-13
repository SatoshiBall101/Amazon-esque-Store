#ifndef CLOTHING_H
#define CLOTHING_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "util.h"
#include "product.h"

class Clothing : public Product {
	public:

		Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand);
		virtual ~Clothing();
		std::set<std::string> keywords() const;
		std::string displayString() const;
		void dump(std::ostream& os) const;

		// Accessors
	
		std::string getSize() const;
		std::string getBrand() const;

	private:

		std::string size_;
		std::string brand_;

};
#endif