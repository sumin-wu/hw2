#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"
#include "product.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating) :
Product(category, name, price, qty)
{
  genre_=genre;
  rating_=rating;
}

Movie::~Movie(){}

std::set<std::string> Movie::keywords() const{
    std::set<std::string> keywords;
    std::set<std::string> genreWords = parseStringToWords(genre_);
    std::set<std::string> nameWords = parseStringToWords(name_);
    keywords.insert(genreWords.begin(), genreWords.end());
    keywords.insert(nameWords.begin(), nameWords.end());
    keywords.insert(rating_);
    return keywords;
}

std::string Movie::displayString() const{
    std::stringstream ss;
    ss << name_ << "\n" << "Genre: " << genre_ << " Rating: " << rating_ << "\n" << std::to_string(price_) << " " << std::to_string(qty_) << " left.";
    return ss.str();
}

void Movie::dump(std::ostream& os) const{
    Product::dump(os);
    os << genre_ << "\n" << rating_ << "\n";
}
