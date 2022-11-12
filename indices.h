/**
 * This file contains methods that generate lists for
 * general sudoku patterns.
 */

#include <list>
#include "encoding.h"

/*
 * Returns the indices for each field.
 */
list<list<unsigned int>> field_indices(unsigned int order) {
    list<list<unsigned int>> indices;
    unsigned int dimension = order * order;

    // iterate over each column
    for (unsigned int i = 0; i < dimension; i++) {
        // iterate over each row
        for (unsigned int j = 0; j < dimension; j++) {
            list<unsigned int> field_clauses;
            // iterate over each number
            for (unsigned int n = 1; n <= dimension; n++) {
                field_clauses.push_back(encode(n, i, j, order));
            }
            indices.push_back(field_clauses);
        }
    }

    return indices;
}

/*
 * Returns the indices for each column.
 */
list<list<unsigned int>> col_indices(unsigned int order) {
    list<list<unsigned int>> indices;
    unsigned int dimension = order * order;

    // iterate over each number
    for (unsigned int n = 1; n <= dimension; n++) {
        // iterate over each column
        for (unsigned int i = 0; i < dimension; i++) {
            list<unsigned int> column_clauses;
            // iterate over each row
            for (unsigned int j = 0; j < dimension; j++) {
                column_clauses.push_back(encode(n, i, j, order));
            }
            indices.push_back(column_clauses);
        }
    }

    return indices;
}

/*
 * Returns the indices for each row.
 */
list<list<unsigned int>> row_indices(unsigned int order) {
    list<list<unsigned int>> indices;
    unsigned int dimension = order * order;

    // iterate over each number
    for (unsigned int n = 1; n <= dimension; n++) {
        // iterate over each row
        for (unsigned int j = 0; j < dimension; j++) {
            list<unsigned int> row_clauses;
            // iterate over each column
            for (unsigned int i = 0; i < dimension; i++) {
                row_clauses.push_back(encode(n, i, j, order));
            }
            indices.push_back(row_clauses);
        }
    }
    return indices;
}

/*
 * Returns the indices for each block.
 */
list<list<unsigned int>> block_indices(unsigned int order) {
    list<list<unsigned int>> indices;
    unsigned int dimension = order * order;

    // iterate over each number
    for (unsigned int n = 1; n <= dimension; n++) {
        // iterate over each block column
        for (unsigned int a = 0; a < order; a++) {
            // iterate over each block row
            for (unsigned int b = 0; b < order; b++) {
                list<unsigned int> block_clauses;
                // iterate over each column in a block
                for (unsigned int col_i = 0; col_i < order; col_i++) {
                    // iterate over each row in a block
                    for (unsigned int row_j = 0; row_j < order; row_j++) {
                        // construct the index for sat variable
                        unsigned int col_offset = a * order;
                        unsigned int row_offset = b * order;
                        block_clauses.push_back(encode(n, col_i + col_offset, row_j + row_offset, order));
                    }
                }
                indices.push_back(block_clauses);
            }
        }
    }

    return indices;
}