#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include "graph.h"
#include "variable.h"
#include "function.h"
#include <queue>
#include <iterator>
#include <sstream>
#include <cmath>
#include <climits>
#include <list>

using namespace std;

template<class Container>
void split1(const string &str, Container &cont) {
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(cont));
}

// helper function that checks whether the given string is number or not.
bool isNumber(const string &s) {
    char *end = 0;
    double val = strtod(s.c_str(), &end);
    return end != s.c_str() && val != HUGE_VAL;
}

int Graph::getVariable(string inp) {
    int res;
    if (isNumber(inp)) {
        double val = stod(inp.c_str());
        idCount++;
        name[idCount] = inp;
        vars[idCount] = new Variable(idCount, inp, val);
        res = idCount;
        type[idCount] = VARIABLE;
    } else {
        if (id.find(inp) == id.end()) {
            idCount++;
            id[inp] = idCount;
            name[idCount] = inp;
            vars[idCount] = new Variable(idCount, inp);
            res = idCount;
            type[idCount] = VARIABLE;
        } else {
            res = id[inp];
        }
    }
    return res;
}

string Graph::getOutputName() {
    return name[outputNode];
}

Graph::~Graph() {}

int Graph::getFunction(string fnc) {
    idCount++;
    name[idCount] = fnc;
    type[idCount] = FUNCTION;
    Function *f;
    // cout << "new Function: " << fnc << endl;
    if (fnc.compare("mult") == 0)
        f = new Multiplication(idCount, fnc);
    else if (fnc.compare("add") == 0)
        f = new Addition(idCount, fnc);
    else if (fnc.compare("subs") == 0)
        f = new Subtraction(idCount, fnc);
    else if (fnc.compare("divide") == 0)
        f = new Division(idCount, fnc);
    else if (fnc.compare("sin") == 0)
        f = new Sine(idCount, fnc);
    else if (fnc.compare("cos") == 0)
        f = new Cosine(idCount, fnc);
    else if (fnc.compare("identity") == 0)
        f = new Identity(idCount, fnc);
    else if (fnc.compare("tan") == 0)
        f = new Tangent(idCount, fnc);
    else if (fnc.compare("acos") == 0)
        f = new ArcCosine(idCount, fnc);
    else if (fnc.compare("asin") == 0)
        f = new ArcSine(idCount, fnc);
    else if (fnc.compare("atan") == 0)
        f = new ArcTangent(idCount, fnc);
    else if (fnc.compare("exp") == 0)
        f = new Exponential(idCount, fnc);
    else if (fnc.compare("log") == 0)
        f = new Log(idCount, fnc);
    else if (fnc.compare("log10") == 0)
        f = new Log10(idCount, fnc);
    else if (fnc.compare("pow") == 0)
        f = new Power(idCount, fnc);
    else if (fnc.compare("sqrt") == 0)
        f = new Sqrt(idCount, fnc);
    fncs[idCount] = f;
    return idCount;
}

void Graph::addUnaryFunction(string fnc, string inp, string out) {
    int fId = getFunction(fnc);
    int inpId = getVariable(inp);
    int outId = getVariable(out);

    fncs[fId]->addInput(vars[inpId]);
    fncs[fId]->setOutput(vars[outId]);

    vars[inpId]->addTo(fncs[fId]);
    vars[outId]->setFrom(fncs[fId]);
}

void Graph::addBinaryFunction(string fnc, string inp1, string inp2, string out) {
    int fId = getFunction(fnc);
    int inp1Id = getVariable(inp1);
    int inp2Id = getVariable(inp2);
    int outId = getVariable(out);
    fncs[fId]->addInput(vars[inp1Id]);
    fncs[fId]->addInput(vars[inp2Id]);
    fncs[fId]->setOutput(vars[outId]);

    vars[inp1Id]->addTo(fncs[fId]);
    vars[inp2Id]->addTo(fncs[fId]);
    vars[outId]->setFrom(fncs[fId]);
}

void Graph::addAssignment(string lvalue, string rvalue) {
    int lId = getVariable(lvalue);
    int rId = getVariable(rvalue);
    int fId = getFunction("identity");

    fncs[fId]->addInput(vars[rId]);
    fncs[fId]->setOutput(vars[lId]);

    vars[rId]->addTo(fncs[fId]);
    vars[lId]->setFrom(fncs[fId]);


}

void Graph::readGraph(string fileName) {

    ifstream infunctionfile(fileName);

    while (!infunctionfile.eof()) {
        string in;
        infunctionfile >> in;

        if (in.compare("input") == 0) {
            string input;
            infunctionfile >> input;
            int tmpid = getVariable(input);
            inputNodes.push_back(tmpid);

        } else if (in.compare("output") == 0) {
            string output;
            infunctionfile >> output;
            outputNode = getVariable(output);
            vars[outputNode]->derivative = 1;

        } else {
            string line;
            getline(infunctionfile, line);
            vector<string> words;
            split1(line, words);

            if (words.size() == 4) {
                addBinaryFunction(words[1], words[2], words[3], in);

            } else if (words.size() == 3) {
                addUnaryFunction(words[1], words[2], in);

            } else if (words.size() == 2) {
                addAssignment(in, words[1]);
            }

        }
    }
}

void Graph::initTopologicalOrder(queue<Node *> &q, int incSizes) {
    queue<Node *> nodeQueue;
    vector<NodeStr> strs;
    for (auto it = vars.begin(); it != vars.end(); it++) {
        Node *t = it->second;
        NodeStr tmp;
        if (type[t->id] == VARIABLE) {
            vars[t->id]->derivative = 0;
        }
        tmp.indegree = t->getIndegree();
        tmp.node = t;
        if (tmp.indegree == 0)nodeQueue.push(t);
        strs.push_back(tmp);
    }
    vars[outputNode]->derivative = 1;

    for (auto it = fncs.begin(); it != fncs.end(); it++) {
        Node *t = it->second;
        NodeStr tmp;
        tmp.indegree = t->getIndegree();
        tmp.node = t;
        if (tmp.indegree == 0)nodeQueue.push(t);
        strs.push_back(tmp);
    }

    while (!nodeQueue.empty()) {
        Node *tmp = nodeQueue.front();
        nodeQueue.pop();

        vector<Node *> tmpV = tmp->getOutgoings();

        for (Node *n : tmpV) {
            for (int i = 0; i < strs.size(); i++) {
                if (n->id == strs[i].node->id) {
                    if (--strs[i].indegree == 0) nodeQueue.push(strs[i].node);
                    break;
                }
            }
        }
        q.push(tmp);
        topOrderStack.push(tmp);
    }

    if (incSizes != q.size())isCyclicB = true;

}

bool Graph::isCyclic() {
    return isCyclicB;
}

double Graph::forwardPass(vector<double> inputValues) {

    for (int i = 0; i < inputNodes.size(); i++) {
        Variable *var = vars[inputNodes[i]];
        var->value = inputValues[i];
    }

    queue<Node *> topOrQueue;

    int a = vars.size() + fncs.size();

    initTopologicalOrder(topOrQueue, a);
    if (isCyclic()) return INT_MIN;

    while (!topOrQueue.empty()) {
        Node *tmp = topOrQueue.front();
        topOrQueue.pop();
        int id = tmp->id;
        if (type[id] == FUNCTION) {
            Function *f = (Function *) tmp;
            f->doForward();
        }
    }

    return vars[outputNode]->value;

}

vector<double> Graph::backwardPass() {

    while (!topOrderStack.empty()) {
        Node *tmp = topOrderStack.top();
        topOrderStack.pop();
        int id = tmp->id;
        if (type[id] == FUNCTION) {
            Function *f = (Function *) tmp;
            f->doBackward();
        }
    }

    vector<double> derivatives;

    for (int id : inputNodes) {
        derivatives.push_back(vars[id]->derivative);
    }

    return derivatives;

}

bool NodeStr::operator<(const NodeStr &rhs) const {
    return indegree > rhs.indegree;
}

bool NodeStr::operator==(const NodeStr &rhs) const {
    return node->id == rhs.node->id;
}
