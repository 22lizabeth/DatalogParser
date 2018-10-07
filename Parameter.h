#ifndef PARAMETER_H
#define PARAMETER_H

#include<iostream>
#include<string>
#include<vector>
#include <sstream>

using namespace std;

class Parameter
{
  private:
    string value;
  public:
    Parameter(string newValue = "");
    string toString();

};

#endif
