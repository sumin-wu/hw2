//make a class named Book, derived class from Product
#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"
#include "product.h"
#include <string>
#include <iostream>
#include <set>

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author) : 
Product(category, name, price, qty)
    {
      isbn_= isbn; 
      author_=author;
    }
    
Book::~Book(){}



std::set<std::string> Book::keywords() const{
    std::set<std::string> keywords;
    //works std::cout<<"in book.cpp"<<author_<<std::endl;
    std::set<std::string> authorWords = parseStringToWords(author_);
    std::set<std::string> nameWords = parseStringToWords(name_);
    // for (string s: authorWords){
    //   keywords.insert(s);
    // }
    //std::cout<<"in book.cpp"<<std::endl;
    
    //std::cout<<"in book.cpp"<<std::endl;
    keywords.insert(authorWords.begin(), authorWords.end());
    keywords.insert(isbn_);
    keywords.insert(nameWords.begin(), nameWords.end());
    return keywords;
}

std::string Book::displayString() const{
    std::stringstream ss;
    ss << getName() << "\n" << "Author: " << author_ << " ISBN: " << isbn_ << "\n" << std::fixed<<std::setprecision(2)<<std::to_string(getPrice()) << " " << std::to_string(getQty()) << " left.";
    return ss.str();
}

void Book::dump(std::ostream& os) const
{
    Product::dump(os);
    os << isbn_ << "\n" << author_ << "\n";
}
