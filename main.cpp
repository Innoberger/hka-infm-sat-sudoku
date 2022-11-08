#include <iostream>
#include <list>

/*
 * Overloads the << operator to be able to be used with std::list<int>.
 */
std::ostream &operator<<(std::ostream &os, const std::list<int> &list) {
    for (auto const &i: list) {
        os << i << std::endl;
    }
    return os;
}

/*
 * Returns the AtMostOne clause sat variable indices for each column.
 */
std::list<std::list<int>> at_most_one_col_indices() {
    std::list<std::list<int>> at_most_one_indices;

    // iterate over each number
    for (unsigned int n = 1; n <= 9; n++) {
        // iterate over each column
        for (unsigned int i = 0; i < 9; i++) {
            std::list<int> column_clauses;
            // iterate over each row
            for (unsigned int j = 0; j < 9; j++) {
                // construct the index for sat variable
                unsigned int var_index = n * 100 + i * 10 + j;
                column_clauses.push_back(var_index);
            }
            at_most_one_indices.push_back(column_clauses);
        }
    }

    return at_most_one_indices;
}

/*
 * Returns the AtMostOne clause sat variable indices for each row.
 */
std::list<std::list<int>> at_most_one_row_indices() {
    std::list<std::list<int>> at_most_one_indices;

    // iterate over each number
    for (unsigned int n = 1; n <= 9; n++) {
        // iterate over each row
        for (unsigned int j = 0; j < 9; j++) {
            std::list<int> row_clauses;
            // iterate over each column
            for (unsigned int i = 0; i < 9; i++) {
                // construct the index for sat variable
                unsigned int var_index = n * 100 + i * 10 + j;
                row_clauses.push_back(var_index);
            }
            at_most_one_indices.push_back(row_clauses);
        }
    }

    return at_most_one_indices;
}

/*
 * Returns the AtMostOne clause sat variable indices for each block.
 */
std::list<std::list<int>> at_most_one_block_indices() {
    std::list<std::list<int>> at_most_one_indices;

    // iterate over each number
    for (unsigned int n = 1; n <= 9; n++) {
        // iterate over each block column
        for (unsigned int a = 0; a < 3; a++) {
            // iterate over each block row
            for (unsigned int b = 0; b < 3; b++) {
                std::list<int> block_clauses;
                // iterate over each column in a block
                for (unsigned int col_i = 0; col_i < 3; col_i++) {
                    // iterate over each row in a block
                    for (unsigned int row_j = 0; row_j < 3; row_j++) {
                        // construct the index for sat variable
                        unsigned int col_offset = a * 3;
                        unsigned int row_offset = b * 3;
                        unsigned int var_index = n * 100 + (col_i + col_offset) * 10 + (row_j + row_offset);
                        block_clauses.push_back(var_index);
                    }
                }
                at_most_one_indices.push_back(block_clauses);
            }
        }
    }

    return at_most_one_indices;
}

int main() {
    std::list<std::list<int>> list = at_most_one_block_indices();
    std::cout << list.front();
    std::cout << "---" << std::endl;
    std::cout << list.back();
    return 0;
}