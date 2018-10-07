#ifndef PREDICATE_H
#define PREDICATE_H

#include<iostream>
#include<string>
#include<vector>
#include <sstream>

#include "Parameter.h"

using namespace std;

class Predicate
{
  private:
    string name;
    vector<Parameter> params;
  public:
    Predicate(string newName = "");
    void changeName(string newName);
    string getName();
    void addParam(string value);
    void clearVector();
    vector<string> getParam();
    string toString();
};

#endif
