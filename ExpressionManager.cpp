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
const std::string OPERATORS = "+-*/%";
const std::string OPERATORS2 = "({[)}]";
const int PRECEDENCE[] = { 1, 1, 2, 2 };
const int PRECEDENCE2[] = { 0, 0, 0, 3, 3, 3 };


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

int ExpressionManager::getPrecedence(string t)
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
  int precedence = 0;
  string prevToken = "";
  int tokenNumber = 0;
  stringstream getInput(infixExpression);

  stack<char> stack;
  bool balanced = true;
  string::const_iterator iter = infixExpression.begin();
  while (balanced && (iter != infixExpression.end()))
  {
    char nextCH = *iter;
    if (isOpen(nextCH))
    {
      stack.push(nextCH);
    }
    else if (isClose(nextCH))
    {
      if (stack.empty())
      {
        balanced = false;
      }
      else
      {
        char topCH = stack.top();
        stack.pop();
        balanced = OPEN.find(topCH) == CLOSE.find(nextCH);
      }
    }
    ++iter;
  }

  if (balanced == false)
  {
    return "invalid";
  }
  if (stack.empty() == false)
  {
    return "invalid";
  }

  while (getInput >> tempToken)
  {
    tokenNumber++;

    if (isNumber(tempToken))
    {
      if (tokenNumber < 2)
      {
        postfix += tempToken + " ";
      }

      else if (isNumber(prevToken) || isRightParen(prevToken))
      {
        return "invalid";
      }
    }



    else if (isOperator((tempToken)))
    {
      if (isOperator(prevToken) || isLeftParen(prevToken))
      {
        return "invalid";
      }



      if (postfixString.size() < 1)
      {
        postfixString.push(tempToken);
      }

      else if (getPrecedence(tempToken) > getPrecedence(postfixString.top()))
      {
        postfixString.push(tempToken);
      }

      else
      {
        while ((!postfixString.empty()) && getPrecedence(tempToken) <= getPrecedence(postfixString.top()))
        {
          postfix += postfixString.top() + " ";
          postfixString.pop();
        }
        postfixString.push(tempToken);
      }
    }




    else if (isLeftParen(tempToken))
    {
    /*  if (isNumber(prevToken) || isRightParen(prevToken))
      {
        return "invalid";
      }*/
      postfixString.push(tempToken);
    }


    else if (isRightParen(tempToken))
    {
      if (isLeftParen(prevToken) || isOperator(prevToken))
      {
        return "invalid";
      }

      while ((!postfixString.empty()) && (!(OPEN.find(postfixString.top()) == CLOSE.find(tempToken))))
      {
        postfix += postfixString.top() + " ";
        postfixString.pop();
      }

      if (!postfixString.empty())
      {
        postfixString.pop();
      }

    }
      else
      {
        return "invalid";
      }
      prevToken = tempToken;
    }
    while (!postfixString.empty())
    {
      postfix += postfixString.top() + " ";
      postfixString.pop();
    }
    postfix.erase(postfix.size() - 1);
    return postfix;
}
