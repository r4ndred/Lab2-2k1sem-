#pragma once

#include <iostream>
#include <string>
#include <stdexcept>
#include <cctype>

using namespace std;

struct StackNode;
void push(StackNode*& top, int value);
int pop(StackNode*& top);
int peek(StackNode* top);
bool isEmpty(StackNode* top);
int getPrecedence(char op);
int applyOperation(int a, int b, char op);
string infixToPostfix(const string& expression);
int evaluatePostfix(const string& postfix);
 