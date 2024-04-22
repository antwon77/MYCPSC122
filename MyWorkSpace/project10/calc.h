
/*
Name: anthony hidalgo
Class: CPSC 122, Section 1
Date Submitted: February 25, 2021
Assignment: 10 
Description: Part 1 of Calculator Assignment 
To Compile: make
To Execute: ./calc "(121+12)"
*/


#ifndef CALC_H
#define CALC_H

#include "stack2.h"

class Calc {
public:
    Calc(char* argvIn);
    ~Calc();
    void DisplayInFix();
    void DisplayPostFix();
    int Evaluate();

private:
    char* inFix;
    char* postFix;
    int* valueTbl;
    int valueIdx;
    Stack* stk;

    bool CheckTokens();
    void MakeValueTbl();
    void Parse();
    int FindLast(int cur);
    bool CheckParens();
    void InFixToPostFix();
    void ResetStack(Stack* stk);
};

#endif
