/* Write a C ++ Program for creating a queue with 5 elements 10 9 8 7 6 and print its elements.

Instructions
- Write a comment to make your code readable.
- Use descriptive variables in your (Name of the variables should show their purposes).
- Ensure your code compiles without any errors/warnings/deprecations 
- Avoid too many & unnecessary usages of white spaces (newline, spaces, tabs, …)
- Always test the code thoroughly, before saving/submitting exercises/projects. */

#include <iostream>
#include <queue>
using namespace std;

int main() {
    // Declare a queue specifically for integer values
    queue<int> numberQueue;

    // Push the 5 specified elements into the back of the queue
    numberQueue.push(10);
    numberQueue.push(9);
    numberQueue.push(8);
    numberQueue.push(7);
    numberQueue.push(6);

    cout << "Elements in the queue (First-In, First-Out): ";

    // Iterate through the queue until it contains no elements
    while (!numberQueue.empty()) {
        // Access the element at the front of the queue
        int currentFrontValue = numberQueue.front();
        
        // Print the retrieved value
        cout << currentFrontValue << " ";
        
        // Pop (remove) the front element to expose the next one
        numberQueue.pop();
    }
    
    // Output a newline for clean terminal formatting
    cout << "\n";

    return 0;
}
