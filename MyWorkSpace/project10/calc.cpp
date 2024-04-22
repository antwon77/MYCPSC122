#include <iostream>
#include "calc.h"
#include <cstring>
#include <cstdlib>

using namespace std;

Calc::Calc(char* argvIn) {
    inFix = new char[strlen(argvIn) + 1];
    strcpy(inFix, argvIn);
    MakeValueTbl();
    if (!CheckTokens()) {
        cout << "Error: Invalid tokens." << endl;
        exit(EXIT_FAILURE);
    }
    Parse();
    if (!CheckParens()) {
        cout << "Error: Unbalanced parentheses." << endl;
        exit(EXIT_FAILURE);
    }
    InFixToPostFix();
    stk = new Stack;
}

Calc::~Calc() {
    delete[] inFix;
    delete[] postFix;
    delete[] valueTbl;
    ResetStack(stk);
    delete stk;
}

void Calc::DisplayInFix() {
    cout << "Infix Expression: " << inFix << endl;
}

void Calc::DisplayPostFix() {
    cout << "Postfix Expression: " << postFix << endl;
}

int Calc::Evaluate() {
    stk->Reset();
    int i = 0;
    while (postFix[i] != '\0') {
        if (isdigit(postFix[i])) {
            stk->Push(valueTbl[postFix[i] - 'A']);
        } else {
            int operand2 = stk->Pop();
            int operand1 = stk->Pop();
            switch (postFix[i]) {
                case '+':
                    stk->Push(operand1 + operand2);
                    break;
                case '-':
                    stk->Push(operand1 - operand2);
                    break;
                case '*':
                    stk->Push(operand1 * operand2);
                    break;
                case '/':
                    stk->Push(operand1 / operand2);
                    break;
            }
        }
        i++;
    }
    return stk->Pop();
}

bool Calc::CheckTokens() {
    int i = 0;
    while (inFix[i] != '\0') {
        if (!(isalpha(inFix[i]) || isdigit(inFix[i]) || strchr("+-*/()", inFix[i]))) {
            return false;
        }
        i++;
    }
    return true;
}

void Calc::MakeValueTbl() {
    valueTbl = new int[26]();
    valueIdx = 0;
}

void Calc::Parse() {
    int i = 0;
    while (inFix[i] != '\0') {
        if (isalpha(inFix[i])) {
            inFix[i] = 'A' + valueIdx;
            int lastDigit = FindLast(i);
            char* numString = new char[lastDigit - i + 2];
            strncpy(numString, inFix + i, lastDigit - i + 1);
            numString[lastDigit - i + 1] = '\0';
            valueTbl[valueIdx++] = atoi(numString);
            delete[] numString;
            i = lastDigit;
        }
        i++;
    }
}

int Calc::FindLast(int cur) {
    while (isdigit(inFix[cur])) {
        cur++;
    }
    return cur - 1;
}

bool Calc::CheckParens() {
    int count = 0;
    int i = 0;
    while (inFix[i] != '\0') {
        if (inFix[i] == '(') {
            count++;
        } else if (inFix[i] == ')') {
            count--;
        }
        i++;
    }
    return count == 0;
}

void Calc::InFixToPostFix() {
    postFix = new char[strlen(inFix) + 1];
    int postFixIdx = 0;
    Stack operators;
    int i = 0;
    while (inFix[i] != '\0') {
        if (isdigit(inFix[i])) {
            postFix[postFixIdx++] = inFix[i];
        } else if (isalpha(inFix[i])) {
            postFix[postFixIdx++] = inFix[i];
        } else if (inFix[i] == '(') {
            operators.Push(inFix[i]);
        } else if (inFix[i] == ')') {
            while (!operators.IsEmpty() && operators.Top() != '(') {
                postFix[postFixIdx++] = operators.Pop();
            }
            operators.Pop();
        } else {
            while (!operators.IsEmpty() && operators.Top() != '(' && 
                   ((inFix[i] == '*' || inFix[i] == '/') && (operators.Top() == '*' || operators.Top() == '/'))) {
                postFix[postFixIdx++] = operators.Pop();
            }
            operators.Push(inFix[i]);
        }
        i++;
    }
    while (!operators.IsEmpty()) {
        postFix[postFixIdx++] = operators.Pop();
    }
    postFix[postFixIdx] = '\0';
}

void Calc::ResetStack(Stack* stk) {
    while (!stk->IsEmpty()) {
        stk->Pop();
    }
}
