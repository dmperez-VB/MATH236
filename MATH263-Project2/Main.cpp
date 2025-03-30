#include <iostream>
#include <vector>
#include <string>
#include <iomanip>


using namespace std;


const int MOD = 27;


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


// Matrix multiplication (mod 27)
vector<vector<int>> matrixMultiply(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int rows = A.size();
    int cols = B[0].size();
    int shared = B.size();
    vector<vector<int>> result(rows, vector<int>(cols, 0));


    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            for (int k = 0; k < shared; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
            result[i][j] %= MOD;
        }
    }


    return result;
}


// Create the 4xN plaintext or ciphertext matrix
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


    int cols = nums.size() / 4;
    vector<vector<int>> matrix(4, vector<int>(cols));
    for (int i = 0; i < nums.size(); i++) {
        matrix[i % 4][i / 4] = nums[i];
    }


    return matrix;
}


// Convert matrix back to text
string matrixToText(const vector<vector<int>>& matrix) {
    string result;
    int cols = matrix[0].size();
    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < 4; i++) {
            result += numToChar(matrix[i][j]);
        }
    }
    return result;
}


// Encryption and decryption matrices
vector<vector<int>> A = {
    {14, 12, 26, 15},
    {8, 0, 7, 8},
    {6, 13, 20, 7},
    {7, 18, 25, 8}
};


vector<vector<int>> B = {
    {9, 19, 18, 26},
    {24, 26, 25, 5},
    {2, 2, 3, 22},
    {23, 3, 3, 2}
};


string encode(const string& plaintext) {
    auto P = textToMatrix(plaintext);
    auto C = matrixMultiply(A, P);
    return matrixToText(C);
}


string decode(const string& ciphertext) {
    auto C = textToMatrix(ciphertext);
    auto P = matrixMultiply(B, C);
    return matrixToText(P);
}


int main(void) {
    printf("Enter Message In CAPS: ");
    string message;
    getline(cin, message);
    string encrypted = encode(message);
    string decrypted = decode(encrypted);


    cout << "Original:   " << message << endl;
    cout << "Encrypted:  " << encrypted << endl;
    cout << "Decrypted:  " << decrypted << endl;


    return 0;
}
