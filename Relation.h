#ifndef A_RELATION_H
#define A_RELATION_H

#include<set>
#include<map>
#include "Tuple.h"
#include "Scheme.h"

class Relation
{
  private:
    string name;
    Scheme s;
    set<Tuple> tuples;
  public:
    Relation(){};
    Relation(string newName, Scheme newS);
    string getName();
    Scheme getScheme();
    set<Tuple> getTuples();
    int getTupleSize();
    void insertTuple(Tuple t);
    void changeTuples(set<Tuple> &newTuples);
    void addAttribute(string newAttribute);
    void changeName(string newName);
    Relation select(int index, string value);
    Relation select(int index1, int index2);
    Relation project(vector<int> &indexes);
    Relation rename(vector<string> &attributeVars);
    void checkJoinCompatible(set<Tuple> &tuples1, set<Tuple> &tuples2, map<string, vector<int> > &commonAttributes, vector<int> &uniqueAttributes);
    void joinTuples(Tuple t1, Tuple t2, vector<int> &uniqueAttributes);
    void printQuerySuccess();
    void printRelation();
    void printTuple(Tuple t);
};

#endif
