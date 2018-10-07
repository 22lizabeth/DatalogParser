#include "Scanner.h"

Scanner::Scanner(string newFileName)
{
  fileName = newFileName;
  currentLineNum = 1;
}

vector<Token> Scanner::scanToken() {

  ifs.open(fileName);
  if(!ifs.is_open())
  {
    return tokens;
  }

  input = ifs.get();

  while(!ifs.eof())
  {
      Token t;
      currentString = "";

      skipWS();
      if(ifs.eof())
      {
        break;
      }

      switch (input) {
        case ',':
          t.changeType(COMMA);
          t.changeValue(",");
          t.changeLineNum(currentLineNum);
          tokens.push_back(t);
          input = ifs.get();
          break;
        case '.':
          t.changeType(PERIOD);
          t.changeValue(".");
          t.changeLineNum(currentLineNum);
          tokens.push_back(t);
          input = ifs.get();
          break;
        case '?':
          t.changeType(Q_MARK);
          t.changeValue("?");
          t.changeLineNum(currentLineNum);
          tokens.push_back(t);
          input = ifs.get();
          break;
        case '(':
          t.changeType(LEFT_PAREN);
          t.changeValue("(");
          t.changeLineNum(currentLineNum);
          tokens.push_back(t);
          input = ifs.get();
          break;
        case ')':
          t.changeType(RIGHT_PAREN);
          t.changeValue(")");
          t.changeLineNum(currentLineNum);
          tokens.push_back(t);
          input = ifs.get();
          break;
        case ':':
            input = ifs.get();
            checkForDash(); //check for :- COLON_DASH
            break;
        case '*':
          t.changeType(MULTIPLY);
          t.changeValue("*");
          t.changeLineNum(currentLineNum);
          tokens.push_back(t);
          input = ifs.get();
          break;
        case '+':
          t.changeType(ADD);
          t.changeValue("+");
          t.changeLineNum(currentLineNum);
          tokens.push_back(t);
          input = ifs.get();
          break;
        case '\'':
          currentString.push_back(input);
          stringLineNum = currentLineNum;
          scanString(); //get full string or reach end unidentified
          break;
        case '#':
          currentString.push_back(input);
          scanComment();
          break;
        default:
            currentString.push_back(input);
            checkForUndef();
            break;
        }
    }

    Token t(EOFILE, "", currentLineNum);
    tokens.push_back(t);
    ifs.close();
    return tokens;
}

void Scanner::skipWS()
{
    if(isspace(input))
    {
      while(isspace(input))
      {
        if(input == '\n')
        {
          currentLineNum++;
        }
          input = ifs.get();
      }
    }
}


void Scanner::checkForDash()
{
  if(input == '-')
  {
    t.changeType(COLON_DASH);
    t.changeValue(":-");
    t.changeLineNum(currentLineNum);
    tokens.push_back(t);
    input = ifs.get();
  }
  else
  {
    t.changeType(COLON);
    t.changeValue(":");
    t.changeLineNum(currentLineNum);
    tokens.push_back(t);
  }
}

void Scanner::scanString()
{
  //I have ' in my currentString
  input = ifs.get();

  if(input == '\'')
  {
    currentString.push_back(input);
    input = ifs.get();
    checkForApost();
  }
  else
  {
    continueString();
  }
}

void Scanner::checkForApost()
{
    if(input == '\'')
    {
      currentString.push_back(input);
      scanString();
    }
    else if(ifs.eof())
    {
      t.changeType(UNDEFINED);
      t.changeValue(currentString);
      t.changeLineNum(stringLineNum);
      tokens.push_back(t);
    }
    else
    {
      t.changeType(STRING);
      t.changeValue(currentString);
      t.changeLineNum(stringLineNum);
      tokens.push_back(t);
    }
}

void Scanner::continueString()
{
    while(input != '\'' && !ifs.eof())
    {
      if(input == '\n')
      {
        currentLineNum++;
      }
      currentString.push_back(input);
      input = ifs.get();
    }

    if(ifs.eof())
    {
      t.changeType(UNDEFINED);
      t.changeValue(currentString);
      t.changeLineNum(stringLineNum);
      tokens.push_back(t);
    }
    else
    {
        currentString.push_back(input);
        input = ifs.get();
        checkForApost();
    }
}

void Scanner::scanComment()
{
  input = ifs.get();
  if(input == '|')
  {
    currentString.push_back(input);
    scanBlockComment();
  }
  else
  {
    ifs.unget();
    scanLineComment();
  }
}

void Scanner::scanLineComment()
{
  //currentString hold "#"
  input = ifs.get();
  while(input != '\n' && !ifs.eof())
  {
    currentString.push_back(input);
    input = ifs.get();
  }
}

void Scanner::scanBlockComment()
{
  //currentString holds "#"
  stringLineNum = currentLineNum;
  input = ifs.get();

  while(!ifs.eof())
  {
    if(input == '#' && currentString.back() == '|')
    {
      currentString.push_back(input);
      input = ifs.get();
      return;
    }

    if(input == '\n')
    {
      currentLineNum++;
    }

    currentString.push_back(input);
    input = ifs.get();
  }
}

void Scanner::checkForUndef()
{
  if(isalpha(input))
  {
    scanIdent();
  }
  else
  {
    t.changeType(UNDEFINED);
    t.changeValue(currentString);
    t.changeLineNum(currentLineNum);
    tokens.push_back(t);
    input = ifs.get();
  }
}

void Scanner::scanIdent()
{
  input = ifs.get();
  while(!isspace(input) && !ifs.eof())
  {
    if(!isdigit(input) && !isalpha(input))
    {
      checkForSpecial();
      return;
    }
    currentString.push_back(input);
    input = ifs.get();
  }

  checkForSpecial();

  if(ifs.eof())
  {
    return;
  }
  else if(input == '\n')
  {
    currentLineNum++;
    input = ifs.get();
  }
  else
  {
    input = ifs.get();
  }
}

void Scanner::checkForSpecial()
{
  if(currentString == "Schemes")
  {
    t.changeType(SCHEMES);
    t.changeValue("Schemes");
    t.changeLineNum(currentLineNum);
    tokens.push_back(t);
  }
  else if(currentString == "Facts")
  {
    t.changeType(FACTS);
    t.changeValue("Facts");
    t.changeLineNum(currentLineNum);
    tokens.push_back(t);
  }
  else if(currentString == "Rules")
  {
    t.changeType(RULES);
    t.changeValue("Rules");
    t.changeLineNum(currentLineNum);
    tokens.push_back(t);
  }
  else if(currentString == "Queries")
  {
    t.changeType(QUERIES);
    t.changeValue("Queries");
    t.changeLineNum(currentLineNum);
    tokens.push_back(t);
  }
  else
  {
    t.changeType(ID);
    t.changeValue(currentString);
    t.changeLineNum(currentLineNum);
    tokens.push_back(t);
  }
}
