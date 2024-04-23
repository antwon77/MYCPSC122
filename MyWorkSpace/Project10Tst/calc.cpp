#include <iostream>
using namespace std;

#include "calc.h"
#include <cstring>

Calc::Calc(char* argvIn) {
    // Invoke set-up functions
    CheckTokens();
    CheckParens();
    MakeValueTbl();
    Parse();
}

Calc::~Calc() {}

bool Calc::CheckTokens() {
    return true; // Placeholder implementation
}

void Calc::MakeValueTbl() {
    valueTbl = new int[26];
    valueIdx = 0;
}

void Calc::Parse() {
    results* nums = AddToValueTbl(inFix); // Corrected line
    for (int i = 0; i < nums->len; i++)
        cout << nums->items << endl;
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

void Calc::DisplayInFix() {}

int Calc::FindLast(int cur) {
    // Placeholder implementation
    return 0;
}