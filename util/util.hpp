#ifndef __UTIL_H_INCLUDED__
#define __UTIL_H_INCLUDED__

#include <vector>
#include <string>

using namespace std;

template<typename Out>
void split(const string &s, char delim, Out result);

vector<string> split(const string &s, char delim);

float dist(float x, float y);

#endif
