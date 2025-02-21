#ifndef CLOTHING_H
#define CLOTHING_H
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <set>
#include <vector>
#include "product.h"
#include "util.h"

using namespace std;

class Clothing : public Product{
public:
    Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand);
    virtual ~Clothing();

    /**
     * Returns the appropriate keywords that this product should be associated with: brand and size
     */
    std::set<std::string> keywords() const;

    /**
     * Returns a string to display the product info for hits of the search
     */
    std::string displayString() const;

    /**
     * Outputs the product info in the database format
     */
    void dump(std::ostream& os) const;
private:
    std::string size_;
    std::string brand_;
};

#endif