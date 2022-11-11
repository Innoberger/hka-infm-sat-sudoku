/**
 * This file contains generator methods for SAT constraints.
 */

#include <list>

/*
 * Generates at AtLeastOne constraints.
 */
list<map<unsigned int, bool>> at_least_one_constraints(list<list<unsigned int>> indices) {
    list<map<unsigned int, bool>> constraints;

    while (!indices.empty()) {
        list<unsigned int> elems = indices.back();
        map<unsigned int, bool> at_least_one;

        while (!elems.empty()) {
            at_least_one.insert({ elems.back(), true });
            elems.pop_back();
        }

        constraints.push_back(at_least_one);
        indices.pop_back();
    }

    return constraints;
}

/*
 * Generates at AtMostOne constraints.
 */
list<map<unsigned int, bool>> at_most_one_constraints(list<list<unsigned int>> indices) {
    list<map<unsigned int, bool>> constraints;

    while (!indices.empty()) {
        vector<unsigned int> elems(indices.back().size());
        copy(indices.back().begin(), indices.back().end(), elems.begin());

        for (unsigned int i = 0; i < elems.size(); i++) {
            for (unsigned int j = i + 1; j < elems.size(); j++) {
                constraints.push_back({{ elems.at(i), false }, { elems.at(j), false }});
            }
        }

        indices.pop_back();
    }

    return constraints;
}