#ifndef SCANNER_H
#define SCANNER_H


#include "Token.h"

class Scanner {
private:
  string fileName;
  ifstream ifs;
  vector<Token> tokens;
  int currentLineNum;
  Token t;
  int stringLineNum;
  string currentString;
  char input;

public:
  Scanner(string newFileName);
  vector<Token> scanToken();
  void skipWS();
  void checkForDash();
  void scanString();
  void checkForApost();
  void continueString();
  void scanComment();
  void scanLineComment();
  void scanBlockComment();
  void checkForUndef();
  void scanIdent();
  void checkForSpecial();

};

#endif
