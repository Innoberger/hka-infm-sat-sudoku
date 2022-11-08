#include <iostream>
#include <list>
#include <math.h>

struct encoding {
    unsigned int number, column, row;
};

/*
 * Overloads the << operator to be able to be used with std::list<unsigned int>.
 */
std::ostream &operator<<(std::ostream &os, const std::list<unsigned int> &list) {
    for (auto const &i: list) {
        os << i << std::endl;
    }
    return os;
}

/*
 * Returns the bit sequence of a decimal number as std::string.
 */
std::string dec_to_bin(unsigned int num) {
    std::string result;
    while (num != 0) {
        if (num % 2)
            result.append(1, '1');
        else
            result.append(1, '0');
        num /= 2;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

/*
 * Returns the decimal number of a bit sequence.
 */
unsigned int bin_to_dec(std::string num) {
    return std::stoi(num, 0, 2);
}

/*
 * Returns a string filled up with chars.
 */
std::string pad_left(std::string source, unsigned int totalWidth, char paddingChar = ' ') {
    if (totalWidth > source.size())
        source.insert(0, totalWidth - source.size(), paddingChar);

    return source;
}

/*
 * Returns the binary encoded number, column and row as a single integer.
 */
unsigned int encode(unsigned int n, unsigned int i, unsigned int j, unsigned int bits) {
    std::string num_binary = pad_left(dec_to_bin(n), bits, '0');
    std::string col_binary = pad_left(dec_to_bin(i), bits, '0');
    std::string row_binary = pad_left(dec_to_bin(j), bits, '0');

    std::string combined_binary = num_binary.append(col_binary).append(row_binary);

    return bin_to_dec(combined_binary);
}

/*
 * Returns the decoded number, column and row of an encoded variable index.
 */
encoding decode(unsigned int encoded, unsigned int order) {
    unsigned int dimension = order * order;
    unsigned int bits = ceil(log2(dimension));
    encoding enc;

    std::string encoded_binary = pad_left(dec_to_bin(encoded), 3 * bits, '0');

    enc.number = bin_to_dec(encoded_binary.substr(0, bits));
    enc.column = bin_to_dec(encoded_binary.substr(bits, bits));
    enc.row = bin_to_dec(encoded_binary.substr(bits * 2, bits));

    return enc;
}

/*
 * Returns the indices for each column.
 */
std::list<std::list<unsigned int>> col_indices(unsigned int order) {
    std::list<std::list<unsigned int>> at_most_one_indices;
    unsigned int dimension = order * order;
    unsigned int bits = ceil(log2(dimension));

    // iterate over each number
    for (unsigned int n = 1; n <= dimension; n++) {
        // iterate over each column
        for (unsigned int i = 0; i < dimension; i++) {
            std::list<unsigned int> column_clauses;
            // iterate over each row
            for (unsigned int j = 0; j < dimension; j++) {
                column_clauses.push_back(encode(n, i, j, bits));
            }
            at_most_one_indices.push_back(column_clauses);
        }
    }

    return at_most_one_indices;
}

/*
 * Returns the indices for each row.
 */
std::list<std::list<unsigned int>> row_indices(unsigned int order) {
    std::list<std::list<unsigned int>> at_most_one_indices;
    unsigned int dimension = order * order;
    unsigned int bits = ceil(log2(dimension));

    // iterate over each number
    for (unsigned int n = 1; n <= dimension; n++) {
        // iterate over each row
        for (unsigned int j = 0; j < dimension; j++) {
            std::list<unsigned int> row_clauses;
            // iterate over each column
            for (unsigned int i = 0; i < dimension; i++) {
                row_clauses.push_back(encode(n, i, j, bits));
            }
            at_most_one_indices.push_back(row_clauses);
        }
    }

    return at_most_one_indices;
}

/*
 * Returns the indices for each block.
 */
std::list<std::list<unsigned int>> block_indices(unsigned int order) {
    std::list<std::list<unsigned int>> at_most_one_indices;
    unsigned int dimension = order * order;
    unsigned int bits = ceil(log2(dimension));

    // iterate over each number
    for (unsigned int n = 1; n <= dimension; n++) {
        // iterate over each block column
        for (unsigned int a = 0; a < order; a++) {
            // iterate over each block row
            for (unsigned int b = 0; b < order; b++) {
                std::list<unsigned int> block_clauses;
                // iterate over each column in a block
                for (unsigned int col_i = 0; col_i < order; col_i++) {
                    // iterate over each row in a block
                    for (unsigned int row_j = 0; row_j < order; row_j++) {
                        // construct the index for sat variable
                        unsigned int col_offset = a * order;
                        unsigned int row_offset = b * order;
                        block_clauses.push_back(encode(n, col_i + col_offset, row_j + row_offset, bits));
                    }
                }
                at_most_one_indices.push_back(block_clauses);
            }
        }
    }

    return at_most_one_indices;
}

int main() {
    unsigned int sudoku_order = 3;
    std::list<std::list<unsigned int>> list = col_indices(sudoku_order);
    std::cout << list.front();
    std::cout << "---" << std::endl;
    std::cout << list.back();
    std::cout << decode(2440, sudoku_order).number << std::endl;
    return 0;
}