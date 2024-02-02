#include <iostream>
#include <cstdlib> 
#include <ctime>

template <typename T>
class Matrix {
private:
    int rows;
    int cols;
    T** data;

public:
    Matrix(int rows, int cols) : rows(rows), cols(cols) {
        data = new T * [rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new T[cols];
        }
    }

    ~Matrix() {
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;
    }

    void fillFromKeyboard() {
        std::cout << "Enter matrix elements row by row:" << std::endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cin >> data[i][j];
            }
        }
    }

    void fillWithRandom() {
        srand(time(nullptr));
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] = rand() % 100;
            }
        }
    }

    Matrix operator+(const Matrix& other) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator-(const Matrix& other) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                for (int k = 0; k < cols; k++) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    Matrix operator/(const T& scalar) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] / scalar;
            }
        }
        return result;
    }

    void print() const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    int choice;
    std::cout << "Choose how to fill the matrix:" << std::endl;
    std::cout << "1. Fill matrix from keyboard" << std::endl;
    std::cout << "2. Fill matrix with random values" << std::endl;
    std::cin >> choice;

    int rows, cols;
    std::cout << "Enter number of rows and columns for the matrix: ";
    std::cin >> rows >> cols;

    Matrix<int> matrix1(rows, cols);
    Matrix<int> matrix2(rows, cols);

    switch (choice) {
    case 1:
        matrix1.fillFromKeyboard();
        matrix2.fillFromKeyboard();
        break;
    case 2:
        matrix1.fillWithRandom();
        matrix2.fillWithRandom();
        break;
    default:
        std::cout << "Invalid choice. Exiting." << std::endl;
        return 1;
    }

    std::cout << "Matrix 1:" << std::endl;
    matrix1.print();
    std::cout << std::endl;

    std::cout << "Matrix 2:" << std::endl;
    matrix2.print();
    std::cout << std::endl;

    Matrix<int> resultAddition = matrix1 + matrix2;
    std::cout << "Matrix Addition:" << std::endl;
    resultAddition.print();
    std::cout << std::endl;

    Matrix<int> resultSubtraction = matrix1 - matrix2;
    std::cout << "Matrix Subtraction:" << std::endl;
    resultSubtraction.print();
    std::cout << std::endl;

    Matrix<int> resultMultiplication = matrix1 * matrix2;
    std::cout << "Matrix Multiplication:" << std::endl;
    resultMultiplication.print();
    std::cout << std::endl;

    int scalar;
    std::cout << "Enter scalar value for division: ";
    std::cin >> scalar;
    Matrix<int> resultDivision = matrix1 / scalar;
    std::cout << "Matrix Division by Scalar:" << std::endl;
    resultDivision.print();
}
