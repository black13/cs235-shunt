#include "ExpressionManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <stack>
#include <cctype>

using namespace std;

const string OPEN = "([{";
const string CLOSE = ")]}";

bool ExpressionManager::isOpen(char ch)
{
  return OPEN.find(ch) != string::npos;
}

bool ExpressionManager::isClose(char ch)
{
  return CLOSE.find(ch) != string::npos;
}

bool ExpressionManager::isBalanced(string expression)
{
  stack<char> s;
  bool balanced = true;
  string::const_iterator iter = expression.begin();
  while (balanced && (iter != expression.end()))
  {
    char nextCH = *iter;
    if (isOpen(nextCH))
    {
      s.push(nextCH);
    }
    else if (isClose(nextCH))
    {
      if (s.empty())
      {
        balanced = false;
      }
      else
      {
        char topCH = s.top();
        s.pop();
        balanced = OPEN.find(topCH) == CLOSE.find(nextCH);
      }
    }
    ++iter;
  }
  return balanced && s.empty();
}

string ExpressionManager::postfixToInfix(string postfixExpression)
{
//  stack<string> postfixString;

  return 0;
}

string ExpressionManager::postfixEvaluate(string postfixExpression)
{

  return 0;
}

string ExpressionManager::infixToPostfix(string infixExpression)
{
  return 0;
}
