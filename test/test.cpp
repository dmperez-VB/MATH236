#include <iostream>
#include <string>
#include "extern/eigen/Eigen/Dense"
#include <vector>

using namespace std;
using namespace Eigen;

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
MatrixXi multiplyandMod(const MatrixXi& A, const MatrixXi& B) {
    int MOD = 27;

    MatrixXi resultTemp = (A * B);
    MatrixXi result = resultTemp.unaryExpr([MOD](int x) { return x % MOD; });  // Use MOD here
    return result;
}

// Convert text to matrix form
MatrixXi textToMatrix(const string& text) {
    vector<int> nums;
    for (int i = 0; i < text.length(); ++i) {
        char c = text[i];
        if (c == ' ' || (c >= 'A' && c <= 'Z')) {
            nums.push_back(charToNum(c));
        }
    }

    // Pad with zeros if not divisible by 4
    while (nums.size() % 4 != 0) {
        nums.push_back(0);
    }

    int cols = nums.size() / 4;
    MatrixXi matrix(4, cols);

    for (int i = 0; i < nums.size(); i++) {
        matrix(i % 4, i / 4) = nums[i];
    }

    return matrix;
}

// Convert matrix back to text
string matrixToText(const MatrixXi& matrix) {
    string result;
    for (int j = 0; j < matrix.cols(); ++j) {
        for (int i = 0; i < matrix.rows(); ++i) {
            result += numToChar(matrix(i, j));
        }
    }
    return result;
}

// Encode function
string encode(const string& plaintext, const MatrixXi& A) {
    MatrixXi P = textToMatrix(plaintext);
    MatrixXi C = multiplyandMod(A, P);
    return matrixToText(C);
}

// Decode function
string decode(const string& ciphertext, const MatrixXi& B) {
    MatrixXi C = textToMatrix(ciphertext);
    MatrixXi P = multiplyandMod(B, C);
    return matrixToText(P);
}

int main() {
    MatrixXi A(4, 4);
    A << 14, 12, 26, 15,
         8, 0, 7, 8,
         6, 13, 20, 7,
         7, 18, 25, 8;

    MatrixXi B(4, 4);
    B << 9, 19, 18, 26,
         24, 26, 25, 5,
         2, 2, 3, 22,
         23, 3, 3, 2;

    string message;
    cout << "Enter Message In CAPS: ";
    getline(cin, message);

    string encrypted = encode(message, A);
    string decrypted = decode(encrypted, B);

    cout << "Original:   " << message << endl;
    cout << "Encrypted:  " << encrypted << endl;
    cout << "Decrypted:  " << decrypted << endl;

    return 0;
}