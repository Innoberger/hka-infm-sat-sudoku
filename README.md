# hka-infm-sat-sudoku
Exercise 2 "Sudoku" for sheet 1 in course "Practical SAT Solving" at Hochschule Karlsruhe

This is a Sudoku solver using SAT solving methods.

Compile with `cmake CMakeLists.txt && make`. This will create an executable such as `hka_infm_sat_sudoku`.

The application will read [.sudoku files](https://baldur.iti.kit.edu/sat/files/sudokus.zip) from stdin. To execute, run `cat file.sudoku | ./hka_infm_sat_sudoku`.