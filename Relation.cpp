#include "Relation.h"

Relation::Relation(string newName, Scheme newScheme)
{
  name = newName;
  s = newScheme;
}

string Relation::getName()
{
  return name;
}

Scheme Relation::getScheme()
{
  return s;
}

set<Tuple> Relation::getTuples()
{
  return tuples;
}

int Relation::getTupleSize()
{
  return tuples.size();
}

void Relation::insertTuple(Tuple t)
{
  tuples.insert(t);
}

void Relation::changeTuples(set<Tuple> &newTuples)
{
  tuples = newTuples;
}

void Relation::addAttribute(string newAttribute)
{
  s.push_back(newAttribute);
}

void Relation::changeName(string newName)
{
  name = newName;
}

Relation Relation::select(int index, string value)
{
  Relation r(name, s);
  set<Tuple>::iterator currentTuple = tuples.begin();
  while(currentTuple != tuples.end())
  {
    if(currentTuple->at(index) == value)
    {
      r.insertTuple(*currentTuple);
    }
    currentTuple++;
  }
  return r;
}

Relation Relation::select(int index1, int index2)
{
  Relation r(name, s);
  set<Tuple>::iterator currentTuple = tuples.begin();
  while(currentTuple != tuples.end())
  {
    if(currentTuple->at(index1) == currentTuple->at(index2))
    {
      r.insertTuple(*currentTuple);
    }
    currentTuple++;
  }
  return r;
}

Relation Relation::project(vector<int> &indexes)
{
  Scheme newScheme;
  Relation r(name, newScheme);

  if(indexes.empty())
  {
    r.changeTuples(tuples);
    return r;
  }

  for(unsigned int i = 0; i < indexes.size(); i++)
  {
    int index = indexes[i];
    string newAttribute = s[index];
    r.addAttribute(newAttribute);
  }
  set<Tuple>::iterator currentTuple = tuples.begin();
  while(currentTuple != tuples.end())
  {
    Tuple t;
    for(unsigned int i = 0; i < indexes.size(); i++)
    {
      int index = indexes[i];
      t.push_back(currentTuple->at(index));
    }
    r.insertTuple(t);
    currentTuple++;
  }
  return r;
}

Relation Relation::rename(vector<string> &attributeVars)
{
  Scheme newScheme;
  Relation r(name, newScheme);
  r.changeTuples(tuples);

  for(unsigned int i = 0; i < attributeVars.size(); i++)
  {
    r.addAttribute(attributeVars[i]);
  }

  return r;
}

void Relation::checkJoinCompatible(set<Tuple> &tuples1, set<Tuple> &tuples2,
  map<string, vector<int> > &commonAttributes, vector<int> &uniqueAttributes)
{
  for(set<Tuple>::iterator it1 = tuples1.begin(); it1 != tuples1.end(); it1++)
  {
    for(set<Tuple>::iterator it2 = tuples2.begin(); it2 != tuples2.end(); it2++)
    {
      bool compatible = true;
      for(map<string, vector<int> >::iterator it3 = commonAttributes.begin();
        it3 != commonAttributes.end(); it3++)
      {
          int index1 = it3->second.at(0);
          int index2 = it3->second.at(1);
          if(it1->at(index1) != it2->at(index2))
          {
            compatible = false;
            //skip to end of for loop
            it3 = commonAttributes.end();
            it3--;
          }
      }
      if(compatible)
      {
        joinTuples(*it1, *it2, uniqueAttributes);
      }
    }
  }
}

void Relation::joinTuples(Tuple t1, Tuple t2, vector<int> &uniqueAttributes)
{
  Tuple t;
  for(unsigned int i = 0; i < t1.size(); i++)
  {
    t.push_back(t1[i]);
  }
  for(unsigned int i = 0; i < uniqueAttributes.size(); i++)
  {
    int addIndex = uniqueAttributes[i];
    t.push_back(t2[addIndex]);
  }
  tuples.insert(t);
}

void Relation::printQuerySuccess()
{
  if(tuples.empty())
  {
    cout << "No";
    return;
  }

  cout << "Yes(" << tuples.size() << ")";
  if(!s.empty())
  {
    printRelation();
  }
}

void Relation::printRelation()
{
  set<Tuple>::iterator currentTuple = tuples.begin();
  while(currentTuple != tuples.end())
  {
    cout << endl << "  ";
    for(unsigned int i = 0; i < s.size(); i++)
    {
      cout << s[i] << "=" << currentTuple->at(i);
      if(i+1 != s.size())
      {
        cout << ", ";
      }
    }
    currentTuple++;
  }
}

void Relation::printTuple(Tuple t)
{
  cout << endl << "  ";
  for(unsigned int i = 0; i < s.size(); i++)
  {
    cout << s[i] << "=" << t[i];
    if(i+1 != s.size())
    {
      cout << ", ";
    }
  }
}
