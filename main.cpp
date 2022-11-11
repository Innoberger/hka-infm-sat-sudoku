#include "utils.h"
#include "indices.h"

int main() {
    int sudoku_order, order_squared;
    list<string> lines;

    for (string line; getline(cin, line);)
        lines.push_back(line);

    if (lines.size() < 2) {
        cout << "error reading from stdin: expected at least 2 lines" << endl;
        return 1;
    }

    sudoku_order = stoi(lines.front());
    order_squared = sudoku_order * sudoku_order;
    lines.pop_front();

    if (sudoku_order < 1) {
        cout << "error reading from stdin: expected sudoku order in line 1 "
            << "to be a positive integer, got " << sudoku_order << endl;
        return 1;
    }

    if (lines.size() != order_squared) {
        cout << "error reading from stdin: after order number line ("
            << sudoku_order << "), there are order * order (" << order_squared
            << ") lines expected, got " << lines.size() << endl;
        return 1;
    }

    unsigned int lne_ctr = 0;

    while (!lines.empty()) {
        list<string> columns = tokenize(lines.front(), ' ');

        if (columns.size() != order_squared) {
            cout << "error reading from stdin: error in line "
                << (lne_ctr + 2) << ": expected " << order_squared
                << " columns separated by whitespace, got " << columns.size() << endl;
            return 1;
        }

        unsigned int col_ctr = 0;

        while (!columns.empty()) {
            int elem = stoi(columns.front());

            if (elem < 0 || elem > order_squared) {
                cout << "error reading from stdin: error in line "
                    << (lne_ctr + 2) << ", column " << col_ctr
                    << ": expected integer between 0 and " << order_squared
                    << ", got " << elem << endl;
                return 1;
            }

            /**
             * TODO:
             * assignment of bolean variables for SAT solving goes HERE
             */

            col_ctr++;
            columns.pop_front();
        }

        lne_ctr++;
        lines.pop_front();
    }

    return 0;
}