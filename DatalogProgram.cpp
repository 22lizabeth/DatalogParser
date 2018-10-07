#include "DatalogProgram.h"

DatalogProgram::DatalogProgram(vector<Token> &scannerTokens, TokenType startTokenType)
{
  tokens = scannerTokens;
  currentToken = startTokenType;
  tokenNum = 0;
}

vector<Predicate> DatalogProgram::getSchemes()
{
  return schemes;
}

vector<Predicate> DatalogProgram::getFacts()
{
  return facts;
}

vector<Predicate> DatalogProgram::getQueries()
{
  return queries;
}

vector<Rule> DatalogProgram::getRules()
{
  return rules;
}

TokenType DatalogProgram::getToken()
{
  return tokens[tokenNum].getTokenType();
}

void DatalogProgram::match(TokenType idealToken)
{
  if(currentToken == idealToken)
  {
    tokenNum++;
    currentToken = getToken();
  }
  else
  {
    error();
  }
}

void DatalogProgram::error()
{
  throw tokens[tokenNum];
}

void DatalogProgram::startGrammar()
{
  //SCHEMES
  match(SCHEMES);
  match(COLON);
  scheme();
  schemeList();
  //FACTS
  match(FACTS);
  match(COLON);
  factList();
  //RULES
  match(RULES);
  match(COLON);
  ruleList();
  //QUERIES
  match(QUERIES);
  match(COLON);
  query();
  queryList();
  if(currentToken != EOFILE)
  {
      error();
  }
}

//Schemes grammar line
void DatalogProgram::schemeList()
{
  if(currentToken == ID)
  {
    scheme();
    schemeList();
  }
}

void DatalogProgram::scheme()
{
  headPredicate();
  schemes.push_back(pred);
  pred.clearVector();
}

//Facts grammar line
void DatalogProgram::factList()
{
  if(currentToken == ID)
  {
    pred.changeName(tokens[tokenNum].getValue());
    fact();
    factList();
  }
}

void DatalogProgram::fact()
{
  match(ID);
  match(LEFT_PAREN);

  match(STRING);
  pred.addParam(tokens[tokenNum - 1].getValue());

  stringList();
  match(RIGHT_PAREN);
  match(PERIOD);

  facts.push_back(pred);
  pred.clearVector();
}

//Rules grammar line
void DatalogProgram::ruleList()
{
  if(currentToken == ID)
  {
    rule();
    ruleList();
  }
}

void DatalogProgram::rule()
{
  r.clearVector();

  headPredicate();
  r.addPred(pred);
  pred.clearVector();

  match(COLON_DASH);

  predicate();
  r.addPred(pred);
  pred.clearVector();

  predicateList();
  match(PERIOD);

  rules.push_back(r);
}

//Queries grammar line
void DatalogProgram::queryList()
{
  if(currentToken == ID)
  {
    query();
    queryList();
  }
}

void DatalogProgram::query()
{
  predicate();
  match(Q_MARK);
  queries.push_back(pred);
  pred.clearVector();
}

//Predicate grammars
void DatalogProgram::headPredicate()
{
  pred.changeName(tokens[tokenNum].getValue());
  match(ID);
  match(LEFT_PAREN);
  match(ID);
  pred.addParam(tokens[tokenNum - 1].getValue());
  idList();
  match(RIGHT_PAREN);
}

void DatalogProgram::predicate()
{
  pred.changeName(tokens[tokenNum].getValue());
  match(ID);
  match(LEFT_PAREN);
  parameter();
  parameterList();
  match(RIGHT_PAREN);
}

//other list grammars
void DatalogProgram::predicateList()
{
  if(currentToken == COMMA)
  {
    match(COMMA);
    predicate();
    r.addPred(pred);
    pred.clearVector();
    predicateList();
  }
}

void DatalogProgram::parameterList()
{
  if(currentToken == COMMA)
  {
    match(COMMA);
    parameter();
    parameterList();
  }
}

void DatalogProgram::stringList()
{
  if(currentToken == COMMA)
  {
    match(COMMA);
    match(STRING);
    pred.addParam(tokens[tokenNum - 1].getValue());
    //checkforDuplicate();
    stringList();
  }
}

void DatalogProgram::idList()
{
  if(currentToken == COMMA)
  {
    match(COMMA);
    match(ID);
    pred.addParam(tokens[tokenNum - 1].getValue());
    idList();
  }
}

//parameter grammar
void DatalogProgram::parameter()
{
  switch (currentToken) {
    case STRING:
      match(STRING);
      pred.addParam(tokens[tokenNum - 1].getValue());
      break;
    case ID:
      match(ID);
      pred.addParam(tokens[tokenNum - 1].getValue());
      break;
    case LEFT_PAREN:
      compileStr = "";
      expression();
      pred.addParam(compileStr);
      break;
    default:
      error();
  }

}

void DatalogProgram::expressParameter()
{
  switch (currentToken) {
    case STRING:
      match(STRING);
      compileStr += tokens[tokenNum - 1].getValue();
      break;
    case ID:
      match(ID);
      compileStr += tokens[tokenNum - 1].getValue();
      break;
    case LEFT_PAREN:
      expression();
      break;
    default:
      error();
  }
}

//expression grammar
void DatalogProgram::expression()
{
  match(LEFT_PAREN);
  compileStr += "(";
  expressParameter();
  operatorFunct();
  expressParameter();
  match(RIGHT_PAREN);
  compileStr += ")";
}

//operator grammar
void DatalogProgram::operatorFunct()
{
  if(currentToken == ADD)
  {
    match(ADD);
    compileStr += "+";
  }
  else if(currentToken == MULTIPLY)
  {
    match(MULTIPLY);
    compileStr += "*";
  }
  else
  {
    error();
  }
}
