/**
 * This file concerns the binary encoding methods
 * for general sudoku patterns.
 */

#include <iostream>

using namespace std;

using var_assignment = map<size_t, bool>;
using clauses = map<size_t, bool>;
using cnf_formula = list<clauses>;

namespace encoding {
    struct encoding {
        size_t number, column, row;
    };

    /*
     * Returns the encoded number, column and row as a single integer.
     */
    size_t encode(size_t num, size_t col, size_t row, size_t &order) {
        size_t dimension = order * order;
        return ((col + row * dimension) * dimension) + num;
    }

    /*
     * Returns the encoded number, column and row (derived from the struct encoding) as a single integer.
     */
    size_t encode(encoding enc, size_t &order) {
        return encode(enc.number, enc.column, enc.row, order);
    }

    /*
     * Returns the decoded number, column and row of an encoded variable index.
     */
    encoding decode(size_t encoded, size_t &order) {
        size_t dimension = order * order;
        encoding enc{};

        for (size_t i = 0; i < dimension; i++) {
            for (size_t j = 0; j < dimension; j++) {
                for (size_t k = 1; k <= dimension; k++) {
                    if (encode(k, i, j, order) != encoded)
                        continue;

                    enc.number = k;
                    enc.column = i;
                    enc.row = j;
                    return enc;
                }
            }
        }

        return enc;
    }

    /*
     * Prints the formula in a human-readable format.
     */
    void print_formula(cnf_formula &formula, size_t &order) {
        for (auto const &clause: formula) {
            cout << "{";
            for (auto const &literal: clause) {
                encoding enc = decode(literal.first, order);
                cout << " [" << literal.first << "] (num:" << enc.number << ", col:" << enc.column << ", row:"
                     << enc.row << ") = " << literal.second;
            }
            cout << " }" << endl;
        }
    }

    /*
     * Prints the formula in a DIMACS format.
     */
    void print_dimacs(cnf_formula &formula, size_t &order) {
        cout << "c" << endl;
        cout << "c DIMACS file to solve a Sudoku game with SAT" << endl;
        cout << "c" << endl;
        cout << "p cnf " << (order * order * order * order * order * order) << " " << formula.size() << endl;

        for (auto const &clause: formula) {
            for (auto const &literal: clause) {
                int var = literal.first;

                if (!literal.second)
                    var *= -1;

                cout << var << " ";
            }
            cout << "0" << endl;
        }
    }

    /*
     * Prints the formula in a SUDOKU format.
     */
    void print_sudoku(var_assignment &solution, size_t &order) {
        size_t dimension = order * order;

        cout << order << endl;

        for (size_t row = 0; row < dimension; row++) {
            for (size_t col = 0; col < dimension; col++) {
                for (size_t num = 1; num <= dimension; num++) {
                    size_t encoded = encode(num, col, row, order);
                    bool value = solution.at(encoded);

                    if (value)
                        cout << num;
                }

                if (col < dimension - 1)
                    cout << " ";
            }
            cout << endl;
        }
    }
}