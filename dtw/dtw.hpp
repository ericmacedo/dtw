#ifndef __DTW_H_INCLUDED__
#define __DTW_H_INCLUDED__

#include <vector>
#include <string>
#include <ctime>
#include "../timeserie/timeserie.hpp"
#include "../util/util.hpp"

using namespace std;

class DTW {
public:
    DTW (vector<Timeserie*>*& tests, vector<Timeserie*>*& trains, string s);

    clock_t startTime, deltaTime;

    float scores;

    int n, m;

    string name;

    vector<Timeserie*>* tests;
    vector<Timeserie*>* trains;

    void Start();

    void Start(int w);

    void Start(string opt);

private:
    float OPT(Timeserie* x, Timeserie* y);

    float OPT(Timeserie* x, Timeserie* y, int w);

    float OPT_I(Timeserie* x, Timeserie* y);

    float OPT_D(Timeserie* x, Timeserie* y);
};

#endif
