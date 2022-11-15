/**
 * This file contains generator methods for SAT constraints.
 */

#include <list>

namespace constraints {
    /*
     * Generates at ExactlyOne constraints.
     * This is basically a merge of AtLeastOne and AtMostOne Constraints,
     * but for performance, this will be calculated in one function.
     */
    cnf_formula exactly_one_of(list<indices_set> indices) {
        cnf_formula constraints;

        while (!indices.empty()) {
            vector<size_t> elems(indices.back().size());
            copy(indices.back().begin(), indices.back().end(), elems.begin());
            clauses at_least_one;

            for (size_t i = 0; i < elems.size(); i++) {
                at_least_one.insert({elems.at(i), true });
                for (size_t j = i + 1; j < elems.size(); j++) {
                    constraints.push_back({{elems.at(i), false}, {elems.at(j), false }});
                }
            }

            constraints.push_back(at_least_one);
            indices.pop_back();
        }

        return constraints;
    }

    /*
     * Generates at AtLeastOne constraints.
     */
    cnf_formula at_least_one_of(list<indices_set> indices) {
        cnf_formula constraints;

        while (!indices.empty()) {
            indices_set elems = indices.back();
            clauses at_least_one;

            while (!elems.empty()) {
                at_least_one.insert({elems.back(), true });
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
    cnf_formula at_most_one_of(list<indices_set> indices) {
        cnf_formula constraints;

        while (!indices.empty()) {
            vector<size_t> elems(indices.back().size());
            copy(indices.back().begin(), indices.back().end(), elems.begin());

            for (size_t i = 0; i < elems.size(); i++) {
                for (size_t j = i + 1; j < elems.size(); j++) {
                    constraints.push_back({{elems.at(i), false}, {elems.at(j), false }});
                }
            }

            indices.pop_back();
        }

        return constraints;
    }
}