#include <iostream>
#include <vector>
using namespace std;

#define MOD 2

typedef vector<vector<int>> Matrix;

Matrix multiply(const Matrix &A, const Matrix &B) {
    int n = A.size();
    Matrix result(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                result[i][j] ^= (A[i][k] & B[k][j]);  
            }
        }
    }
    return result;
}

Matrix matrixExpo(Matrix A, int n) {
    int size = A.size();
    Matrix result(size, vector<int>(size, 0));

    for (int i = 0; i < size; i++) result[i][i] = 1;

    while (n > 0) {
        if (n % 2 == 1) {
            result = multiply(result, A); 
        }
        A = multiply(A, A); 
        n /= 2;             
    }
    return result;
}

void printMatrix(const Matrix &mat) {
    for (const auto &row : mat) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main() {
    int n, power;
    cout << "Enter matrix size: ";
    cin >> n;

    Matrix A(n, vector<int>(n));
    cout << "Enter matrix elements (0 or 1 only):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }

    cout << "Enter the power to raise the matrix: ";
    cin >> power;

    Matrix result = matrixExpo(A, power);

    cout << "Resultant Matrix A^" << power << ":\n";
    printMatrix(result);

    return 0;
}
