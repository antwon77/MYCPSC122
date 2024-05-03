#include <iostream> // Including the input/output stream library
using namespace std;

#include "calc.h" // Including the user-defined header file for the calculator
#include <cstring> // Including the C string manipulation library
#include <cctype> // Including the C character handling library

// Constructor for the Calculator class
Calc::Calc(char *argvIn)
{
  stk = new Stack; // Creating a new stack object
  if (!CheckTokens(argvIn)) // Checking if the tokens in the input expression are valid
  {
    cout << "Error: Invalid expression" << endl; // Displaying error message if the expression is invalid
  }
  if (!CheckParens(argvIn)) // Checking if parentheses in the input expression are balanced
  {
    cout << "Error: Unbalanced parentheses" << endl; // Displaying error message if parentheses are unbalanced
  }
  MakeValueTbl(); // Creating an array to store integers from the command line
  Parse(argvIn); // Parsing the input expression
  InFixToPostFix(); // Converting the infix expression to postfix
}

// Destructor for the Calculator class
Calc::~Calc() 
{
  delete stk; // Deleting the stack object
  delete valueTbl; // Deleting the array storing integer values
  delete inFix; // Deleting the infix expression
  delete postFix; // Deleting the postfix expression
}

// Function to check if the tokens in the expression are valid
bool Calc::CheckTokens(char* exp) 
{ 
  int count = 0;
  char allowed[] = " ()*+-0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // Allowed characters in the expression
  for (int i = 0; i < strlen(exp); i++){
    for (int j = 0; j < strlen(allowed); j++){
      if(exp[i] == allowed[j]){
        count++;
      }
    }

  }
  if(count == strlen(exp)){ // If count matches the length of the expression, all characters are allowed
    return true;
  }
  return false; // Otherwise, some characters are not allowed
}

// Function to create an array to store integers from the command line
void Calc::MakeValueTbl() {
  valueTbl = new int[26]; // Creating an array of size 26 to store integer values
  for (int i = 0; i < 26; i++)
    valueTbl[i] = 0; // Initializing array elements to 0
}

// Function to parse the input expression and store it in infix notation
void Calc::Parse(char* exp) 
{
  int num = 0;
  int inFixCt = 0;
  inFix = new char[strlen(exp) + 1]; // Allocating memory for the infix expression
  for(int i = 0; i < strlen(exp); i++)
    {
      if(isdigit(exp[i]) == true) // If the character is a digit
      {
        num = (exp[i] - '0'); // Converting character to integer
        while (isdigit(exp[i+1]) == true) // Handling multi-digit numbers
          {
            num = (num * 10) + (exp[i+1] - '0');
            i++;
          }
        valueTbl[valueIdx] = num; // Storing the integer value in the value table
        valueIdx++;
        inFix[inFixCt++] = 'A' + valueIdx - 1; // Storing the corresponding variable in infix notation
      } 
      else 
      {
        inFix[inFixCt++] = exp[i]; // Storing operators and other characters in infix notation
      }
    }
}

// Function to check if parentheses in the expression are balanced
bool Calc::CheckParens(char* exp) 
{
  int i = 0;
  while (exp[i] != '\0') {
    if (exp[i] == '(')
      stk->Push(exp[i]); // Pushing '(' onto the stack
    if (exp[i] == ')') {
      if (stk->IsEmpty())
        return false; // If stack is empty when encountering ')', parentheses are unbalanced
      stk->Pop(); // Popping '(' from the stack
    }
    i++;
  }
  return (stk->IsEmpty()); // If stack is empty after processing the expression, parentheses are balanced
}

// Function to evaluate the postfix expression
int Calc::Evaluate()
{
  for(int i = 0; i < strlen(postFix); i++) // Looping through the postfix expression
    {
      if(isalpha(postFix[i])) // If character is a letter (operand)
      {
        stk->Push(postFix[i]); // Pushing operand onto the stack
      }
      else // If character is an operator
      {
        int result; 
        int op1 = 0;
        int op2 = 0;
        if (isalpha(stk->Peek())) // If top of stack is an operand
        {
          op2 = valueTbl[stk->Peek() - 'A']; // Getting operand value from value table
          stk->Pop(); // Popping operand from the stack
        } 
        else
        {
          op2 = stk->Peek(); // Getting operand from the stack
          stk->Pop(); // Popping operand from the stack
        }

        if (isalpha(stk->Peek())) // If top of stack is an operand
        {
          op1 = valueTbl[stk->Peek() - 'A']; // Getting operand value from value table
          stk->Pop(); // Popping operand from the stack
        }
        else
        {
          op1 = stk->Peek(); // Getting operand from the stack
          stk->Pop(); // Popping operand from the stack
        }

        if(postFix[i] == '-') // Performing arithmetic operations based on the operator
          result = op1 - op2; 
        if(postFix[i] == '+')
          result = op1 + op2;
        if(postFix[i] == '*')
          result = op1 * op2;
        stk->Push(result); // Pushing the result onto the stack
      }
    }
  return stk->Peek(); // Returning the final result
}

// Function to convert infix expression to postfix
void Calc::InFixToPostFix()
{
  int idx = 0;
  postFix = new char[strlen(inFix) + 1]; // Allocating memory for the postfix expression
  for(int i = 0; i < strlen(inFix); i++)
    {
      if(isalpha(inFix[i])) // If character is a letter (operand)
        postFix[idx++] = inFix[i]; // Storing operand in postfix notation
      if(inFix[i] == '(')
        stk->Push(inFix[i]); // Pushing '(' onto the stack
      if(inFix[i] == '+' || inFix[i] == '-' || inFix[i] == '*') // If character is an operator
        stk->Push(inFix[i]); // Pushing operator onto the stack
      if(inFix[i] == ')') // If character is ')'
        {
          while(stk->Peek() != '(') // Pop operators from the stack until '(' is encountered
          {
            postFix[idx++] = stk->Peek(); // Storing operators in postfix notation
            stk->Pop(); // Popping operator from the stack
          }
          stk->Pop(); // Popping '(' from the stack
        }
    }
}

// Function to display the infix expression
void Calc::DisplayInFix() 
{
  int i = 0;
  cout << "Infix: ";
  while (inFix[i] != '\0') // Looping through the infix expression
    {
    cout << inFix[i++];
    }
  cout << endl;
}

// Function to display the postfix expression
void Calc::DisplayPostFix()
{
  int i = 0;
  cout << "Postfix: ";
  while (postFix[i] != '\0') // Looping through the postfix expression
    {
    cout << postFix[i++];
    }
  cout << endl;
}
