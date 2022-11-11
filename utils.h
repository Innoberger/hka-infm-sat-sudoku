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