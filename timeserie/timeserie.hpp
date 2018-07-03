#ifndef __TIMESERIE_H_INCLUDED__
#define __TIMESERIE_H_INCLUDED__

#include <vector>
#include <string>

using namespace std;

class Timeserie {
public:
    Timeserie (int id, vector<float> values);

    int id;

    vector<float> values;

    float operator[] (int i);

    static void PrintTimeseries(vector<Timeserie*> v);

    static vector<Timeserie*>* GetTimeseries(string s);

};

#endif
