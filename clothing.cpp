#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"
#include "product.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand) :
Product(category, name, price, qty)
{
  size_=size;
  brand_=brand;
}

Clothing::~Clothing(){}

std::set<std::string> Clothing::keywords() const{
    std::set<std::string> keywords;
    std::set<std::string> brandWords = parseStringToWords(brand_);
    std::set<std::string> nameWords = parseStringToWords(name_);
    keywords.insert(brandWords.begin(), brandWords.end());
    keywords.insert(nameWords.begin(), nameWords.end());
    keywords.insert(size_);
    return keywords;
}

std::string Clothing::displayString() const{
    std::stringstream ss;
    ss << name_ << "\n" << "Size: " << size_ << " Brand: " << brand_ << "\n" << std::to_string(price_) << " " << std::to_string(qty_) << " left.";
    return ss.str();
}

void Clothing::dump(std::ostream& os) const{
    Product::dump(os);
    os << size_ << "\n" << brand_ << "\n";
}