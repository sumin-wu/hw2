#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <map>
#include "product.h"
#include "user.h"
#include "datastore.h"

class MyDataStore : public DataStore
{
public:
    MyDataStore(){};
    ~MyDataStore();
    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p);

    /**
     * Adds a user and the items in their cart to the data store
     */
    void addUser(User* u);
    void addtoCart(std::string username, int hit_result_index, std::vector<Product*> hits);
    void buyCart(std::string username);
    void viewCart(std::string username);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection)
     *  type 1 = OR search (union)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile);

    private:
  
    std::map<std::string, User*> users_li;//user map
    std::vector<Product*> products_li;//product list

    //map for products and keywords
    std::map<std::string, std::set<Product* > > keywords_product;
    //user usernames and carts
    std::map<std::string, std::vector<Product*> > carts_; 
};

#endif