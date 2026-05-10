
/*
Write a C++ program to input a 3×3 matrix and find the sum of 2nd row.
Instructions
- Write a comment to make your code readable.
- Use descriptive variables in your (Name of the variables should show their purposes).
- Ensure your code compiles without any errors/warnings/deprecations 
- Avoid too many & unnecessary usages of white spaces (newline, spaces, tabs, …)
- Always test the code thoroughly, before saving/submitting exercises/projects.   */

#include <iostream>
using namespace std;

int main() {
    // Declare a 3x3 integer matrix and a variable to hold the sum
    int matrix[3][3];
    int secondRowSum = 0;

    // Prompt the user to input the 9 elements of the matrix
    cout << "Enter elements for the 3x3 matrix:\n";
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            cin >> matrix[row][col];
        }
    }

    // Calculate the sum of the 2nd row (index 1 in 0-based indexing)
    for (int col = 0; col < 3; ++col) {
        secondRowSum += matrix[1][col];
    }

    // Print the final calculated sum
    cout << "Output should be - " << secondRowSum << "\n";

    return 0;
}