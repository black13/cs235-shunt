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

bool ExpressionManager::isNumber(string t)
{
  for (int i = 0; i < t.size(); i++)
  {
    if (!isdigit(t.at(i)))
    {
      return false;
    }
  }
  return true;
}

const std::string OPERATORS = "+-*/";
bool ExpressionManager::isOperator(string t)
{
  return OPERATORS.find(t) != std::string::npos;
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
  //const string OPERATORS = "+-*/";
  //const int PRECEDENCE[] = { 1, 1, 2, 2 };

  stack<string> postfixString;
  string tempToken = "";
  string pushToStack = "";
  stringstream getInput(postfixExpression);
  while (getInput >> tempToken)
  {
    if (isNumber(tempToken))
    {
      postfixString.push(tempToken);
    }
    else if (!isOperator(tempToken))
      {
        return "invalid";
      }
    else
    {
      if (postfixString.size() < 2)
      {
        return "invalid";
      }
      string temp2 = postfixString.top();
      if (tempToken == "/" || tempToken == "%" && temp2 == "0")
      {
        return "invalid";
      }
      postfixString.pop();
      string temp3 = "( " + postfixString.top() + " " + tempToken + " " + temp2 + " )";
      postfixString.pop();
      postfixString.push(temp3);

      if (postfixString.size() > 1)
      {
        return "invalid";
      }
    }
  }

  return 0;
}

string ExpressionManager::postfixEvaluate(string postfixExpression)
{
  //const string OPERATORS = "+-*/";
  //const int PRECEDENCE[] = { 1, 1, 2, 2 };

  stack<string> postfixString;
  string tempToken = "";
  string pushToStack = "";
  stringstream getInput(postfixExpression);
  while (getInput >> tempToken)
  {
    if (isNumber(tempToken))
    {
      postfixString.push(tempToken);
    }
    else if (!isOperator(tempToken))
      {
        return "invalid";
      }
    else
    {
      if (postfixString.size() < 2)
      {
        return "invalid";
      }
      string temp2 = postfixString.top();
      if (tempToken == "/" || tempToken == "%" && temp2 == "0")
      {
        return "invalid";
      }
      postfixString.pop();
      string temp3 = "( " + postfixString.top() + " " + tempToken + " " + temp2 + " )";
      postfixString.pop();
      postfixString.push(temp3);

      if (postfixString.size() > 1)
      {
        return "invalid";
      }
    }
  }

  return 0;
}

string ExpressionManager::infixToPostfix(string infixExpression)
{
  return 0;
}
