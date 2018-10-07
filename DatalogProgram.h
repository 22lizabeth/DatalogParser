#ifndef DATALOG_PROGRAM_H
#define DATALOG_PROGRAM_H

#include "Token.h"
#include "Scanner.h"
#include "Predicate.h"
#include "Rule.h"

class DatalogProgram
{
  private:
    int tokenNum;
    TokenType currentToken;
    vector<Token> tokens;
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Predicate> queries;
    vector<Rule> rules;
    Predicate pred;
    Rule r;
    string compileStr;
  public:
    DatalogProgram(vector<Token> &scannerTokens, TokenType startTokenType);
    //Get data members functions
    vector<Predicate> getSchemes();
    vector<Predicate> getFacts();
    vector<Predicate> getQueries();
    vector<Rule> getRules();
    TokenType getToken();
    //Grammar utility functions
    void match(TokenType idealToken);
    void startGrammar();
    void error();
    //Schemes grammar line
    void schemeList();
    void scheme();
    //Facts grammar line
    void factList();
    void fact();
    //Rules grammar line
    void ruleList();
    void rule();
    //Queries grammar line
    void queryList();
    void query();
    //Predicate grammars
    void headPredicate();
    void predicate();
    //other list grammars
    void predicateList();
    void parameterList();
    void stringList();
    void idList();
    //parameter grammar
    void parameter();
    //expression grammar
    void expressParameter();
    void expression();
    //operator grammar
    void operatorFunct();
};

#endif
