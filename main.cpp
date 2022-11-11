#include <map>
#include "utils.h"
#include "indices.h"

map<unsigned int, bool> sudoku_field;

int main() {
    int sudoku_order, dimension;
    list<string> lines;

    for (string line; getline(cin, line);)
        lines.push_back(line);

    if (lines.size() < 2) {
        cout << "error reading from stdin: expected at least 2 lines" << endl;
        return 1;
    }

    sudoku_order = stoi(lines.front());
    dimension = sudoku_order * sudoku_order;
    lines.pop_front();

    if (sudoku_order < 1) {
        cout << "error reading from stdin: expected sudoku order in line 1 "
            << "to be a positive integer, got " << sudoku_order << endl;
        return 1;
    }

    if (lines.size() != dimension) {
        cout << "error reading from stdin: after order number line ("
            << sudoku_order << "), there are order * order (" << dimension
            << ") lines expected, got " << lines.size() << endl;
        return 1;
    }

    unsigned int lne_ctr = 0;

    while (!lines.empty()) {
        list<string> columns = tokenize(lines.front(), ' ');

        if (columns.size() != dimension) {
            cout << "error reading from stdin: error in line "
                << (lne_ctr + 2) << ": expected " << dimension
                << " columns separated by whitespace, got " << columns.size() << endl;
            return 1;
        }

        unsigned int col_ctr = 0;

        while (!columns.empty()) {
            int elem = stoi(columns.front());

            if (elem < 0 || elem > dimension) {
                cout << "error reading from stdin: error in line "
                    << (lne_ctr + 2) << ", column " << col_ctr
                    << ": expected integer between 0 and " << dimension
                    << ", got " << elem << endl;
                return 1;
            }

            // only prefill the start field if the input element is not 0
            if (elem == 0)
                continue;

            // set the all (column, row) variables for that number to false,
            // except for the number that was read from input (is true by definition)
            for (unsigned int n = 0; n <= dimension; n++) {
                sudoku_field.insert(pair<unsigned int, bool>(encode(n, col_ctr, lne_ctr, ceil(log2(dimension))), ((unsigned int) elem) == n));
            }

            col_ctr++;
            columns.pop_front();
        }

        lne_ctr++;
        lines.pop_front();
    }

    return 0;
}