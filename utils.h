/**
 * This is the utils file.
 */

#include <iostream>
#include <list>

using namespace std;

/*
 * Overloads the << operator to be able to be used with list<unsigned int>.
 */
ostream &operator<<(ostream &os, const list<unsigned int> &list) {
    for (auto const &i: list) {
        os << i << endl;
    }
    return os;
}

/*
 * Overloads the << operator to be able to be used with list<string>.
 */
ostream &operator<<(ostream &os, const list<string> &list) {
    for (auto const &i: list) {
        os << i << endl;
    }
    return os;
}

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
 