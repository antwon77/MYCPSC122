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
    int FindLast(int cur);
    bool CheckParens();
    void InFixToPostFix();
    void ResetStack(Stack* stk);

    char* inFix;
    int* valueTbl;
    int valueIdx;
    Stack* stk;
};

#endif