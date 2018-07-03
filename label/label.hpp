#ifndef __LABEL_H_INCLUDED__
#define __LABEL_H_INCLUDED__

#include <string>
#include <vector>

using namespace std;

class Label {
public:
    Label (int id, string label);

    int id;

    string label;

    static void PrintLabels(vector<Label*> v);

    static vector<Label*> GetLabels(string s);
};

#endif
