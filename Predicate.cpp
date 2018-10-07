#include "Predicate.h"

Predicate::Predicate(string newName)
{
  name = newName;
}

void Predicate::changeName(string newName)
{
  name = newName;
}

string Predicate::getName()
{
  return name;
}

void Predicate::addParam(string value)
{
  Parameter p(value);
  params.push_back(p);
}

void Predicate::clearVector()
{
  params.clear();
}

vector<string> Predicate::getParam()
{
  vector<string> parameters;
  for(unsigned int i = 0; i < params.size(); i++)
  {
    parameters.push_back(params[i].toString());
  }
  return parameters;
}

string Predicate::toString()
{
  stringstream ss;
  ss << name << "(" << params[0].toString();

  for(unsigned int i = 1; i < params.size(); i++)
  {
    ss << ",";
    ss << params[i].toString();
  }

  ss << ")";
  return ss.str();
}
