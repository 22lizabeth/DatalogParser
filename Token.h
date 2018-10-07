#ifndef TOKEN_H
#define TOKEN_H

#include<iostream>
#include<fstream>
#include<string>
#include<cctype>
#include<map>
#include<vector>

using namespace std;

enum TokenType {
  COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH,
  MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT,
  UNDEFINED, EOFILE
};

class Token
{
  private:
    TokenType type;
    int lineNum;
    string value;
  public:
    Token(TokenType newType = COMMA, string newValue = "", int newLineNum = 0);
    TokenType getTokenType();
    string getValue();
    int getLineNum();
    void changeType(TokenType newType);
    void changeValue(string newValue);
    void changeLineNum(int newLineNum);
};

#endif
