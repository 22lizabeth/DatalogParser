#include "Token.h"
#include "Scanner.h"
#include "DatalogProgram.h"
#include "Database.h"

using namespace std;

int main(int argc, char* argv[]) {

  string fileName = argv[1];
  vector<Token> tokens;
  map<TokenType, string> tMap;
  tMap[COMMA]="COMMA";
  tMap[PERIOD]="PERIOD";
  tMap[Q_MARK]="Q_MARK";
  tMap[LEFT_PAREN]="LEFT_PAREN";
  tMap[RIGHT_PAREN]="RIGHT_PAREN";
  tMap[COLON]="COLON";
  tMap[COLON_DASH]="COLON_DASH";
  tMap[MULTIPLY]="MULTIPLY";
  tMap[ADD]="ADD";
  tMap[SCHEMES]="SCHEMES";
  tMap[FACTS]="FACTS";
  tMap[RULES]="RULES";
  tMap[QUERIES]="QUERIES";
  tMap[ID]="ID";
  tMap[STRING]="STRING";
  tMap[COMMENT]="COMMENT";
  tMap[UNDEFINED]="UNDEFINED";
  tMap[EOFILE]="EOF";

  //Initiate scanner
  Scanner s(fileName);
  tokens = s.scanToken();

  //Return if scanner failed to produce
  if(tokens.size() == 0)
  {
    return 0;
  }

  //create Datalog object
  TokenType startTokenType = tokens[0].getTokenType();
  DatalogProgram d(tokens, startTokenType);

  //Initiate Parser
  try{
    d.startGrammar();
  }catch(Token t){
    cout << "Failure!" << endl;
    cout << "  (" << tMap.at(t.getTokenType())<< ",\"";
    cout << t.getValue() << "\"," << t.getLineNum() << ")";
    cout << endl;
  }

  //Get finished lists from Parser
  vector<Predicate> schemes = d.getSchemes();
  vector<Predicate> facts = d.getFacts();
  vector<Rule> rules = d.getRules();
  vector<Predicate> queries = d.getQueries();

  //Initiate Interpreter
  Database dB;
  dB.evaluateSchemes(schemes);
  dB.evaluateFacts(facts);
  //Create dependency and reverse dependency graphs from rules
  dB.buildGraphs(rules);
  //Print the Dependency Graph
  dB.printDependencyGraph();
  cout << endl << endl << "Rule Evaluation";
  dB.findSCC(rules);
  cout << endl << endl << "Query Evaluation" << endl;
  dB.evaluateQueries(queries);

  return 0;
}
