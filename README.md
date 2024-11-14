# Matrix Class Library

A simple C++ Matrix class that supports various matrix operations including addition, subtraction, multiplication, and calculation of the determinant. This project demonstrates the use of object-oriented programming principles to implement a custom matrix class.

## Features
- **Matrix Construction**: Supports construction using initializer lists, custom values, and random initialization.
- **Matrix Operations**: Supports addition (`+`), subtraction (`-`), multiplication (`*`), and equality (`==`, `!=`).
- **Determinant Calculation**: Calculates the determinant of a square matrix.
- **Element Access**: Access elements using `operator()` and print the matrix with `operator<<`.
- **Error Handling**: Handles errors such as mismatched matrix dimensions and attempts to calculate the determinant of non-square matrices.

## Files
- **Matrix.h**: Header file containing the Matrix class definition.
- **main.cpp**: Test file containing various test cases to verify the functionality of the Matrix class.

## Installation

To use this library, simply include the `Matrix.h` file in your C++ project.

```cpp
#include "Matrix.h"
