#ifndef FUNCTION_H
#define FUNCTION_H

#include <vector>
#include <string>
#include "variable.h"

using namespace std;

/*
An abstract subclass of node class and represents the functions.
Due to the different functionality, we have variable and function classes.
*/
class Function : public Node {

public:

    // represents the list of variables that are inputs of this function
    vector<Variable *> inputs;

    // represents the output variable of the function.
    Variable *output;

    //Function();

    Function(int _id, string _name = ""); // custom constructor

    ~Function(); // destructor

    // adds given variable as an input of this function
    void addInput(Variable *input);

    // sets the output variable of the function
    void setOutput(Variable *_output);

    // following two functions are inherited features from node class
    vector<Node *> getIncomings();

    vector<Node *> getOutgoings();

    int getIndegree();

    // following two functions will be implemented by the subclasses of Function class

    // performs forward pass and sets the value of output variable
    virtual void doForward() = 0;

    // performs backward pass and sets the derivative values of the input variables
    virtual void doBackward() = 0;

};

/*
Subclass of function class that provides forward and backward pass functionalities 
for multiplication
*/
class Multiplication : public Function {
public:
    Multiplication(int _id, string _name = "");

    void doForward();

    void doBackward();
};

/*
Subclass of function class that provides forward and backward pass functionalities 
for addition
*/
class Addition : public Function {
public:
    Addition(int _id, string _name = "");

    void doForward();

    void doBackward();
};

/*
Subclass of function class that provides forward and backward pass functionalities 
for sine
*/
class Sine : public Function {
public:
    Sine(int _id, string _name = "");

    void doForward();

    void doBackward();
};


class Cosine : public Function {
public:
    Cosine(int _id, string _name);

    void doForward();

    void doBackward();
};

class Tangent : public Function {
public:
    Tangent(int _id, string _name);

    void doForward();

    void doBackward();
};

class ArcCosine : public Function {
public:
    ArcCosine(int _id, string _name);

    void doForward();

    void doBackward();
};

class ArcSine : public Function {
public:
    ArcSine(int _id, string _name);

    void doForward();

    void doBackward();
};

class ArcTangent : public Function {
public:
    ArcTangent(int _id, string _name);

    void doForward();

    void doBackward();
};

class Exponential : public Function {
public:
    Exponential(int _id, string _name);

    void doForward();

    void doBackward();
};

class Log : public Function {
public:
    Log(int _id, string _name);

    void doForward();

    void doBackward();
};

class Log10 : public Function {
public:
    Log10(int _id, string _name);

    void doForward();

    void doBackward();
};

class Sqrt : public Function {
public:
    Sqrt(int _id, string _name);

    void doForward();

    void doBackward();
};

class Subtraction : public Function {
public:
    Subtraction(int _id, string _name);

    void doForward();

    void doBackward();
};

class Division : public Function {
public:
    Division(int _id, string _name);

    void doForward();

    void doBackward();
};

class Power : public Function {
public:
    Power(int _id, string _name);

    void doForward();

    void doBackward();
};

class Identity : public Function {
public:
    Identity(int _id, string _name);

    void doForward();

    void doBackward();
};

#endif // VARIABLE