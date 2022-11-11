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
 * Returns the bit sequence of a decimal number as a string.
 */
string dec_to_bin(unsigned int num) {
    string result;
    while (num != 0) {
        if (num % 2)
            result.append(1, '1');
        else
            result.append(1, '0');
        num /= 2;
    }
    reverse(result.begin(), result.end());
    return result;
}

/*
 * Returns the decimal number of a bit sequence.
 */
unsigned int bin_to_dec(const string& num) {
    return stoi(num, nullptr, 2);
}

/*
 * Returns a string filled up with chars.
 */
string pad_left(string source, unsigned int totalWidth, char paddingChar = ' ') {
    if (totalWidth > source.size())
        source.insert(0, totalWidth - source.size(), paddingChar);

    return source;
}

/*
 * Returns the binary encoded number, column and row as a single integer.
 */
unsigned int encode(unsigned int n, unsigned int i, unsigned int j, unsigned int bits) {
    string num_binary = pad_left(dec_to_bin(n), bits, '0');
    string col_binary = pad_left(dec_to_bin(i), bits, '0');
    string row_binary = pad_left(dec_to_bin(j), bits, '0');

    string combined_binary = num_binary.append(col_binary).append(row_binary);

    return bin_to_dec(combined_binary);
}

/*
 * Returns the binary encoded number, column and row (derived from the struct encoding) as a single integer.
 */
unsigned int encode(encoding enc, unsigned int bits) {
    return encode(enc.number, enc.column, enc.row, bits);
}

/*
 * Returns the decoded number, column and row of an encoded variable index.
 */
encoding decode(unsigned int encoded, unsigned int order) {
    unsigned int dimension = order * order;
    unsigned int bits = ceil(log2(dimension));
    encoding enc{};

    string encoded_binary = pad_left(dec_to_bin(encoded), 3 * bits, '0');

    enc.number = bin_to_dec(encoded_binary.substr(0, bits));
    enc.column = bin_to_dec(encoded_binary.substr(bits, bits));
    enc.row = bin_to_dec(encoded_binary.substr(bits * 2, bits));

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
            cout << " (num:" << enc.number << ", col:" << enc.column << ", row:" << enc.row << ") = " << literal.second;
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

            if (literal.second)
                var *= -1;

            cout << var << " ";
        }
        cout << "0" << endl;
    }
}