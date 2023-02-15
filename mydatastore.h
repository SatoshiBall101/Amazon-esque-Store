#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "user.h"
#include "datastore.h"
#include "clothing.h"
#include "movie.h"
#include "book.h"
#include "util.h"
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>

class MyDataStore : public DataStore
{
	public:
		
		MyDataStore();
		~MyDataStore();
		void addProduct(Product* p); //
		void addUser(User* u); //
		std::vector<Product*> search(std::vector<std::string>& terms, int type);  //
		// type 1 means AND (intersection), type 2 means OR (union)
		std::vector<Product*> viewCart(std::string username) const; //
		void buyCart(std::string username); 
		void addToCart(std::string username, Product* p); //
		void dump(std::ostream& ofile); //

	private:

		std::map<std::string, std::set<Product*>> keyProd_; // map keyword to set of products
		std::map<std::string, std::vector<Product*>> usrCart_; // map username to products in their cart	
		std::vector<Product*> productDB_;
		std::map<std::string, User*> userDB_; // map unique username (key) to user ptrs
};
#endif