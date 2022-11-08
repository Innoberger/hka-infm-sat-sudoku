#include <iostream>
#include <list>

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

/*
 * Returns the AtMostOne clause sat variable indices for each column.
 */
std::list<std::list<int>> at_most_one_col_indices() {
    std::list<std::list<int>> at_most_one_indices;

    // iterate over each column
    for (unsigned int i = 0; i < 9; i++) {
        std::list<int> column_clauses;
        // iterate over each row
        for (unsigned int j = 0; j < 9; j++) {
            // iterate over each number
            for (unsigned int n = 1; n <= 9; n++) {
                // construct the index for sat variable
                unsigned int var_index = n * 100 + i * 10 + j;
                column_clauses.push_back(var_index);
            }
        }
        at_most_one_indices.push_back(column_clauses);
    }
}

/*
 * Returns the AtMostOne clause sat variable indices for each row.
 */
std::list<std::list<int>> at_most_one_row_indices() {
    std::list<std::list<int>> at_most_one_indices;

    // iterate over each row
    for (unsigned int j = 0; j < 9; j++) {
        std::list<int> row_clauses;
        // iterate over each column
        for (unsigned int i = 0; i < 9; i++) {
            // iterate over each number
            for (unsigned int n = 1; n <= 9; n++) {
                // construct the index for sat variable
                unsigned int var_index = n * 100 + i * 10 + j;
                row_clauses.push_back(var_index);
            }
        }
        at_most_one_indices.push_back(row_clauses);
    }
}

/*
 * Returns the AtMostOne clause sat variable indices for each block.
 */
std::list<std::list<int>> at_most_one_block_indices() {
    std::list<std::list<int>> at_most_one_indices;

    // iterate over each block column
    for (unsigned int a = 0; a < 3; a++) {
        // iterate over each block row
        for (unsigned int b = 0; b < 3; b++) {
            std::list<int> block_clauses;
            // iterate over each column in a block
            for (unsigned int col_i = 0; col_i < 3; col_i++) {
                // iterate over each row in a block
                for (unsigned int row_j = 0; row_j < 3; row_j++) {
                    // iterate over each number
                    for (unsigned int n = 1; n <= 9; n++) {
                        // construct the index for sat variable
                        unsigned int col_offset = a * 3;
                        unsigned int row_offset = b * 3;
                        unsigned int var_index = n * 100 + (col_i + col_offset) * 10 + (row_j + row_offset);
                        block_clauses.push_back(var_index);
                    }
                }
            }
            at_most_one_indices.push_back(block_clauses);
        }
    }
}