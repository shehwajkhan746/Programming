/* Write a C++ program to convert an infix expression (5+2)*(8-3) into postfix form and then evaluate and print the postfix expression value.

Instructions
- Write a comment to make your code readable.
- Use descriptive variables in your (Name of the variables should show their purposes).
- Ensure your code compiles without any errors/warnings/deprecations 
- Avoid too many & unnecessary usages of white spaces (newline, spaces, tabs, …)
- Always test the code thoroughly, before saving/submitting exercises/projects. */

#include <iostream>
#include <stack>
#include <string>
#include <cctype>
using namespace std;

// Helper function to return precedence of operators
int getPrecedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

// Helper function to perform basic arithmetic
int performOperation(int operand1, int operand2, char op) {
    switch (op) {
        case '+': return operand1 + operand2;
        case '-': return operand1 - operand2;
        case '*': return operand1 * operand2;
        case '/': return operand1 / operand2;
        default: return 0;
    }
}

// Function to convert infix to postfix (Shunting Yard Algorithm)
string convertInfixToPostfix(const string& infixExpr) {
    stack<char> operatorStack;
    string postfixExpr = "";

    for (char currentChar : infixExpr) {
        // If operand (digit), append directly to output
        if (isdigit(currentChar)) {
            postfixExpr += currentChar;
        } 
        // If opening parenthesis, push to stack
        else if (currentChar == '(') {
            operatorStack.push(currentChar);
        } 
        // If closing parenthesis, pop to output until opening parenthesis is found
        else if (currentChar == ')') {
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                postfixExpr += operatorStack.top();
                operatorStack.pop();
            }
            if (!operatorStack.empty()) operatorStack.pop(); // Remove '('
        } 
        // If operator (+, -, *, /)
        else {
            while (!operatorStack.empty() && getPrecedence(operatorStack.top()) >= getPrecedence(currentChar)) {
                postfixExpr += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.push(currentChar);
        }
    }

    // Pop all remaining operators from the stack
    while (!operatorStack.empty()) {
        postfixExpr += operatorStack.top();
        operatorStack.pop();
    }

    return postfixExpr;
}

// Function to evaluate the generated postfix expression
int evaluatePostfix(const string& postfixExpr) {
    stack<int> evaluationStack;

    for (char currentChar : postfixExpr) {
        // If operand, convert from char to int and push to stack
        if (isdigit(currentChar)) {
            evaluationStack.push(currentChar - '0');
        } 
        // If operator, pop two operands, evaluate, and push result back
        else {
            int operand2 = evaluationStack.top(); evaluationStack.pop();
            int operand1 = evaluationStack.top(); evaluationStack.pop();
            
            int result = performOperation(operand1, operand2, currentChar);
            evaluationStack.push(result);
        }
    }

    // The final result remains at the top of the stack
    return evaluationStack.top();
}

int main() {
    // The target infix expression provided in the instructions
    string infixExpression = "(5+2)*(8-3)";
    
    // Step 1: Convert to Postfix
    string postfixExpression = convertInfixToPostfix(infixExpression);
    cout << "Original Infix Expression : " << infixExpression << "\n";
    cout << "Converted Postfix Form    : " << postfixExpression << "\n";
    
    // Step 2: Evaluate the Postfix string
    int finalResult = evaluatePostfix(postfixExpression);
    cout << "Evaluated Result          : " << finalResult << "\n";

    return 0;
}
