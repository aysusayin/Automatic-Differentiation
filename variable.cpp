#include <iostream>
#include "function.h"

using namespace std;

Node::~Node() {}

Node::Node() {
}


vector<Node *> Node::getOutgoings() {}

vector<Node *> Node::getIncomings() {}

Variable::Variable(int _id, string _name, double _value) {
    this->id = _id;
    this->name = _name;
    this->value = _value;
    this->derivative = 0;
}

void Variable::addTo(Function *_to) {
    to.push_back(_to);
}

void Variable::setFrom(Function *_from) {
    from = _from;
}

int Variable::getIndegree() {
    if (from == nullptr) return 0;
    return 1;
}

vector<Node *> Variable::getIncomings() {
    vector<Node *> tmp;
    tmp.push_back(from);
    return tmp;
}

vector<Node *> Variable::getOutgoings() {
    vector<Node *> tmpe;
    for (Function *fnc : to) {
        tmpe.push_back(fnc);
    }
    return tmpe;
}

Variable::~Variable() {
    delete from;
}

Variable::Variable() {
    this->derivative = 0;
}

