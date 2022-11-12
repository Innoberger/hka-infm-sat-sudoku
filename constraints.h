/**
 * This file contains generator methods for SAT constraints.
 */

#include <list>

/*
 * Generates at AtLeastOne constraints.
 */
list<map<size_t, bool>> at_least_one_constraints(list<list<size_t>> indices) {
    list<map<size_t, bool>> constraints;

    while (!indices.empty()) {
        list<size_t> elems = indices.back();
        map<size_t, bool> at_least_one;

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
list<map<size_t, bool>> at_most_one_constraints(list<list<size_t>> indices) {
    list<map<size_t, bool>> constraints;

    while (!indices.empty()) {
        vector<size_t> elems(indices.back().size());
        copy(indices.back().begin(), indices.back().end(), elems.begin());

        for (size_t i = 0; i < elems.size(); i++) {
            for (size_t j = i + 1; j < elems.size(); j++) {
                constraints.push_back({{ elems.at(i), false }, { elems.at(j), false }});
            }
        }

        indices.pop_back();
    }

    return constraints;
}