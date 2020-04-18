# vs_sudoku
A program that reads a puzzle in text format and manages the truth table as the puzzle is solved.

The program requests an input file and expects to find 9 rows of digits where '0' is an unknown to be determined by
normal Sudoku logic.  The program uses fairly sophisticated logic to create a truth table.  It will not permit a
value to be entered into the puzzle that is not logically correct.  However, it does allow for a guess, using the 'g'
command, and will determine when the information in the puzzle becomes logically inconsistent.  At this point, it
can update its truth table and allow for the puzzle to be returned to its pre-guess position with an updated truth
table, which allows for a valid move to be made.  The program was written using Visual Studio C++, but lacks the
visual interface.  It is possible to save the current position in a new text file to be continued later.
