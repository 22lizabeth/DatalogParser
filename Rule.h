#ifndef RULE_H
#define RULE_H

#include "Predicate.h"

using namespace std;

class Rule
{
  private:
    vector<Predicate> preds;

  public:
    Rule();
    vector<Predicate> getPreds();
    string getRuleName();
    void clearVector();
    void addPred(Predicate pred);
    string toString();
};
#endif
