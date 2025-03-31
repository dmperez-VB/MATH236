#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Character to number mapping
int charToNum(char c) {
    if (c == ' ') return 0;
    return c - 'A' + 1;
}

// Number to character mapping
char numToChar(int n) {
    if (n == 0) return ' ';
    return 'A' + n - 1;
}

// Matrix multiplication with modulo operation
vector<vector<int>> multiplyAndMod(const vector<vector<int>>& A, const vector<vector<int>>& B, int MOD = 27) {
    int rowsA = A.size(), colsA = A[0].size();
    int rowsB = B.size(), colsB = B[0].size();
    
    // Ensure multiplication is valid (columns of A must match rows of B)
    if (colsA != rowsB) {
        cerr << "Matrix dimensions do not match for multiplication!" << endl;
        exit(1);
    }

    vector<vector<int>> result(rowsA, vector<int>(colsB, 0));

    // Matrix multiplication with modulo operation
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            for (int k = 0; k < colsA; ++k) {
                result[i][j] = (result[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        }
    }

    return result;
}

// Convert text to matrix form
vector<vector<int>> textToMatrix(const string& text) {
    vector<int> nums;
    for (char c : text) {
        if (c == ' ' || (c >= 'A' && c <= 'Z')) {
            nums.push_back(charToNum(c));
        }
    }

    // Pad with zeros if not divisible by 4
    while (nums.size() % 4 != 0) {
        nums.push_back(0);
    }

    // Convert the linear vector into a 4xN matrix
    int cols = nums.size() / 4;
    vector<vector<int>> matrix(4, vector<int>(cols));

    for (int i = 0; i < nums.size(); ++i) {
        matrix[i % 4][i / 4] = nums[i];
    }

    return matrix;
}

// Convert matrix back to text
string matrixToText(const vector<vector<int>>& matrix) {
    string result;
    for (int j = 0; j < matrix[0].size(); ++j) {
        for (int i = 0; i < matrix.size(); ++i) {
            result += numToChar(matrix[i][j]);
        }
    }
    return result;
}

// Encode function
string encode(const string& plaintext, const vector<vector<int>>& A) {
    vector<vector<int>> P = textToMatrix(plaintext);
    vector<vector<int>> C = multiplyAndMod(A, P);
    return matrixToText(C);
}

// Decode function
string decode(const string& ciphertext, const vector<vector<int>>& B) {
    vector<vector<int>> C = textToMatrix(ciphertext);
    vector<vector<int>> P = multiplyAndMod(B, C);
    return matrixToText(P);
}

int main() {
    // Define the encoding matrix A (4x4)
    vector<vector<int>> A = {
        {14, 12, 26, 15},
        {8, 0, 7, 8},
        {6, 13, 20, 7},
        {7, 18, 25, 8}
    };

    // Define the decoding matrix B (4x4)
    vector<vector<int>> B = {
        {9, 19, 18, 26},
        {24, 26, 25, 5},
        {2, 2, 3, 22},
        {23, 3, 3, 2}
    };

    string message;
    cout << "Enter Message In CAPS: ";
    getline(cin, message);

    string encrypted = encode(message, A);
    string decrypted = decode(encrypted, B);

    cout << "\nOriginal:   " << message << endl;
    cout << "Encrypted:  " << encrypted << endl;
    cout << "Decrypted:  " << decrypted << endl;

    return 0;
}
