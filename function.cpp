#include <array>
#include <math.h>
#include <iostream>
#include "function.h"

using namespace std;

Function::Function(int _id, string _name) {
    this->id = _id;
    this->name = _name;
}

void Function::addInput(Variable *input) {
    this->inputs.push_back(input);
}

void Function::setOutput(Variable *_output) {
    this->output = _output;
}

vector<Node *> Function::getIncomings() {
    vector<Node *> tmp;
    for (Variable *var : inputs) {
        tmp.push_back(var);
    }
    return tmp;
}

vector<Node *> Function::getOutgoings() {
    vector<Node *> tmpe;
    tmpe.push_back(output);
    return tmpe;
}

int Function::getIndegree() {
    return inputs.size();
}

Function::~Function() {
    delete output;
}

Cosine::Cosine(int _id, string _name) : Function(_id, _name) {}

void Cosine::doForward() {
    Variable *inp = inputs[0];
    output->value = cos(inp->value);
}

void Cosine::doBackward() {
    inputs[0]->derivative += -1 * output->derivative * sin(inputs[0]->value);
}

Sine::Sine(int _id, string _name) : Function(_id, _name) {}


void Sine::doForward() {
    Variable *inp = inputs[0];
    output->value = sin(inp->value);
}

void Sine::doBackward() {
    inputs[0]->derivative += output->derivative * cos(inputs[0]->value);
}

Tangent::Tangent(int _id, string _name) : Function(_id, _name) {}


void Tangent::doForward() {
    Variable *inp = inputs[0];
    output->value = tan(inp->value);

}

void Tangent::doBackward() {
    inputs[0]->derivative += output->derivative * (1 / pow(cos(inputs[0]->value), 2));
}

ArcCosine::ArcCosine(int _id, string _name) : Function(_id, _name) {}


void ArcCosine::doForward() {
    Variable *inp = inputs[0];
    output->value = acos(inp->value);
}

void ArcCosine::doBackward() {
    inputs[0]->derivative += output->derivative * -1 / (sqrt(1 - pow(inputs[0]->value, 2)));
}

void ArcSine::doForward() {
    Variable *inp = inputs[0];
    output->value = asin(inp->value);
}

ArcSine::ArcSine(int _id, string _name) : Function(_id, _name) {}

void ArcSine::doBackward() {
    inputs[0]->derivative += output->derivative / (sqrt(1 - pow(inputs[0]->value, 2)));

}

ArcTangent::ArcTangent(int _id, string _name) : Function(_id, _name) {}

void ArcTangent::doForward() {
    Variable *inp = inputs[0];
    output->value = atan(inp->value);
}

void ArcTangent::doBackward() {
    inputs[0]->derivative += output->derivative / (1 + pow(inputs[0]->value, 2));

}

Exponential::Exponential(int _id, string _name) : Function(_id, _name) {}

void Exponential::doForward() {
    output->value = exp(inputs[0]->value);
}

void Exponential::doBackward() {
    inputs[0]->derivative += output->derivative * exp(inputs[0]->value);
}

Log::Log(int _id, string _name) : Function(_id, _name) {}

void Log::doForward() {
    output->value = log(inputs[0]->value);
}

void Log::doBackward() {
    inputs[0]->derivative += output->derivative / inputs[0]->value;
}

Log10::Log10(int _id, string _name) : Function(_id, _name) {}


void Log10::doForward() {
    output->value = log10(inputs[0]->value);
}

void Log10::doBackward() {
    inputs[0]->derivative += output->derivative / inputs[0]->value / log(10);

}

Sqrt::Sqrt(int _id, string _name) : Function(_id, _name) {}


void Sqrt::doForward() {
    output->value = sqrt(inputs[0]->value);
}

void Sqrt::doBackward() {
    inputs[0]->derivative += output->derivative / 2 / sqrt(inputs[0]->value);
}

Addition::Addition(int _id, string _name) : Function(_id, _name) {}


void Addition::doForward() {
    output->value = inputs[0]->value + inputs[1]->value;
}

void Addition::doBackward() {
    inputs[0]->derivative += 1 * output->derivative;
    inputs[1]->derivative += 1 * output->derivative;
}

Multiplication::Multiplication(int _id, string _name) : Function(_id, _name) {}

void Multiplication::doForward() {
    output->value = inputs[0]->value * inputs[1]->value;
}

void Multiplication::doBackward() {
    inputs[0]->derivative += output->derivative * inputs[1]->value;
    inputs[1]->derivative += output->derivative * inputs[0]->value;
}

Subtraction::Subtraction(int _id, string _name) : Function(_id, _name) {}

void Subtraction::doForward() {
    output->value = inputs[0]->value - inputs[1]->value;
}

void Subtraction::doBackward() {
    inputs[0]->derivative += 1 * output->derivative;
    inputs[1]->derivative += -1 * output->derivative;
}

Division::Division(int _id, string _name) : Function(_id, _name) {}

void Division::doForward() {
    output->value = inputs[0]->value / inputs[1]->value;
}

void Division::doBackward() {
    inputs[0]->derivative += output->derivative / inputs[1]->value;
    inputs[1]->derivative += output->derivative * -1 * inputs[0]->value / pow(inputs[1]->value, 2);

}

Power::Power(int _id, string _name) : Function(_id, _name) {}

void Power::doForward() {
    output->value = pow(inputs[0]->value, inputs[1]->value);
}

void Power::doBackward() {
    inputs[0]->derivative += output->derivative * inputs[1]->value * pow(inputs[0]->value, inputs[1]->value - 1);
    inputs[1]->derivative += output->derivative * pow(inputs[0]->value, inputs[1]->value) * log(inputs[0]->value);
}

Identity::Identity(int _id, string _name) : Function(_id, _name) {}


void Identity::doForward() {
    output->value = inputs[0]->value;
}

void Identity::doBackward() {
    inputs[0]->derivative = output->derivative;
}

