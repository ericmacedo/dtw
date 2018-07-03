#include "timeserie.hpp"
#include "../util/util.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

Timeserie::Timeserie(int id, vector<float> values) {
    this->id = id;
    this->values = values;
}


vector<Timeserie*>* Timeserie::GetTimeseries(string s) {
    string line;
    ifstream timeserie ("data/" + s + ".txt");
    vector<Timeserie*>* timeseries = new vector<Timeserie*>();

    if(timeserie.is_open()) {
        vector<string> v;
        vector<float> timeserieValues;
        string id;

        while(getline(timeserie, line)) {
            v = split(line, ' ');

            for(vector<string>::iterator it = v.begin() + 1; it != v.end(); ++it) {
                timeserieValues.push_back(stof(*it));
            }

            timeseries->push_back(new Timeserie(stoi(v[0]), timeserieValues));

            timeserieValues.clear();
            v.clear();
        }
    }
    timeserie.close();
    return timeseries;
}

void Timeserie::PrintTimeseries(vector<Timeserie*> v) {
    for(vector<Timeserie*>::iterator i = v.begin(); i != v.end(); ++i) {
        cout << (*i)->id << " ";
        for(vector<float>::iterator j = (*i)->values.begin(); j != (*i)->values.end(); ++j) {
            cout << *j << " ";
        }
        cout << endl;
    }
}

float Timeserie::operator[] (int i) {
    return this->values[i];
}
