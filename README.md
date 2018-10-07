# DatalogParser
Scans, parses, and interprets a Datalog program.

Scanner reads a datalog program from a text file and identifies the datalog tokens found in the file and stores them in different data types.

Parser builds a data structure that represents the datalog program. Using the Datalog Grammar, the parser tests the input from the text file to determine if it is a valid datalog program. 

Interpreter uses relational database operations such as join and union to evaluate the facts, rules, and queries of the datalog program. The program employs the use of dependency graphs and reverse dependency graphs built and accessed through recursive depth-first searches in order to improve evaluation of the rules.

Input: Text file containing a Datalog program

Output: The program outputs the dependency graph as an adjacency list. Since each node in the graph is representative of one of the rules in the Datalog program, the nodes are outputted as 'R' followed by the rule number. For example, each node in the graph that represents the first rule in the Datalog program would be outputted 'R0'. The program then outputs the result of evaluating the rules. For each rule that is evaluated, the rule is outputted followed by the tuples generated from the evaluation of that rule. The strongly connected components (SCC) used in the rule evaluation are also outputted as well as the number of passes through the rules that it took to evaluate the SCC. For each query, the output is either 'Yes()' or 'No', where 'Yes()' is printed when the query is true in which case the tuples that make it true are also printed and the number of facts for which the query is true is printed inside the parenthesis. 'No' is printed when the query cannot be true based on evaluation of facts and rules.

**All files of this project were written by Elizabeth Van Patten
