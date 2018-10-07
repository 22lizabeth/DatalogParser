#ifndef DATABASE_H
#define DATABASE_H

#include "DatalogProgram.h"
#include "Relation.h"
#include "Graph.h"

class Database
{
  private:
    map<string, Relation> relations;
    int numTuples;
    int rulePasses;
    Graph dependencyGraph;
    Graph reverseGraph;
  public:
    Database(){ numTuples = 0; rulePasses = 0; };
    void evaluateSchemes(vector<Predicate> &schemes);
    void evaluateFacts(vector<Predicate> &facts);
    void evaluateQueries(vector<Predicate> &queries);
    void printDependencyGraph();
    void findSCC(vector<Rule> &rules);
    void evaluateRules(vector<int> &currentSCC, vector<Rule> &rules);
    void evaluateRule(int currentSCC, vector<Rule> &rules);
    void buildGraphs(vector<Rule> &rules);
    Relation evaluatePredicates(vector<Predicate> &predicates);
    Relation createNewRelation(Relation r, vector<string> &values);
    Relation join(Relation r1, Relation r2);
    Relation unionRelations(Relation r1, Relation r2);
};

#endif
