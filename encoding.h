/**
 * This file concerns the binary encoding methods
 * for general sudoku patterns.
 */

#include <iostream>

using namespace std;

struct encoding {
    unsigned int number, column, row;
};

/*
 * Returns the encoded number, column and row as a single integer.
 */
unsigned int encode(unsigned int num, unsigned int col, unsigned int row, unsigned int order) {
    unsigned int dimension = order * order;
    return ((col + row * dimension) * dimension) + num;
}

/*
 * Returns the encoded number, column and row (derived from the struct encoding) as a single integer.
 */
unsigned int encode(encoding enc, unsigned int order) {
    return encode(enc.number, enc.column, enc.row, order);
}

/*
 * Returns the decoded number, column and row of an encoded variable index.
 */
encoding decode(unsigned int encoded, unsigned int order) {
    unsigned int dimension = order * order;
    encoding enc{};

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            for (int k = 1; k <= dimension; k++) {
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
void print_formula(list<map<unsigned int, bool>> clauses, unsigned int order) {
    for (auto const &clause: clauses) {
        cout << "{";
        for (auto const &literal: clause) {
            encoding enc = decode(literal.first, order);
            cout << " [" << literal.first << "] (num:" << enc.number << ", col:" << enc.column << ", row:" << enc.row << ") = " << literal.second;
        }
        cout << " }" << endl;
    }
}

/*
 * Prints the formula in a DIMACS format.
 */
void print_dimacs(list<map<unsigned int, bool>> clauses, unsigned int order) {
    cout << "c" << endl;
    cout << "c DIMACS file to solve a Sudoku game with SAT" << endl;
    cout << "c" << endl;
    cout << "p cnf " << (order * order * order * order * order * order) << " " << clauses.size() << endl;

    for (auto const &clause: clauses) {
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
int print_sudoku(map<unsigned int, bool> solution, unsigned int order) {
    unsigned int dimension = order * order;

    cout << order << endl;

    for (unsigned int row = 0; row < dimension; row++) {
        for (unsigned col = 0; col < dimension; col++) {
            for (unsigned num = 1; num <= dimension; num++) {
                unsigned int encoded = encode(num, col, row, order);
                bool value = solution.at(encoded);

                if (value)
                    cout << num;
            }

            if (col < dimension - 1)
                cout << " ";
        }
        cout << endl;
    }

    return 0;
}