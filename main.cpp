#include "Matrix.h"
#include <iostream>
#include <exception>

int main() {
    try {
        // --- Test 1: Matrix Construction with Initializer List ---
        std::cout << "Test 1: Constructor with initializer list" << std::endl;
        Matrix<int> mat1({
            {1, 2},
            {3, 4}
        });

        std::cout << "Matrix 1:" << std::endl;
        std::cout << mat1 << std::endl;

        // Calculate and print the determinant of mat1
        std::cout << "Determinant of Matrix 1: " << mat1.determinant() << std::endl;
        std::cout << "------------------------------------" << std::endl;

        // --- Test 2: Matrix Construction with Custom Value ---
        std::cout << "Test 2: Constructor with custom value" << std::endl;
        Matrix<int> mat2(3, 3, 5);  // 3x3 matrix filled with 5s
        std::cout << "Matrix 2:" << std::endl;
        std::cout << mat2 << std::endl;

        // Test matrix element access via operator()
        std::cout << "Element at (1, 1): " << mat2(1, 1) << std::endl;
        std::cout << "------------------------------------" << std::endl;

        // --- Test 3: Matrix Addition ---
        std::cout << "Test 3: Matrix addition" << std::endl;
        Matrix<int> mat3({
            {1, 1},
            {1, 1}
        });

        Matrix<int> mat4({
            {2, 2},
            {2, 2}
        });

        Matrix<int> result_add = mat3 + mat4;
        std::cout << "Matrix 3 + Matrix 4:" << std::endl;
        std::cout << result_add << std::endl;
        std::cout << "------------------------------------" << std::endl;

        // --- Test 4: Matrix Subtraction ---
        std::cout << "Test 4: Matrix subtraction" << std::endl;
        Matrix<int> result_sub = mat3 - mat4;
        std::cout << "Matrix 3 - Matrix 4:" << std::endl;
        std::cout << result_sub << std::endl;
        std::cout << "------------------------------------" << std::endl;

        // --- Test 5: Matrix Multiplication ---
        std::cout << "Test 5: Matrix multiplication" << std::endl;
        Matrix<int> mat5({
            {1, 2},
            {3, 4}
        });

        Matrix<int> mat6({
            {5, 6},
            {7, 8}
        });

        Matrix<int> result_mult = mat5 * mat6;
        std::cout << "Matrix 5 * Matrix 6:" << std::endl;
        std::cout << result_mult << std::endl;
        std::cout << "------------------------------------" << std::endl;

        // --- Test 6: Matrix Equality and Inequality ---
        std::cout << "Test 6: Matrix equality and inequality" << std::endl;
        Matrix<int> mat7({
            {1, 2},
            {3, 4}
        });

        std::cout << "Matrix 7 == Matrix 1? " << (mat7 == mat1 ? "True" : "False") << std::endl;
        std::cout << "Matrix 7 != Matrix 1? " << (mat7 != mat1 ? "True" : "False") << std::endl;
        std::cout << "------------------------------------" << std::endl;

        // --- Test 7: Determinant for a 3x3 matrix ---
        std::cout << "Test 7: Determinant for a 3x3 matrix" << std::endl;
        Matrix<int> mat8({
            {6, 1, 1},
            {4, -2, 5},
            {2, 8, 7}
        });

        std::cout << "Matrix 8:" << std::endl;
        std::cout << mat8 << std::endl;

        std::cout << "Determinant of Matrix 8: " << mat8.determinant() << std::endl;
        std::cout << "------------------------------------" << std::endl;

        // --- Test 8: Determinant for a 2x2 matrix ---
        std::cout << "Test 8: Determinant for a 2x2 matrix" << std::endl;
        Matrix<int> mat9({
            {1, 2},
            {3, 4}
        });

        std::cout << "Matrix 9:" << std::endl;
        std::cout << mat9 << std::endl;

        std::cout << "Determinant of Matrix 9: " << mat9.determinant() << std::endl;
        std::cout << "------------------------------------" << std::endl;

        // --- Test 9: Determinant for a Non-Square Matrix ---
        std::cout << "Test 9: Determinant for a non-square matrix (should throw an exception)" << std::endl;
        try {
            Matrix<int> mat10(2, 3);  // 2x3 matrix
            std::cout << "Matrix 10 (2x3):" << std::endl;
            std::cout << mat10 << std::endl;

            // Attempting to calculate the determinant should throw an exception
            std::cout << "Determinant of Matrix 10: " << mat10.determinant() << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
        std::cout << "------------------------------------" << std::endl;

        mat9[0][0] = 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
