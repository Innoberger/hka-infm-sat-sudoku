#include "utils.h"
#include "indices.h"

int main() {
    unsigned int sudoku_order, order_squared;
    list<string> lines;

    for (string line; getline(cin, line);)
        lines.push_back(line);

    if (lines.size() < 2) {
        cout << "error reading from stdin: expected at least 2 lines" << endl;
        return 1;
    }

    sudoku_order = (unsigned int) stoi(lines.front());
    order_squared = sudoku_order * sudoku_order;
    lines.pop_front();

    if (lines.size() != sudoku_order * sudoku_order) {
        cout << "error reading from stdin: after order number line ("
            << sudoku_order << "), there are order * order (" << order_squared
            << ") lines expected, got " << lines.size() << endl;
        return 1;
    }

    return 0;
}