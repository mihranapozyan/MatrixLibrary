#include "Matrix.h"

#include <iomanip>
#include <iostream>
#include <string>
#include <ostream>
#include <random>


template<typename T>
Matrix<T>::Matrix(const std::size_t a_rows, const std::size_t a_cols, const bool a_rand)
    : m_rows(a_rows), m_cols(a_cols), m_data(a_rows, std::vector<T>(a_cols, 0)) {

    if(a_rand) {
        // Use random_device to initialise the random number generator
        std::random_device rd;
        std::mt19937 gen(rd()); // Random number generator (Mersenne Twister)

        // Random number range [0, 100]
        std::uniform_int_distribution<int> dis(0, 100);

        for (auto &row : m_data)
            for (auto &elem : row)
                elem = dis(gen);
    }
}

template <typename T>
Matrix<T>::Matrix(std::size_t a_rows, std::size_t a_cols, T a_initVaalue)
    : m_rows(a_rows), m_cols(a_cols), m_data(a_rows, std::vector<T>(a_cols, a_initVaalue)) {}

template <typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> a_init)
    : m_rows(a_init.size()), m_cols(a_init.begin()->size()), m_data() {
    // Ensure that all rows have the same number of elements
    for (const auto& row : a_init) {
        if (row.size() != m_cols) {
            throw std::invalid_argument("All rows must have the same number of elements.");
        }
    }

    // Now initialize m_data from the initializer_list
    m_data.reserve(m_rows);  // Reserve memory for the number of rows
    for (const auto& row : a_init) {
        m_data.push_back(std::vector<T>(row));  // Copy each row into m_data
    }
}

template<typename T>
Matrix<T>::Matrix(const Matrix &a_other) : m_rows(a_other.m_rows), m_cols(a_other.m_cols), m_data(a_other.m_data) {}

template <typename T>
Matrix<T>::Matrix(Matrix<T>&& a_other) noexcept
    : m_rows(a_other.m_rows), m_cols(a_other.m_cols), m_data(std::move(a_other.m_data)) {
    // Move constructor - transfers the resources of the 'other' matrix
    // 'other' is left in a valid, empty state
    a_other.m_rows = 0;
    a_other.m_cols = 0;
}

// Operators overloading
template<typename T>
bool Matrix<T>::operator==(const Matrix &a_other) const {
    // Checks if two matrices are equal by comparing their rows, columns, and data
    return m_rows == a_other.m_rows && m_cols == a_other.m_cols && m_data == a_other.m_data;
}

template<typename T>
bool Matrix<T>::operator!=(const Matrix &a_other) const {
    // Checks if two matrices are not equal by negating the equality check
    return !(*this == a_other);
}

template<typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix &a_other) {
    if (this != &a_other) {
        m_rows = a_other.m_rows;
        m_cols = a_other.m_cols;
        m_data = a_other.m_data;
    }
    return *this;
}

template<typename T>
Matrix<T> & Matrix<T>::operator=(Matrix&& a_other) noexcept {
    if (this != &a_other) {
        m_rows = a_other.m_rows;
        m_cols = a_other.m_cols;
        m_data = std::move(a_other.m_data);
    }
    return *this;
}

template<typename T>
T &Matrix<T>::operator()(std::size_t a_rows, std::size_t a_cols) {
    // Accessor for modifying an element in the matrix
    return m_data[a_rows][a_cols];
}

template<typename T>
const T &Matrix<T>::operator()(std::size_t a_rows, std::size_t a_cols) const {
    // Const accessor for reading an element in the matrix
    return m_data[a_rows][a_cols];
}

template<typename T>
T &Matrix<T>::operator[](std::size_t a_rows, std::size_t a_cols) {
    // Accessor for modifying an element in the matrix
    return m_data[a_rows][a_cols];
}

template<typename T>
const T &Matrix<T>::operator[](std::size_t a_rows, std::size_t a_cols) const {
    // Const accessor for reading an element in the matrix
    return m_data[a_rows][a_cols];
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix &a_other) const {
    // Matrix addition: check if dimensions match, then perform element-wise addition
    checkDimensions(a_other);
    Matrix result(m_rows, a_other.m_cols, false);
    for (size_t i = 0; i < m_rows; ++i) {
        for (size_t j = 0; j < m_cols; ++j) {
            result(i, j) = (*this)(i, j) + a_other(i, j);
        }
    }
    return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix &a_other) const {
    // Matrix subtraction: check if dimensions match, then perform element-wise subtraction
    checkDimensions(a_other);
    Matrix result(m_rows, a_other.m_cols, false);
    for (size_t i = 0; i < m_rows; ++i) {
        for (size_t j = 0; j < m_cols; ++j) {
            result(i, j) = (*this)(i, j) - a_other(i, j);
        }
    }
    return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix &a_other) const {
    // Matrix multiplication: check if the number of columns of the first matrix
    // matches the number of rows of the second matrix
    if (m_cols != a_other.m_rows)
        throw std::invalid_argument("The number of columns of the first matrix must be equal to the number of rows of the second matrix.");
    Matrix result(m_rows, a_other.m_cols, false);
    for (size_t i = 0; i < m_rows; ++i) {
        for (size_t j = 0; j < a_other.m_cols; ++j) {
            result.m_data[i][j] = 0;
            for (size_t k = 0; k < m_cols; ++k)
                result.m_data[i][j] += (*this)(i, k) * a_other(k, j);
        }
    }
    return result;
}

// Functions
template<typename T>
std::size_t Matrix<T>::getRows() const {
    return m_rows; // Return the number of rows
}

template<typename T>
std::size_t Matrix<T>::getCols() const {
    return m_cols; // Return the number of columns
}

template<typename T>
void Matrix<T>::print(std::ostream& os) const {
    // Print the matrix row by row
    for (std::size_t i = 0; i < m_rows; i++) {
        std::cout << "|";
        for (std::size_t j = 0; j < m_cols; j++)
            os << std::setw(4) << m_data[i][j] << " ";
        os << std::setw(4) << "|\n"; // Newline after each row
    }
}

// Method to compute the determinant of the matrix
template<typename T>
T Matrix<T>::determinant() const {
    // Check if the matrix is square (determinant is only defined for square matrices)
    if (m_rows != m_cols)
        throw std::invalid_argument("Determinant can only be calculated for square matrices.");
    Matrix<T> lt_matrix = *this;  // Create a copy of the matrix to work with
    T det = 1;
    // Transform the matrix to upper triangular form
    for (std::size_t i = 0; i < lt_matrix.m_rows; ++i) {
        // If the diagonal element is 0, try to swap with a non-zero row below it
        if (lt_matrix.m_data[i][i] == 0) {
            bool swapped = false;
            for (std::size_t j = i + 1; j < lt_matrix.m_rows; ++j) {
                if (lt_matrix.m_data[j][i] != 0) {
                    std::swap(lt_matrix.m_data[i], lt_matrix.m_data[j]);  // Swap rows
                    det *= -1;  // Change the sign of the determinant when rows are swapped
                    swapped = true;
                    break;
                }
            }
            if (!swapped) {
                return 0;  // If no row is found to swap, the determinant is 0
            }
        }
        // Eliminate the elements below the diagonal (Gaussian elimination)
        for (std::size_t j = i + 1; j < lt_matrix.m_rows; ++j) {
            T factor = lt_matrix.m_data[j][i] / lt_matrix.m_data[i][i];
            for (std::size_t k = i; k < lt_matrix.m_cols; ++k) {
                lt_matrix.m_data[j][k] -= lt_matrix.m_data[i][k] * factor;
            }
        }
    }
    // The determinant is the product of the diagonal elements of the upper triangular matrix
    for (std::size_t i = 0; i < lt_matrix.m_rows; ++i) {
        det *= lt_matrix.m_data[i][i];
    }
    return det;  // Return the determinant value
}


template class Matrix<int>;
template class Matrix<double>;
template class Matrix<float>;



