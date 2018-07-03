#include "util.hpp"
#include <cmath>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

template<typename Out>
void split(const string &s, char delim, Out result) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        *(result++) = item;
    }
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, back_inserter(elems));
    return elems;
}

/*
* O(1)
*/
float dist(float x, float y) {
    return abs(x - y);
}
