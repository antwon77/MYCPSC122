#include <iostream>
using namespace std;

#include "calc.h"
#include <cstring>
#include <cctype>

Calc::Calc(char *argvIn) {
  stk = new Stack;
  // Checking for valid tokens in the expression
  if (!CheckTokens(argvIn)) {
    cout << "Error: Invalid expression" << endl;
  }
  // Checking for balanced parentheses
  if (!CheckParens(argvIn)) {
    cout << "Error: Unbalanced parentheses" << endl;
  }
  // Creating a value table
  MakeValueTbl();
  // Parsing the expression
  Parse(argvIn);
}

Calc::~Calc() {
  delete stk;
  delete valueTbl;
  delete inFix;
}

bool Calc::CheckTokens(char* exp) { 
  int count = 0;
  // Define the allowed characters in the expression
  char allowed[] = " ()*+-0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 0; i < strlen(exp); i++){
    for (int j = 0; j < strlen(allowed); j++){
      if(exp[i] == allowed[j]){
        count++;
      }
    }
  }
  // If the count matches the length of the expression, all characters are valid
  if(count == strlen(exp)){
    return true;
  }
  return false; 
}

void Calc::MakeValueTbl() {
  // Creating an array to store values for variables A-Z
  valueTbl = new int[26];
  // Initialize all values to 0
  for (int i = 0; i < 26; i++)
    valueTbl[i] = 0;
}

void Calc::Parse(char* exp) {
  int inFixCt = 0;
  // Allocate memory for the infix expression
  inFix = new char[strlen(exp)];

  for(int i = 0; i < strlen(exp); i++) {
    // If the character is a digit, it might be part of a number
    if(isdigit(exp[i]) == true) {
      // Extract the number from the expression
      int num = atoi(exp + i); 
      // Store the value in the value table
      valueTbl[valueIdx] = num;
      // Increment value index
      valueIdx++;
      // Assign a variable name to the value in the infix expression
      inFix[inFixCt++] = 'A' + valueIdx - 1;
      cout << inFix[inFixCt - 1] << ": " << num << endl; 
      // Skip to the end of the number
      while(isdigit(exp[i + 1]) == true) 
        i++;
    } else {
      // Copy non-digit characters directly to the infix expression
      inFix[inFixCt++] = exp[i];
    }
  }
}

bool Calc::CheckParens(char *exp) {
  int i = 0;
  // Loop through the expression to check parentheses balance
  while (exp[i] != '\0') {
    if (exp[i] == '(')
      stk->Push(exp[i]);
    if (exp[i] == ')') {
      if (stk->IsEmpty())
        return false;
      stk->Pop();
    }
    i++;
  }
  // If stack is empty after traversing the expression, parentheses are balanced
  return (stk->IsEmpty());
}

void Calc::DisplayInFix() {
  int i = 0;
  cout << "Infix: ";
  // Display the infix expression
  while (inFix[i] != '\0')
    {
    cout << inFix[i++];
    }
  cout << endl;
}
