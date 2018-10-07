#include "Database.h"

void Database::evaluateSchemes(vector<Predicate> &schemes)
{
  for(unsigned int i = 0; i < schemes.size(); i++)
  {
    string relationName = schemes[i].getName();
    Scheme newScheme;

    vector<string> parameters = schemes[i].getParam();
    for(unsigned int i = 0; i < parameters.size(); i++)
    {
      newScheme.push_back(parameters[i]);
    }

    Relation r(relationName, newScheme);
    relations[relationName] = r;
    }
}

void Database::evaluateFacts(vector<Predicate> &facts)
{
  for(unsigned int i = 0; i < facts.size(); i++)
  {
    string relationName = facts[i].getName();
    Tuple t;
    vector<string> parameters = facts[i].getParam();
    for(unsigned int i = 0; i < parameters.size(); i++)
    {
      t.push_back(parameters[i]);
    }
    int tupleSize = relations[relationName].getTupleSize();
    relations[relationName].insertTuple(t);
    if(tupleSize < relations[relationName].getTupleSize())
    {
      numTuples++;
    }
  }
}

void Database::evaluateQueries(vector<Predicate> &queries)
{
  //call select, project, rename, and print
  for(unsigned int i = 0; i < queries.size(); i++)
  {
    string queryName = queries[i].getName();
    vector<string> parameters = queries[i].getParam();
    Relation r2 = relations[queryName];

    r2 = createNewRelation(r2, parameters);
    string printString = queries[i].toString();
    cout << printString << "?" << " ";
    r2.printQuerySuccess();
    if(i+1 != queries.size())
    {
      cout << endl;
    }
  }
}

void Database::printDependencyGraph()
{
  //Print the Dependency Graph
  dependencyGraph.printGraph();
}

void Database::findSCC(vector<Rule> &rules)
{
  vector<int> postorderNodes = reverseGraph.getPostorderNodes();
  //Add the correct postorder nodes from reverse graph to dependency graph
  dependencyGraph.changePostorderNodes(postorderNodes);

  //Call DFS on the depenendency graph for nodes in postorder
  while(!postorderNodes.empty())
  {
    dependencyGraph.DFS2(postorderNodes.back());

    //Print current SCC
    cout << endl << "SCC: ";
    dependencyGraph.printSCC();

    //Get the current vector of SCC's
    vector<int> currentSCC = dependencyGraph.getSCC();

    //Checking to see how many times evaluate rules needs to be run
    bool selfDependent = false;
    if(currentSCC.size() == 1)
    {
      int nodeID = postorderNodes.back();
      Node n = dependencyGraph.getNode(nodeID);
      selfDependent = n.checkForSelfDependence(currentSCC[0]);
      if(!selfDependent)
      {
        evaluateRule(currentSCC[0], rules);
      }
    }
    if(currentSCC.size() > 1 || selfDependent)
    {
      rulePasses = 0;
      evaluateRules(currentSCC, rules);
    }

    //Clear the current SCC vector
    dependencyGraph.clearSCC();

    postorderNodes = dependencyGraph.getPostorderNodes();
  }
}

void Database::evaluateRules(vector<int> &currentSCC, vector<Rule> &rules)
{
  int startTuples = numTuples;
  for(unsigned int i = 0; i < currentSCC.size(); i++)
  {
    //Get rule to be evaluated first
    int currentRule = currentSCC[i];

    //Get intermediate relations for each rule - select, project, and join all right side relations
    vector<Predicate> predicates = rules[currentRule].getPreds();
    Relation r = evaluatePredicates(predicates);

    //Get indexes to project from left side of rule
    vector<string> parameters = predicates[0].getParam();
    vector<string> currentScheme = r.getScheme();
    vector<int> projectIndexes;
    for(unsigned int i = 0; i < parameters.size(); i++)
    {
      int j = 0;
      while(parameters[i] != currentScheme[j])
      {
        j++;
      }
      projectIndexes.push_back(j);
    }
    r = r.project(projectIndexes);

    //Rename to become union compatible with the original relation from schemes
    string newName = predicates[0].getName();
    r.changeName(newName);
    vector<string> renameAttributes = relations[newName].getScheme();
    r = r.rename(renameAttributes);

    //Print rule that is currently being worked on
    string printString = rules[currentRule].toString();
    cout << endl << printString << ".";

    //Union new tuples with the original relation from schemes
    relations[newName] = unionRelations(relations[newName], r);

  }

  //call evaluteRules until no new tuples are added
  rulePasses++;
  if(startTuples != numTuples)
  {
    evaluateRules(currentSCC, rules);
  }
  else
  {
    cout << endl << rulePasses << " passes: ";
    dependencyGraph.printSCC();
  }
}

void Database::evaluateRule(int currentSCC, vector<Rule> &rules)
{
    //Get intermediate relations for the rule - select, project, and join all right side relations
    vector<Predicate> predicates = rules[currentSCC].getPreds();
    Relation r = evaluatePredicates(predicates);

    //Get indexes to project from left side of rule
    vector<string> parameters = predicates[0].getParam();
    vector<string> currentScheme = r.getScheme();
    vector<int> projectIndexes;
    for(unsigned int i = 0; i < parameters.size(); i++)
    {
      int j = 0;
      while(parameters[i] != currentScheme[j])
      {
        j++;
      }
      projectIndexes.push_back(j);
    }
    r = r.project(projectIndexes);

    //Rename to become union compatible with the original relation from schemes
    string newName = predicates[0].getName();
    r.changeName(newName);
    vector<string> renameAttributes = relations[newName].getScheme();
    r = r.rename(renameAttributes);

    //Print rule that is currently being worked on
    string printString = rules[currentSCC].toString();
    cout << endl << printString << ".";

    //Union new tuples with the original relation from schemes
    relations[newName] = unionRelations(relations[newName], r);

    cout << endl << "1 passes: ";
    dependencyGraph.printSCC();
}

void Database::buildGraphs(vector<Rule> &rules)
{
  for(unsigned int i = 0; i < rules.size(); i++)
  {
    //Is this necessary???
    dependencyGraph.addNode(i);
    reverseGraph.addNode(i);
  }

  for(unsigned int i = 0; i < rules.size(); i++)
  {
    //where do I create the initial map IDs?
    vector<Predicate> predicates = rules[i].getPreds();
    for(unsigned int j = 1; j < predicates.size(); j++)
    {
      string currentPredicate = predicates[j].getName();
      for(unsigned int k = 0; k < rules.size(); k++)
      {
        string headPredicate = rules[k].getRuleName();
        if(currentPredicate == headPredicate)
        {
          dependencyGraph.addEdge(i,k);
          reverseGraph.addEdge(k,i);
        }
      }
    }
  }
  //Call DFS on the reverse graph to assign postorder numbers
  for(unsigned int i = 0; i < rules.size(); i++)
  {
    reverseGraph.DFS1(i);
  }

}

Relation Database::evaluatePredicates(vector<Predicate> &predicates)
{
  vector<Relation> interRelations; /*Put somewhere else maybe?*/
  for(unsigned int i = 1; i < predicates.size(); i++)
  {
    string interRuleName = predicates[i].getName();
    vector<string> parameters = predicates[i].getParam();
    Relation r2 = relations[interRuleName];

    r2 = createNewRelation(r2, parameters);
    interRelations.push_back(r2);
  }

  for(unsigned int i = 1; i < interRelations.size(); i++)
  {
    interRelations[0] = join(interRelations[0], interRelations[i]);
  }

  return interRelations[0];
}

Relation Database::createNewRelation(Relation r2, vector<string> &parameters)
{
  map<string, int> varIndexes;
  vector<int> indexes;
  vector<string> attributeVars;

  for(unsigned int i = 0; i < parameters.size(); i++)
  {
    string currentParam = parameters[i];
    if(currentParam[0] == '\'')
    {
      r2 = r2.select(i, currentParam);
    }
    else if(varIndexes.find(currentParam) == varIndexes.end())
    {
        varIndexes[currentParam] = i;
        indexes.push_back(i);
        attributeVars.push_back(currentParam);
    }
    else
    {
      r2 = r2.select(varIndexes[currentParam], i);
    }
  }

  r2 = r2.project(indexes);
  r2 = r2.rename(attributeVars);

  return r2;
}

Relation Database::join(Relation r1, Relation r2)
{
  vector<string> schemeR1 = r1.getScheme();
  vector<string> schemeR2 = r2.getScheme();
  Relation r;
  map<string, vector<int> > commonAttributes;
  vector<int> uniqueAttributes; //holds all the non duplicate attribute indexes in R2

  //Add R1's scheme to the relation r
  for(unsigned int i = 0; i < schemeR1.size(); i++)
  {
    r.addAttribute(schemeR1[i]);
  }

  //Add R2's scheme to the relation r
  for(unsigned int i = 0; i < schemeR2.size(); i++) //is there a more efficient way???
  {
    bool duplicate = false;
    for(unsigned int j = 0; j < schemeR1.size(); j++)
    {
      if(schemeR2[i] == schemeR1[j])
      {
        duplicate = true;
        commonAttributes[schemeR2[i]];
        commonAttributes[schemeR1[j]].push_back(j);
        commonAttributes[schemeR2[i]].push_back(i);
      }
    }
    if(!duplicate)
    {
      r.addAttribute(schemeR2[i]);
      uniqueAttributes.push_back(i);
    }
  }
  set<Tuple> tuples1 = r1.getTuples();
  set<Tuple> tuples2 = r2.getTuples();
  r.checkJoinCompatible(tuples1, tuples2, commonAttributes, uniqueAttributes);

  return r;
}

Relation Database::unionRelations(Relation r1, Relation r2)
{
  if(r1.getScheme() != r2.getScheme())
  {
    cout << "fail" << endl;
    return r1;
  }
  set<Tuple> tuplesToAdd = r2.getTuples();
  for(set<Tuple>::iterator it = tuplesToAdd.begin(); it != tuplesToAdd.end(); it++)
  {
    int tupleSize = r1.getTupleSize();
    r1.insertTuple(*it);
    if(tupleSize < r1.getTupleSize())
    {
      r1.printTuple(*it);
      numTuples++;
    }
  }
  return r1;
}
