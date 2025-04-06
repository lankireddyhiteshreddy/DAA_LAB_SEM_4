#include <bits/stdc++.h>
using namespace std;

void printMatrix(vector<vector<int>>& mat) {
    for (auto& row : mat) {
        for (auto& ele : row) {
            cout << ele << " ";
        }
        cout << endl;
    }
}

vector<vector<int>> addMatrices(vector<vector<int>>& A, vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> result(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = A[i][j] + B[i][j];
    return result;
}

vector<vector<int>> subtractMatrices(vector<vector<int>>& A, vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> result(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = A[i][j] - B[i][j];
    return result;
}


vector<vector<int>> multiplyMatrices(vector<vector<int>>& A, vector<vector<int>>& B) {
    int r1 = A.size(), c1 = A[0].size();
    int r2 = B.size(), c2 = B[0].size();
    vector<vector<int>> result(r1, vector<int>(c2, 0));

    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            for (int k = 0; k < c1; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return result;
}

vector<vector<int>> strassenMultiply(vector<vector<int>>& A, vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));

    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    int newSize = n / 2;

    vector<vector<int>> A11(newSize, vector<int>(newSize)), A12(newSize, vector<int>(newSize)),
                        A21(newSize, vector<int>(newSize)), A22(newSize, vector<int>(newSize)),
                        B11(newSize, vector<int>(newSize)), B12(newSize, vector<int>(newSize)),
                        B21(newSize, vector<int>(newSize)), B22(newSize, vector<int>(newSize)),
                        C11(newSize, vector<int>(newSize)), C12(newSize, vector<int>(newSize)),
                        C21(newSize, vector<int>(newSize)), C22(newSize, vector<int>(newSize)),
                        M1, M2, M3, M4, M5, M6, M7;

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }
    
    vector<vector<int>> temp1 = subtractMatrices(B12, B22);
    vector<vector<int>> temp2 = addMatrices(A11, A12);
    vector<vector<int>> temp3 = addMatrices(A21, A22);
    vector<vector<int>> temp4 = subtractMatrices(B21, B11);
    vector<vector<int>> temp5 = addMatrices(A11, A22);
    vector<vector<int>> temp6 = addMatrices(B11, B22);
    vector<vector<int>> temp7 = subtractMatrices(A12, A22);
    vector<vector<int>> temp8 = addMatrices(B21, B22);
    vector<vector<int>> temp9 = subtractMatrices(A11, A21);
    vector<vector<int>> temp10 = addMatrices(B11, B12);


    M1 = strassenMultiply(A11, temp1);
    M2 = strassenMultiply(temp2, B22);
    M3 = strassenMultiply(temp3, B11);
    M4 = strassenMultiply(A22, temp4);
    M5 = strassenMultiply(temp5, temp6);
    M6 = strassenMultiply(temp7, temp8);
    M7 = strassenMultiply(temp9, temp10);


    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C11[i][j] = M5[i][j] + M4[i][j] - M2[i][j] + M6[i][j];
            C12[i][j] = M1[i][j] + M2[i][j];
            C21[i][j] = M3[i][j] + M4[i][j];
            C22[i][j] = M5[i][j] + M1[i][j] - M3[i][j] - M7[i][j];
        }
    }

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }

    return C;
}

int matrixChainDP(int arr[], int n, vector<vector<int>>& split) {
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int l = 2; l < n; l++) {
        for (int i = 1; i < n - l + 1; i++) {
            int j = i + l - 1;
            dp[i][j] = INT_MAX;

            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k + 1][j] + arr[i - 1] * arr[k] * arr[j];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    split[i][j] = k;
                }
            }
        }
    }

    return dp[1][n - 1];
}

vector<vector<int>> multiplyOptimalChain(vector<vector<vector<int>>>& matrices, vector<vector<int>>& split, int i, int j, bool useStrassen) {
    if (i == j) return matrices[i - 1];

    int k = split[i][j];
    auto A = multiplyOptimalChain(matrices, split, i, k, useStrassen);
    auto B = multiplyOptimalChain(matrices, split, k + 1, j, useStrassen);

    if (useStrassen) {
        return strassenMultiply(A, B);
    } else {
        return multiplyMatrices(A, B);
    }
}

int main() {
    int n;
    cout << "Enter the number of matrices: ";
    cin >> n;

    int arr[n + 1];
    cout << "Enter the dimensions array: ";
    for (int i = 0; i <= n; i++) {
        cin >> arr[i];
    }

    vector<vector<int>> split(n + 1, vector<int>(n + 1, -1));
    int minCost = matrixChainDP(arr, n + 1, split);
    cout << "Minimum number of multiplications (DP): " << minCost << endl;

    vector<vector<vector<int>>> matrices;
    bool allSquare = true;
    char randomInput;
    cout << "Do you want random matrices? (y/n): ";
    cin >> randomInput;

    srand(time(0));
    for (int i = 0; i < n; i++) {
        int rows = arr[i];
        int cols = arr[i + 1];
        vector<vector<int>> matrix(rows, vector<int>(cols));

        if (randomInput == 'y' || randomInput == 'Y') {
            for (int r = 0; r < rows; r++) {
                for (int c = 0; c < cols; c++) {
                    matrix[r][c] = rand() % 10;
                }
            }
        } else {
            cout << "Enter matrix " << i + 1 << " (" << rows << "x" << cols << "):\n";
            for (int r = 0; r < rows; r++) {
                for (int c = 0; c < cols; c++) {
                    cin >> matrix[r][c];
                }
            }
        }
        matrices.push_back(matrix);

        if (rows != cols) allSquare = false;
    }

    vector<vector<int>> result;
    if (allSquare) {
        cout << "All matrices are square. Performing Strassen's Multiplication...\n";
        result = multiplyOptimalChain(matrices, split, 1, n, true);
    } else {
        cout << "Non-square matrices detected. Performing optimal chain multiplication...\n";
        result = multiplyOptimalChain(matrices, split, 1, n, false);
    }

    cout << "Final multiplied matrix:\n";
    printMatrix(result);

    return 0;
}
