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

bool ExpressionManager::isLeftParen(string t)
{
  for (int i = 0; i < t.size(); i++)
  {
    if (t == "(" || t == "[" || t == "{")
    {
      return true;
    }
    else
      return false;
  }
}

bool ExpressionManager::isRightParen(string t)
{
  for (int i = 0; i < t.size(); i++)
  {
    if (t == ")" || t == "]" || t == "}")
    {
      return true;
    }
    else
      return false;
  }
}

int ExpressionManager::precedence(string operator)
{
  switch (t.at(0))
  {
    case ')' :
    case '}' :
    case ']' :
      return 3;
      break;
    case '(' :
    case '{' :
    case '[' :
      return 0;
      break;
    case '/' :
    case '%' :
    case '*' :
      return 2;
      break;
    case '+' :
    case '-' :
      return 1;
      break;
  }
}

const std::string OPERATORS = "+-*/%";
const std::string OPERATORS2 = "({[)}]"
const std::string PRECEDENCE[] = { 1, 1, 2, 2 };
const std::string PRECEDENCE2[] = { 0, 0, 0, 3, 3, 3 };

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
    }l
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

  stack<string> postfixString;
  string tempToken = "";
  string pushToStack = "";
  stringstream getInput(postfixExpression);
  int precedence = 0;

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
      if ((tempToken == "/" || tempToken == "%") && temp2 == "0")
      {
        return "invalid";
      }
      postfixString.pop();
      string temp3 = "( " + postfixString.top() + " " + tempToken + " " + temp2 + " )";
      postfixString.pop();
      postfixString.push(temp3);


    }
  }
  if (postfixString.size() > 1)
  {
    return "invalid";
  }


  return postfixString.top();
}






string ExpressionManager::postfixEvaluate(string postfixExpression)
{
  stack<int> postfixInt;
  string tempToken = "";
  string pushToStack = "";
  stringstream getInput(postfixExpression);
  while (getInput >> tempToken)
  {
    if (isNumber(tempToken))
    {
      postfixInt.push(atoi(tempToken.c_str()));
    }
    else if (!isOperator(tempToken))
      {
        return "invalid";
      }
    else
    {
      if (postfixInt.size() < 2)
      {
        return "invalid";
      }
      int temp2 = postfixInt.top();
      if ((tempToken == "/" || tempToken == "%") && temp2 == 0)
      {
        return "invalid";
      }
      postfixInt.pop();

      int temp3;
  switch (tempToken.at(0))
  {
    case '*' :
      temp3 = postfixInt.top() * temp2;
      break;
    case '/' :
      temp3 = postfixInt.top() / temp2;
      break;
    case '+' :
      temp3 = postfixInt.top() + temp2;
      break;
    case '-' :
      temp3 = postfixInt.top() - temp2;
      break;
    case '%' :
      temp3 = postfixInt.top() % temp2;
      break;
  }

//      string temp3 = "( " + postfixInt.top() + " " + tempToken + " " + temp2 + " )";
      postfixInt.pop();
      postfixInt.push(temp3);


    }
  }

  if (postfixInt.size() > 1)
  {
    return "invalid";
  }

  stringstream ss;
  ss << postfixInt.top();
  string str = ss.str();
  return str; //needs to be a string
}

string ExpressionManager::infixToPostfix(string infixExpression)
{
  stack<string> postfixString;
  string tempToken = "";
  string postfix = "";
  stringstream getInput(postfixExpression);

  while (getInput >> tempToken)
  {
    if (isNumber(tempToken))
    {
      postfixInt.push(tempToken);
    }
    else if (isOperator(tempToken))
      {
        return "invalid";
      }





  }

  return 0;
}
