#include <iostream>
#include <list>

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

/*
 * Returns the AtMostOne clause x indices for each column.
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
                // construct the index for x
                unsigned int x_index = n * 100 + i * 10 + j;
                column_clauses.push_back(x_index);
            }
        }
        at_most_one_indices.push_back(column_clauses);
    }
}

/*
 * Returns the AtMostOne clause x indices for each row.
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
                // construct the index for x
                unsigned int x_index = n * 100 + i * 10 + j;
                row_clauses.push_back(x_index);
            }
        }
        at_most_one_indices.push_back(row_clauses);
    }
}