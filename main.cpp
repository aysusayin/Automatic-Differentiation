#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <sstream>
#include <climits>
#include <iomanip>
#include <cmath>
#include "graph.h"

using namespace std;

template<class Container>
void split1(const string &str, Container &cont) {
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(cont));
}

int main(int argc, char *argv[]) {

    ifstream inputvaluesfile(argv[2]);
    ofstream outputvalues(argv[3]);
    ofstream outputderivatives(argv[4]);

    Graph graph;

    graph.readGraph(argv[1]);

    string s;
    getline(inputvaluesfile, s);
    vector<string> words;
    split1(s, words);

    string outputName = graph.getOutputName();
    outputvalues << outputName << endl;

    for (string w : words) {
        outputderivatives << "d" << outputName << "/d" << w << " ";
    }
    outputderivatives << endl;

    while (!inputvaluesfile.eof()) {

        vector<double> inputValues;
        string s;
        getline(inputvaluesfile, s);
        if (s != "") {
            vector<string> vals;
            split1(s, vals);
            for (int i = 0; i < vals.size(); i++) {
                double d = stod(vals[i]);
                inputValues.push_back(d);
            }

            double result = graph.forwardPass(inputValues);
            if (graph.isCyclic()) {
                outputvalues.close();
                outputvalues.open(argv[3], ios::out);

                outputderivatives.close();
                outputderivatives.open(argv[4], ios::out);

                outputvalues << "ERROR: COMPUTATION GRAPH HAS CYCLE!";
                outputderivatives << "ERROR: COMPUTATION GRAPH HAS CYCLE!";

                break;
            }

            outputvalues << setprecision(16) << fixed;
            outputvalues << result << endl;

            vector<double> derivativeResults = graph.backwardPass();

            outputderivatives << setprecision(16) << fixed;

            for (double d: derivativeResults) {
                outputderivatives << d << " ";
            }

            outputderivatives << endl;

        }
    }
    outputderivatives.close();
    outputvalues.close();
    inputvaluesfile.close();

    return 0;
}
