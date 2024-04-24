#include <iostream>
#include <cstring> // Include for strlen, strcpy, and strtok
#include "calc.h"

using namespace std;

Calc::Calc(char* argvIn) {
    // Initialize nums to nullptr to avoid accessing uninitialized memory
    nums = nullptr;

    // Initialize inFix to argvIn
    inFix = argvIn;

    // Invoke set-up functions
    CheckTokens();
    CheckParens();
    MakeValueTbl();
    Parse();
}

Calc::~Calc() {
    // Deallocate memory for nums if it was allocated
    if (nums != nullptr) {
        delete[] nums->items;
        delete nums;
    }
}

bool Calc::CheckTokens() {
    return true; // Placeholder implementation
}

void Calc::MakeValueTbl() {
    valueTbl = new int[26];
    valueIdx = 0;
}

void Calc::Parse() {
    nums = AddToValueTbl(inFix);
    for (int i = 0; i < nums->len; i++)
        cout << nums->items[i] << endl; // Fix: Access nums->items[i] instead of nums->items
}

results* Calc::AddToValueTbl(char* expression) {
    char* ptr;
    char* str = new char[strlen(expression) + 1];
    strcpy(str, expression);
    int* tokens = new int[26];
    char delimiters[] = " ()+_*/"; //tokens used in arithmetic expressions

    int i = 0;
    ptr = strtok(str,delimiters);
    while (ptr != NULL) {
        tokens[i] = atoi(ptr); 
        ptr = strtok(NULL,delimiters);
        i++;
    }
    results* nums = new results;
    nums->len = i;
    nums->items = tokens;
    return nums;
}

bool Calc::CheckParens() {
    return true; // Placeholder implementation
}

void Calc::DisplayInFix() {
    int total = CalculateTotal(); // Calculate the total
    cout << "Total: " << total << endl; // Display the total
}

int Calc::CalculateTotal() {
    if (nums == nullptr) {
        return 0; // Return 0 if nums is not initialized
    }

    Stack operandStack; // Stack to store operands

    for (int i = 0; i < nums->len; i++) {
        int token = nums->items[i]; // Current token

        // If token is an operand, push it onto the stack
        if (token >= 'A' && token <= 'Z') {
            operandStack.Push(valueTbl[token - 'A']);
        } else { // Otherwise, token is an operator
            int operand2 = operandStack.Peek(); // Second operand
            operandStack.Pop(); // Remove the second operand
            int operand1 = operandStack.Peek(); // First operand
            operandStack.Pop(); // Remove the first operand

            // Perform the operation based on the token
            int result;
            switch (token) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    result = operand1 / operand2; // Division by zero not handled
                    break;
                default:
                    cerr << "Invalid operator: " << (char)token << endl;
                    return 0; // Return 0 if an invalid operator is encountered
            }

            // Push the result back onto the stack
            operandStack.Push(result);
        }
    }

    // The final result is the only item left on the stack
    return operandStack.Peek();
}

int Calc::FindLast(int cur) {
    // Placeholder implementation
    return 0;
}
