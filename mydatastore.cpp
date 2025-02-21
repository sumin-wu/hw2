#include "mydatastore.h"
#include "datastore.h"
#include "user.h"
#include "util.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <map>
#include "product.h"

/**
     * Adds a product to the data store
     */

MyDataStore::~MyDataStore(){
    // delete users
    for (std::map<std::string, User*>:: iterator it= users_li.begin(); it!=users_li.end(); ++it){
         delete it->second;
   }
    
    // delete products
    for(size_t i = 0; i < products_li.size(); i++){
        delete products_li[i];
    }
}

void MyDataStore::addProduct(Product* p){
    products_li.push_back(p);
    std::set <std::string> keyW= p->keywords();
    std::set <std::string> ::iterator it;
    for (it = keyW.begin(); it != keyW.end(); it++)
    {
        std::string key_lower = convToLower(*it);
        
        if (keywords_product.find(key_lower)==keywords_product.end()) //keyword isnt associated with product in data store
        {
            std::set <Product*> x;
            x.insert(p);
            keywords_product.insert(std::pair<std::string, std::set<Product*> >(key_lower, x));
        }
        else //keyword is found in data store
        {//insert product into the set of products associated with the keyword

            keywords_product.find(key_lower)->second.insert(p);
        }
    }
}

void MyDataStore::addUser(User* u){
    std::string username = convToLower(u->getName());
    
    if (users_li.find(username)==users_li.end())
    {
      std::cout<<username<<std::endl;
      std::vector <Product *> c; //users cart
      carts_.insert(std::make_pair(username, c));
      users_li.insert(std::make_pair(username, u)); //insert the user into the users map
      //std::cout<<users_li.size()<<std::endl;
    }
}

/**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection)
     *  type 1 = OR search (union)
     */
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
    std::set<Product*> result; //set of products that match the key word
    std::vector<Product*> result_vector;
    if (terms.empty())
    {
        return result_vector;
    }
    if (type==1){//OR search
        for (std::string s: terms)
        {
            //std::cout<<"searching term"<<s<<std::endl;//?
            s = convToLower(s);
            if (keywords_product.find(s)!=keywords_product.end())//
            {
                //std::cout<<"found product"<<std::endl;//?
                result = setUnion(keywords_product.find(convToLower(s))->second, result);//
            }
        }
    }
    else{ //AND search
        for (std::string s: terms)
        {
            if (keywords_product.find(convToLower(s))!=keywords_product.end())//
            {
                if (result.empty())
                {
                    result= keywords_product.find(convToLower(s))->second;//intersection only works with result containing one set already
                }
                result = setIntersection(keywords_product.find(convToLower(s))->second, result);//
            }
            else{
                break; //first term doesn't exist in keywords of product, so AND search fails
            }
        }
    }
    
    result_vector.insert(result_vector.end(),result.begin(),result.end());
    return result_vector;
}

void MyDataStore::dump(std::ostream& ofile)
{
    ofile << "<products>" << std::endl;
    for (std::vector<Product*>:: iterator it = products_li.begin(); it!= products_li.end(); it++){
         (*it)->dump(ofile);
    }
    ofile << "</products>" << std::endl;
    ofile << "<users>" << std::endl;
    for (std::map <std::string, User*>:: iterator it = users_li.begin(); it!= users_li.end(); it++){
         it->second->dump(ofile);
    }
    ofile << "</users>" << std::endl;
}

void MyDataStore::addtoCart(std::string username, int hit_result_index, std::vector<Product*> hits){
    //std::map<std::string, std::vector<Product*> > carts_; 
     std::string username1 = convToLower(username);
    //check if user exists
    // for (std::map<std::string, User*>::iterator it= users_li.begin(); it!=users_li.end(); it++){
    //   std::cout<<"username "<<it->first<<std::endl;
    // }
    if (users_li.find(username1)==users_li.end()){//no user
        std::cout<<"Invalid Request"<<std::endl;
        //std::cout<<"in here"<<std::endl;
        return;
    }
    if (hit_result_index-1<hits.size()&&hit_result_index>-1)
    {
        //if user doesnt have a cart
        if (carts_.find(username1)==carts_.end())
        {
            std::vector <Product *> cart;
            carts_.insert(make_pair(username1, cart));
        }
        carts_.find(username1)->second.push_back(hits[hit_result_index-1]);
    }
    else{
        std::cout<<"Invalid Request"<<std::endl;
        return;
    }
}

void MyDataStore::viewCart(std::string username){
    if (users_li.find(username)==users_li.end())
    {
        std::cout<<"Invalid username"<<std::endl;
        return;
    }
    std::map <std::string, std::vector <Product*> >::iterator it = carts_.find(username);//returns iterator to this pair
    int iter = 1;
    for (Product* p : it->second){
        std::cout<<"Item "<<iter<<std::endl;
        std::cout<<p->displayString()<<std::endl;
        iter++;
    }
    if (iter==1)
    {
        std::cout<<"Cart is empty"<<std::endl;
    }

}

void MyDataStore::buyCart(std::string username){
    username = convToLower(username);
    if (users_li.find(username)==users_li.end())
    {
        std::cout<<"Invalid username"<<std::endl;
        return;
    }
    std::vector <Product *> newCart;

    for (Product *p : carts_[username]){
        //check if product is in stock
        if (p->getQty()>0){
            if (users_li[username]->getBalance()>p->getPrice())//check balance
            {
                users_li[username]->deductAmount(p->getPrice());//deduct balance
                p->subtractQty(1);//subtract qty
                //(carts_.find(username)->second).erase((carts_.find(username)->second).begin());
                if (p->getQty()!=0)//even after buying or if not bought, if theres still qty left, add to new cart
                {
                newCart.push_back(p);
                }
            }
        }
    }
    carts_[username]=newCart;
}