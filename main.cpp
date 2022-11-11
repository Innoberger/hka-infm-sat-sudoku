#include "utils.h"
#include "indices.h"

int main() {
    unsigned int sudoku_order = 3;
    list<list<unsigned int>> list = col_indices(sudoku_order);
    cout << list.front();
    cout << "---" << endl;
    cout << list.back();
    cout << decode(2440, sudoku_order).number << endl;
    return 0;
}