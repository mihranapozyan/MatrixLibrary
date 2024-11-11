#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <iostream>
#include <stdexcept>
#include <random>
#include <initializer_list>

template <typename T>
class Matrix {
    std::size_t m_rows;  // Number of rows in the matrix
    std::size_t m_cols;  // Number of columns in the matrix
    std::vector<std::vector<T>> m_data;  // 2D vector to store the matrix elements

    // Helper function to check if two matrices have the same dimensions
    void checkDimensions(const Matrix<T>& other) const {
        if (m_rows != other.m_rows || m_cols != other.m_cols)
            throw std::invalid_argument("Matrix dimensions do not match.");
    }

    // Private method for printing the matrix
    void print(std::ostream& os) const;

public:
    // Constructors and Destructor
    explicit Matrix(std::size_t a_rows = 0, std::size_t a_cols = 0, bool a_random = false);  // Constructor with optional random initialization
    Matrix(std::size_t a_rows, std::size_t a_cols, T a_initVaalue);  // Constructor with custom initialization value
    Matrix(std::initializer_list<std::initializer_list<T>> a_init);  // Constructor with initializer list
    Matrix(const Matrix<T>& a_other);  // Copy constructor
    Matrix(Matrix<T>&& a_other) noexcept;  // Move constructor
    ~Matrix() noexcept = default;  // Default destructor, noexcept since we don't dynamically allocate memory

    // Operator Overloads
    Matrix<T>& operator=(const Matrix<T>& a_other);  // Copy assignment operator
    Matrix<T>& operator=(Matrix<T>&& a_other) noexcept;  // Move assignment operator
    bool operator==(const Matrix<T>& a_other) const;  // Equality operator
    bool operator!=(const Matrix<T>& a_other) const;  // Inequality operator
    Matrix<T> operator+(const Matrix<T>& a_other) const;  // Matrix addition operator
    Matrix<T> operator-(const Matrix<T>& a_other) const;  // Matrix subtraction operator
    Matrix<T> operator*(const Matrix<T>& a_other) const;  // Matrix multiplication operator

    // Access operator (for element access)
    T& operator()(std::size_t a_rows, std::size_t a_cols);
    const T& operator()(std::size_t a_rows, std::size_t a_cols) const;
    T& operator[](std::size_t a_rows);
    const T& operator[](std::size_t a_rows, std::size_t a_cols) const;
    // Input and Output stream operators
    friend std::istream& operator>>(std::istream& is, Matrix<T>& a_matrix) {
        for (std::size_t i = 0; i < a_matrix.m_rows; ++i) {
            for (std::size_t j = 0; j < a_matrix.m_cols; ++j) {
                is >> a_matrix.m_data[i][j];  // Read element by element
                if (!is) {
                    throw std::invalid_argument("Invalid input for matrix element.");
                }
            }
        }
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& a_matrix) {
        a_matrix.print(os);  // Print matrix
        return os;
    }

    // Getter methods
    [[nodiscard]] std::size_t getRows() const;  // Returns the number of rows
    [[nodiscard]] std::size_t getCols() const;  // Returns the number of columns

    // Function to calculate the determinant of a matrix
    [[nodiscard]] T determinant() const;
    // Additional functions
    //void fillRandom();  // Fills the matrix with random values
};

#endif // MATRIX_H
