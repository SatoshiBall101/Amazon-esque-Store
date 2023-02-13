#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

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
    set<string> keyWords; // create the set of keywords

    stringstream ss; // put string into ss

		ss << rawWords;
    
    string word;

    while (ss >> word)
    {
			for (size_t i = 0; i < word.size(); i++)
			{
				if (ispunct(word[i])) // if the character is punctuation
				{
					word[i] = ' '; // break up the word into subwords
				}
			}

			stringstream subWord_ss; // create another ss 
			subWord_ss << word; // put subword into ss

			string subWord;

			while (subWord_ss >> subWord)
			{
				if(subWord.size() >= 2) // if the size of subword >=2, add it to set
				{
					keyWords.insert(subWord);
				}
			}
    }

		return keyWords;

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
