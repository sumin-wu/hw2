#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"
#include "product.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    std::set<std::string> words; //set of key words
    
    std::string word; // to hold the current key word found
    
    for (char c : rawWords) 
    {
        if (!isspace(c) && !ispunct(c)) { //check if theres a space or punctuation
            word += c;
        } else 
        { //there is a space or punctuation
            if (word.length() > 1) 
            {
                words.insert(convToLower(word)); //insert the word into the set
            }
            word = "";         //this else statement skips the space or punctuation and does not doing anything with that character
            }
    }
    if (!word.empty()){
      words.insert(convToLower(word)); //add last word
    }

    return words;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
