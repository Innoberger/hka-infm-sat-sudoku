#include <map>
#include <vector>
#include <cmath>
#include "utils.h"
#include "indices.h"
#include "constraints.h"

list<map<unsigned int, bool>> sudoku_input_assignment_clauses;
map<unsigned int, bool> sudoku_solution;
unsigned int order;

/*
 * Initializes the variable sudoku_input_assignment_clauses.
 */
int init_field() {
    int sudoku_order, dimension;
    list<string> lines;

    for (string line; getline(cin, line);)
        lines.push_back(line);

    if (lines.size() < 2) {
        cout << "error reading from stdin: expected at least 2 lines, got " << lines.size() << endl;
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
            if (elem == 0) {
                col_ctr++;
                columns.pop_front();
                continue;
            }

            // set the all (column, row) variables for that number to false,
            // except for the number that was read from input (is true by definition)
            for (unsigned int n = 1; n <= dimension; n++) {
                sudoku_input_assignment_clauses.push_back( {{ encode(n, col_ctr, lne_ctr, sudoku_order), ((unsigned int) elem) == n }});
            }

            col_ctr++;
            columns.pop_front();
        }

        lne_ctr++;
        lines.pop_front();
    }

    order = (unsigned int) sudoku_order;
    return 0;
}

/*
 * Loads the solution from any SAT solver that outputs DIMACS format in stdout.
 */
int load_solution() {
    list<string> lines;

    for (string line; getline(cin, line);)
        lines.push_back(line);

    if (lines.size() < 2) {
        cout << "error reading from stdin: expected at least 2 lines, got " << lines.size() << endl;
        return 1;
    }

    unsigned int lne_ctr = 1;

    while (!lines.empty()) {
        list<string> columns_list = tokenize(lines.front(), ' ');
        vector<string> columns_vector { begin(columns_list), end(columns_list) };

        if (columns_vector.at(0) == "s") {
            if (columns_vector.at(1) == "SATISFIABLE") {
                lne_ctr++;
                lines.pop_front();
                continue;
            } else if (columns_vector.at(1) == "UNSATISFIABLE") {
                cout << "sudoku is not satisfiable / solvable" << endl;
                return 1;
            } else {
                cout << "invalid satisfiability state '" << columns_vector.at(1) << "' in line " << lne_ctr << endl;
                return 1;
            }
        }

        if (columns_vector.at(0) != "v") {
            lne_ctr++;
            lines.pop_front();
            continue;
        }

        for (int i = 1; i < columns_vector.size(); i++) {
            int literal = stoi(columns_vector.at(i));

            if (literal == 0) {
                int order_exp_6 = abs(stoi(columns_vector.at(i - 1)));
                order = (unsigned int) round(pow(order_exp_6, (double) 1/6));
                continue;
            }

            if (literal < 0) {
                sudoku_solution.insert({ (unsigned int) abs(literal), false });
                continue;
            }

            sudoku_solution.insert({ (unsigned int) literal, true });
        }

        lne_ctr++;
        lines.pop_front();
    }

    return 0;
}

/*
 * On option '--generate-dimacs' / '-d'.
 * Reads a .sudoku file format from stdin and output corresponding dimacs to stdout.
 */
int program_generate_dimacs() {
    int init = init_field();

    if (init != 0)
        return init;

    list<list<unsigned int>> fields = field_indices(order);
    list<list<unsigned int>> cols = col_indices(order);
    list<list<unsigned int>> rows = row_indices(order);
    list<list<unsigned int>> blocks = block_indices(order);

    list<map<unsigned int, bool>> clauses = sudoku_input_assignment_clauses;

    clauses.merge(at_least_one_constraints(fields));
    clauses.merge(at_least_one_constraints(cols));
    clauses.merge(at_least_one_constraints(rows));
    clauses.merge(at_least_one_constraints(blocks));

    clauses.merge(at_most_one_constraints(fields));
    clauses.merge(at_most_one_constraints(cols));
    clauses.merge(at_most_one_constraints(rows));
    clauses.merge(at_most_one_constraints(blocks));

    print_dimacs(clauses, order);
    return 0;
}

/*
 * On option '--interpret-solution' / '-s'
 * Reads a solved sat problem from stdin and reinterprets it as .sudoku file format, writing to stdout.
 */
int program_interpret_solution() {
    int load = load_solution();

    if (load != 0)
        return load;

    print_sudoku(sudoku_solution, order);
    return 0;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "error reading program options: expected exactly one option, got " << (argc - 1) << endl;
        return 1;
    }

    if (strcmp(argv[1], "--generate-dimacs") == 0 || strcmp(argv[1], "-d") == 0)
        return program_generate_dimacs();
    else if (strcmp(argv[1], "--interpret-solution") == 0 || strcmp(argv[1], "-s") == 0)
        return program_interpret_solution();

    cout << "error reading program options: unknown option '" << argv[1] << "'" << endl;
    return 1;
}