#include "Rule.h"

Rule::Rule()
{

}

vector<Predicate> Rule::getPreds()
{
  return preds;
}

string Rule::getRuleName()
{
  return preds[0].getName();
}

void Rule::clearVector()
{
  preds.clear();
}

void Rule::addPred(Predicate pred)
{
  preds.push_back(pred);
}

string Rule::toString()
{
  stringstream ss;
  ss << preds[0].toString();
  ss << " :- " << preds[1].toString();

  for(unsigned int i = 2; i < preds.size(); i++)
  {
    ss << ",";
    ss << preds[i].toString();
  }

  return ss.str();
}
