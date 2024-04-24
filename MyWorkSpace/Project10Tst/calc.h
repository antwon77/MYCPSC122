#ifndef CALC
#define CALC

#include "stack2.h"

struct results {
    int len;
    int* items;
};

class Calc { 
public: 
    Calc(char* argvIn);
    ~Calc();
    void DisplayInFix();

private:
    bool CheckTokens();
    void MakeValueTbl();
    void Parse();
    results* AddToValueTbl(char* expression);
    bool CheckParens();
    int CalculateTotal(); // Declaration of the CalculateTotal() method
    int FindLast(int cur);

    char*  inFix;
    int*  valueTbl;
    int valueIdx;
    results* nums; // Added declaration of nums as a member variable
    Stack* stk;
};

#endif
