# DatalogParser
Scans, parses, and interprets a Datalog program.

Scanner reads a datalog program from a text file and identifies the datalog tokens found in the file and stores them in different data types.

Parser builds a data structure that represents the datalog program. Using the Datalog Grammar, the parser tests the input from the text file to determine if it is a valid datalog program. 

Interpreter uses relational database operations such as join and union to evaluate the facts, rules, and queries of the datalog program. The program employs the use of dependency graphs and reverse dependency graphs built and accessed through recursive depth-first searches in order to improve evaluation of the rules.

**All files of this project were written by Elizabeth Van Patten
