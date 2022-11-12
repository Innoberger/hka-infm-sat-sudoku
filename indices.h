/**
 * This file contains methods that generate lists for
 * general sudoku patterns.
 */

#include <list>
#include "encoding.h"

/*
 * Returns the indices for each field.
 */
list<list<size_t>> field_indices(size_t order) {
    list<list<size_t>> indices;
    size_t dimension = order * order;

    // iterate over each column
    for (size_t i = 0; i < dimension; i++) {
        // iterate over each row
        for (size_t j = 0; j < dimension; j++) {
            list<size_t> field_clauses;
            // iterate over each number
            for (size_t n = 1; n <= dimension; n++) {
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
list<list<size_t>> col_indices(size_t order) {
    list<list<size_t>> indices;
    size_t dimension = order * order;

    // iterate over each number
    for (size_t n = 1; n <= dimension; n++) {
        // iterate over each column
        for (size_t i = 0; i < dimension; i++) {
            list<size_t> column_clauses;
            // iterate over each row
            for (size_t j = 0; j < dimension; j++) {
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
list<list<size_t>> row_indices(size_t order) {
    list<list<size_t>> indices;
    size_t dimension = order * order;

    // iterate over each number
    for (size_t n = 1; n <= dimension; n++) {
        // iterate over each row
        for (size_t j = 0; j < dimension; j++) {
            list<size_t> row_clauses;
            // iterate over each column
            for (size_t i = 0; i < dimension; i++) {
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
list<list<size_t>> block_indices(size_t order) {
    list<list<size_t>> indices;
    size_t dimension = order * order;

    // iterate over each number
    for (size_t n = 1; n <= dimension; n++) {
        // iterate over each block column
        for (size_t a = 0; a < order; a++) {
            // iterate over each block row
            for (size_t b = 0; b < order; b++) {
                list<size_t> block_clauses;
                // iterate over each column in a block
                for (size_t col_i = 0; col_i < order; col_i++) {
                    // iterate over each row in a block
                    for (size_t row_j = 0; row_j < order; row_j++) {
                        // construct the index for sat variable
                        size_t col_offset = a * order;
                        size_t row_offset = b * order;
                        block_clauses.push_back(encode(n, col_i + col_offset, row_j + row_offset, order));
                    }
                }
                indices.push_back(block_clauses);
            }
        }
    }

    return indices;
}