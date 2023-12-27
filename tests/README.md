# Automated Testing Program - User Guide

## test.sh [directory [result.csv]]

- **directory:** Indicates the directory where the test configuration files are located.
- **result.csv:** Specifies a file where test results will be appended.

If no arguments are provided, the script will operate on the current directory.

### Configuration Files:
- **run:** A text file specifying the command line to execute (mandatory).
- **std.in:** A text file indicating simulated keyboard input (optional).
- **std.out:** A text file indicating the expected output (optional/validation*).
- **stderr.out:** A text file indicating the expected error output (optional/validation*).
- **description:** A text file providing a description of the test (optional).
- **returncode:** A text file containing the expected integer return code (optional/validation*).
- **\*.outfile:** One or more files to be produced by the program (optional/validation*).
  - If the file is named example.txt.outfile, it will be compared to example.txt.

*Validation indicates that the script will test compliance. If compliance is not met, it will be indicated.

## mktest.sh

A file to be customized. In its current state, it attempts to validate all tests
contained in directories whose names start with "Test".
