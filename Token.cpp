#include "Token.h"

Token::Token(TokenType newType, string newValue, int newLineNum)
{
  type = newType;
  value = newValue;
  lineNum = newLineNum;
}

TokenType Token::getTokenType()
{
  return type;
}

string Token::getValue()
{
  return value;
}

int Token::getLineNum()
{
  return lineNum;
}

void Token::changeType(TokenType newType)
{
    type = newType;
}

void Token::changeValue(string newValue)
{
    value = newValue;
}

void Token::changeLineNum(int newLineNum)
{
    lineNum = newLineNum;
}
