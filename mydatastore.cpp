#include "mydatastore.h"


using namespace std;

MyDataStore::MyDataStore()
{

}

MyDataStore::~MyDataStore()
{
	
	vector<Product*>::iterator it1;
	for (it1 = productDB_.begin(); it1 != productDB_.end(); ++it1) 
	{
  	delete *it1;
	}

	map<std::string, User*>::iterator it2;
	for (it2 = userDB_.begin(); it2 != userDB_.end(); ++it2) 
	{
  	delete it2->second;
	}
	
}

void MyDataStore::addProduct(Product* p)
{
	if(p != nullptr)
	{
		productDB_.push_back(p); // add product to product database

		// we also need to update keyProd_ (map: keywords to set of products)

		set<string> keywordSet = p->keywords();

		set<string>::iterator it;

		for (it = keywordSet.begin(); it != keywordSet.end(); it++)
		{
			if(keyProd_.end() == keyProd_.find(*it)) // if the keyword is new to map
			{
				// create a new set of products and insert current prod

				set<Product*> prods;
				prods.insert(p);

				// insert new keyword-prodset into the map

				keyProd_.insert(pair<string, set<Product*>>(*it, prods));
			}
			else if(keyProd_.find(*it) != keyProd_.end()) // if keyword exists in map
			{
				keyProd_.find(*it)->second.insert(p); // add product to exisiting prod set
			}
		}
	}

}


void MyDataStore::addUser(User* u)
{

	string username = convToLower(u->getName());
	
	userDB_.insert(pair<string, User*>(username, u)); // add user to user database

	// also need to initialize user's cart with no products

	vector<Product*> emptyCart;

	usrCart_.insert(pair<string, vector<Product*>>(username, emptyCart)); // add new username and empty prod vector 	
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type)
{
	// in order to use setunion and set intersection, we will process products w a set

	set<Product*> temp;
	bool frstItr = true;
	bool andSearch = false;
	bool orSearch = false;

	if (type == 0)
	{
		andSearch = true;
	}
	else if (type == 1)
	{
		orSearch = true;
	}
	

	for (size_t i = 0; i < terms.size(); i++)
	{
		if(keyProd_.find(terms[i]) != keyProd_.end()) // if searched word has associated products
		{
			if(frstItr)
			{
				temp = keyProd_[terms[i]]; // assign temp product set the set associated w key: terms[i]
				frstItr = false;
			}
			if(andSearch)
			{
				temp = setIntersection(temp, keyProd_[terms[i]]);
			}
			if(orSearch)
			{
				temp = setUnion(temp, keyProd_[terms[i]]);
			}
		}
	}

	// copy set into vector to match return type

	vector<Product*> retVec(temp.begin(), temp.end());
	return retVec;

}

vector<Product*> MyDataStore::viewCart(string username) const
//void MyDataStore::viewCart(string username) const
{

	// check if username is valid

	vector<Product*> retVec = {};

	if(userDB_.find(convToLower(username)) == userDB_.end())
	{
		cout << "Invalid Username" << endl;
		vector<Product*> empty;
		return empty;
	}
	else // if it is valid
	{
		map<string, vector<Product*>>::const_iterator it;

		it = usrCart_.find(convToLower(username)); // make an itrtr to point at the username/product vector pair

		for(vector<Product*>::const_iterator it1 = it->second.end() - 1; it1 >= it->second.begin(); --it1)
		{
			
			retVec.push_back(*it1);
		}

	}
	return retVec;
	
}

void MyDataStore::buyCart(string username)
{
	// check if username is valid

	if(usrCart_.find(convToLower(username)) == usrCart_.end())
	{
		cout << "Invalid Username" << endl;
		return;
	}

	// check if cart has any products

	map<string, vector<Product*>>::iterator it;
	map<string, User*>::iterator usrIt;

	it = usrCart_.find(convToLower(username));
	usrIt = userDB_.find(convToLower(username));

	if(it->second.size() == 0)
	{
		cout << "Cart is empty." << endl;
		return;
	}

	// now we will go through each item in cart and purchase in FIFO order

	vector<Product*> unpurchasedProd; // save unpurchased products

	vector<Product*>::iterator itv;

	for(itv = it->second.end() - 1; itv >= it->second.begin() ; itv--)
	//for(size_t i = 0; i < it->second.size() - 1; i++)
	{  

		if (*itv == nullptr) {
      cout << "Found a null product pointer in the cart. Skipping..." << endl;
      continue;
    }

		double prodPrice = (*itv)->getPrice();

		if((*itv)->getQty() >= 1 && usrIt->second->getBalance() >= prodPrice)
		{
			// if prod is in stock and user balance is sufficient 

			usrIt->second->deductAmount(prodPrice); // charge customer

			(*itv)->subtractQty(1); // update stock info

			cout << "Your purchase has been processed!" << endl;

		}
		else
		{
			cout << "Your order could not be processed because: " << endl;

			if ((*itv)->getQty() == 0)
			{
				cout << (*itv)->getName() << " is currently out of stock." << endl;
			}
			if (usrIt->second->getBalance() < prodPrice)
			{
				cout << "Your balance (" << usrIt->second->getBalance() << ") is lower than the items cost: " << prodPrice << endl;
			}

			unpurchasedProd.push_back(*itv);
		}
		
	}

	usrCart_[username] = unpurchasedProd; // items should stay in cart if they arent purchased successfully
}

void MyDataStore::addToCart(std::string username, Product* p)
{
	// check if username is valid

	if(userDB_.find(convToLower(username)) == userDB_.end())
	{
		cout << "Invalid request" << endl;
		return;
	}
	else // if it is valid
	{
		 map<string, vector<Product*>>::iterator it;

		 it = usrCart_.find(convToLower(username));

		 it->second.push_back(p); // add product to user's associated prod vector

		 cout << "Product added to cart." << endl;
	}
}

void MyDataStore::dump(std::ostream& ofile)
{
	ofile << "<products>" << "\n";
	
	for(size_t i = 0; i < productDB_.size(); i++)
	{
		productDB_[i]->dump(ofile);
	}

	ofile << "</products>" << "\n" << "<users>" << "\n";

	map<string, User*>::iterator it;
	
	for(it = userDB_.begin(); it != userDB_.end(); it++)
	{
		it->second->dump(ofile);
	}

	ofile << "</users>" << "\n";
}