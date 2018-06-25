#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <fstream>
#include <stack>
#include "variable.h"
#include "function.h"

using namespace std;

struct NodeStr {
    int indegree;
    Node *node;

    bool operator<(const NodeStr &rhs) const;

    bool operator==(const NodeStr &rhs) const;

};

// enum that has VARIABLE and FUNCTION with values of 0 and 1.
enum TYPES {
    VARIABLE, FUNCTION
};

/*
Graph class is created in order to construct directed graph structure
*/
class Graph {

    // map storing the name, id pairs as key and value for each node.
    unordered_map<string, int> id;

    // map storing the id, name pairs as key and value for each node.
    unordered_map<int, string> name;

    // map storing the id, type pairs as key and value for each node.
    unordered_map<int, TYPES> type;

    // map storing the id, variable* pairs as key and value for each variable.
    // in other words, it points the allocated memory of variable with given id.
    unordered_map<int, Variable *> vars;

    // map storing the id, function* pairs as key and value for each function.
    // in other words, it points the allocated memory of function with given id.
    unordered_map<int, Function *> fncs;

    // stores the ids of input nodes.
    vector<int> inputNodes;

    // stores the id of ouput node
    int outputNode;

    // helps to count ids.
    int idCount = 0;

    bool isCyclicB = false;

public:

    ~Graph(); // destructor

    // returns the id of variable with given variable name
    // if the given name is new then it creates an instance of variable and
    // updates the described mappings above and returns the id of it.
    int getVariable(string name);

    // it creates an instance of function and
    // updates the described mappings above and returns the id of it.
    int getFunction(string name);

    // its a helper function to add assignment to graph.
    void addAssignment(string lvalue, string rvalue);

    // its a helper function to add unary function to graph
    void addUnaryFunction(string fnc, string inp, string out);

    // its a helper function to add binary function to graph
    void addBinaryFunction(string fnc, string inp1, string inp2, string out);

    // it reads the graph description and constructs it.
    void readGraph(string filename);

    // checks whether the graph is cyclic or not.
    bool isCyclic();

    // performs forward pass for the graph and returns the output value.
    double forwardPass(vector<double> inputValues);

    // performs backward pass for the graph and returns the derivative values.
    vector<double> backwardPass();

    void initTopologicalOrder(queue<Node *> &q, int incSizes);

    string getOutputName();

    stack<Node *> topOrderStack;
};

#endif //GRAPH