#include "label.hpp"
#include "../util/util.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>


using namespace std;

Label::Label(int id, string label) {
    this->id = id;
    this->label = label;
}

void Label::PrintLabels(vector<Label*> v) {
    for(vector<Label*>::iterator it = v.begin(); it != v.end(); ++it) {
        cout << (*it)->id << "\t" << (*it)->label << endl;
    }
}


vector<Label*> Label::GetLabels(string s) {
    string line;
    ifstream label ("data/" + s + ".txt");
    vector<Label*> labels;

    if(label.is_open()) {
        vector<string> v;
        while(getline(label, line)) {
            v = split(line, '\t');
            labels.push_back(new Label(stoi(v[0]), v[1]));
            v.clear();
        }
    }
    label.close();
    return labels;
}
