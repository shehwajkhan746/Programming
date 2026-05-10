
/* 
Write a C ++ Program for pushing, popping and then printing 5 float values in a stack. 

Instructions
- Write a comment to make your code readable.
- Use descriptive variables in your (Name of the variables should show their purposes).
- Ensure your code compiles without any errors/warnings/deprecations 
- Avoid too many & unnecessary usages of white spaces (newline, spaces, tabs, …)
- Always test the code thoroughly, before saving/submitting exercises/projects.
*/

#include <iostream>
#include <stack>
using namespace std;

int main() {
    // Declare a stack specifically for floating-point numbers
    stack<float> floatNumberStack;

    // Push 5 float values onto the stack
    // Using 'f' suffix ensures literals are treated as floats, preventing compiler warnings
    floatNumberStack.push(10.5f);
    floatNumberStack.push(20.3f);
    floatNumberStack.push(30.8f);
    floatNumberStack.push(40.1f);
    floatNumberStack.push(50.9f);

    cout << "Retrieving values from the stack (Last-In, First-Out):" << endl;

    // Continue popping and printing until the stack contains no elements
    while (!floatNumberStack.empty()) {
        // Access the element at the top of the stack
        float currentTopValue = floatNumberStack.top();
        
        // Print the retrieved value
        cout << currentTopValue << endl;
        
        // Pop (remove) the top element to expose the next one
        floatNumberStack.pop();
    }

    return 0;
}
