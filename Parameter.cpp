#include "Parameter.h"

Parameter::Parameter(string newValue)
{
  value = newValue;
}

string Parameter::toString()
{
  return value;
}
