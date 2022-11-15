#include <map>
#include <vector>
#include <cmath>
#include "utils.h"
#include "indices.h"
#include "constraints.h"

/*
 * Initializes the variable input_formula.
 */
int init_field(size_t& order, cnf_formula& input_formula) {
    size_t dimension;
    list<string> lines;

    for (string line; getline(cin, line);)
        lines.push_back(line);

    if (lines.size() < 2) {
        cout << "error reading from stdin: expected at least 2 lines, got " << lines.size() << endl;
        return 1;
    }

    order = stoi(lines.front());
    dimension = order * order;
    lines.pop_front();

    if (order < 1) {
        cout << "error reading from stdin: expected sudoku order in line 1 "
             << "to be a positive integer, got " << order << endl;
        return 1;
    }

    if (lines.size() != dimension) {
        cout << "error reading from stdin: after order number line ("
             << order << "), there are order * order (" << dimension
             << ") lines expected, got " << lines.size() << endl;
        return 1;
    }

    size_t lne_ctr = 0;

    while (!lines.empty()) {
        list<string> columns = utils::tokenize(lines.front(), ' ');

        if (columns.size() != dimension) {
            cout << "error reading from stdin: error in line "
                 << (lne_ctr + 2) << ": expected " << dimension
                 << " columns separated by whitespace, got " << columns.size() << endl;
            return 1;
        }

        size_t col_ctr = 0;

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
            for (size_t n = 1; n <= dimension; n++) {
                input_formula.push_back( {{ encoding::encode(n, col_ctr, lne_ctr, order), ((size_t) elem) == n }});
            }

            col_ctr++;
            columns.pop_front();
        }

        lne_ctr++;
        lines.pop_front();
    }

    order = (size_t) order;
    return 0;
}

/*
 * Loads the solution from any SAT solver that outputs DIMACS format in stdout.
 */
int load_solution(size_t& order, var_assignment& solution) {
    list<string> lines;

    for (string line; getline(cin, line);)
        lines.push_back(line);

    if (lines.size() < 2) {
        cout << "error reading from stdin: expected at least 2 lines, got " << lines.size() << endl;
        return 1;
    }

    size_t lne_ctr = 1;

    while (!lines.empty()) {
        list<string> columns_list = utils::tokenize(lines.front(), ' ');
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

        for (size_t i = 1; i < columns_vector.size(); i++) {
            int literal = stoi(columns_vector.at(i));

            if (literal == 0)
                break;

            if (literal < 0) {
                solution.insert({ (size_t) abs(literal), false });
                continue;
            }

            solution.insert({ (size_t) literal, true });
        }

        lne_ctr++;
        lines.pop_front();
    }

    order = (size_t) round(pow(solution.size(), (double) 1/6));
    return 0;
}

/*
 * On option '--generate-dimacs' / '-d'.
 * Reads a .sudoku file format from stdin and output corresponding dimacs to stdout.
 */
int program_generate_dimacs() {
    size_t order;
    cnf_formula formula;
    int init = init_field(order, formula);

    if (init != 0)
        return init;

    formula.merge(constraints::exactly_one_of(indices::of_fields(order)));
    formula.merge(constraints::exactly_one_of(indices::of_columns(order)));
    formula.merge(constraints::exactly_one_of(indices::of_rows(order)));
    formula.merge(constraints::exactly_one_of(indices::of_blocks(order)));

    encoding::print_dimacs(formula, order);
    return 0;
}

/*
 * On option '--interpret-solution' / '-s'
 * Reads a solved sat problem from stdin and reinterprets it as .sudoku file format, writing to stdout.
 */
int program_interpret_solution() {
    size_t order;
    var_assignment solution;
    int load = load_solution(order, solution);

    if (load != 0)
        return load;

    encoding::print_sudoku(solution, order);
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