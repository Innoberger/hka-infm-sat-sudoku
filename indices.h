/**
 * This file contains methods that generate lists for
 * general sudoku patterns.
 */

#include <list>
#include "encoding.h"

using indices_set = list<size_t>;

namespace indices {
    /*
     * Returns the indices for each field.
     */
    list<indices_set> of_fields(size_t &order) {
        list<indices_set> indices;
        size_t dimension = order * order;

        // iterate over each column
        for (size_t i = 0; i < dimension; i++) {
            // iterate over each row
            for (size_t j = 0; j < dimension; j++) {
                indices_set field_indices;
                // iterate over each number
                for (size_t n = 1; n <= dimension; n++) {
                    field_indices.push_back(encoding::encode(n, i, j, order));
                }
                indices.push_back(field_indices);
            }
        }

        return indices;
    }

    /*
     * Returns the indices for each column.
     */
    list<indices_set> of_columns(size_t &order) {
        list<indices_set> indices;
        size_t dimension = order * order;

        // iterate over each number
        for (size_t n = 1; n <= dimension; n++) {
            // iterate over each column
            for (size_t i = 0; i < dimension; i++) {
                indices_set column_indices;
                // iterate over each row
                for (size_t j = 0; j < dimension; j++) {
                    column_indices.push_back(encoding::encode(n, i, j, order));
                }
                indices.push_back(column_indices);
            }
        }

        return indices;
    }

    /*
     * Returns the indices for each row.
     */
    list<indices_set> of_rows(size_t &order) {
        list<indices_set> indices;
        size_t dimension = order * order;

        // iterate over each number
        for (size_t n = 1; n <= dimension; n++) {
            // iterate over each row
            for (size_t j = 0; j < dimension; j++) {
                indices_set row_indices;
                // iterate over each column
                for (size_t i = 0; i < dimension; i++) {
                    row_indices.push_back(encoding::encode(n, i, j, order));
                }
                indices.push_back(row_indices);
            }
        }
        return indices;
    }

    /*
     * Returns the indices for each block.
     */
    list<indices_set> of_blocks(size_t &order) {
        list<indices_set> indices;
        size_t dimension = order * order;

        // iterate over each number
        for (size_t n = 1; n <= dimension; n++) {
            // iterate over each block column
            for (size_t a = 0; a < order; a++) {
                // iterate over each block row
                for (size_t b = 0; b < order; b++) {
                    indices_set block_indices;
                    // iterate over each column in a block
                    for (size_t col_i = 0; col_i < order; col_i++) {
                        // iterate over each row in a block
                        for (size_t row_j = 0; row_j < order; row_j++) {
                            // construct the index for sat variable
                            size_t col_offset = a * order;
                            size_t row_offset = b * order;
                            block_indices.push_back(encoding::encode(n, col_i + col_offset, row_j + row_offset, order));
                        }
                    }
                    indices.push_back(block_indices);
                }
            }
        }

        return indices;
    }
}