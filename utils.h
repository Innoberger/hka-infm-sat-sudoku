/**
 * This is the utils file.
 */

#include <iostream>
#include <list>

using namespace std;

/*
 * Tokenizes a string into a list<string> by splitting at a delimiter.
 */
list<string> tokenize(string const &str, const char delim) {
    size_t start;
    size_t end = 0;
    list<string> out;

    while ((start = str.find_first_not_of(delim, end)) != string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }

    return out;
}
 