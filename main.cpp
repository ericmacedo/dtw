#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <string>
#include <fstream>
#include "label/label.hpp"
#include "timeserie/timeserie.hpp"
#include "util/util.hpp"
#include "dtw/dtw.hpp"

using namespace std;


int main (int argc, char **argv) {

    ofstream output_sc;
    ofstream output_sc3D;

    if(*argv[1] == '2' || *argv[1] == '0') {
        output_sc.open("results/S_C.txt");
        output_sc3D.open("results/S_C3D.txt");
    }

    // vector<Label*> labels = Label::GetLabels("rotulos");
    // vector<Label*> labels3D = Label::GetLabels("rotulos3D");

    vector<Timeserie*>* tests;
    vector<Timeserie*>* trains;

    DTW* dtw_tests;

    if(*argv[1] == '1' || *argv[1] == '2' || *argv[1] == '0') {
        tests = Timeserie::GetTimeseries("teste");
        trains = Timeserie::GetTimeseries("treino");

        dtw_tests = new DTW(tests, trains, "Tests");
    }

    vector<Timeserie*>* tests3D = Timeserie::GetTimeseries("teste3D");
    vector<Timeserie*>* trains3D = Timeserie::GetTimeseries("treino3D");

    DTW* dtw_tests3D = new DTW(tests3D, trains3D, "Tests3D");

    // SIMPLE DTW -- PART 1
    if(*argv[1] == '1' || *argv[1] == '0') {
        dtw_tests->Start(); // 1D

        cout << endl;

        dtw_tests3D->Start(); // 3D

        cout << endl;
    }

    // SAKOE-SHIBA BAND CONSTRAINT -- PART 2
    if(*argv[1] == '2' || *argv[1] == '0') {
        for(int i = 0; i <= 100; i++) { // 1D
            dtw_tests->Start(i);
            output_sc << i << " " << (float) ((float) dtw_tests->scores / dtw_tests->n) * 100.00 << " " << dtw_tests->deltaTime << endl;
        }

        output_sc.close();

        cout << "Results writen in ./results/S_C.txt" << endl;
        cout << endl;

        // -----

        for(int i = 0; i <= 100; i++) { // 3D
            dtw_tests3D->Start(i);
            output_sc3D << i << " " << (float) ((float) dtw_tests3D->scores / dtw_tests3D->n) * 100.00 << " " << dtw_tests3D->deltaTime << endl;
        }

        output_sc3D.close();

        cout << "Results writen in ./results/S_C3D.txt" << endl;
        cout << endl;
    }

    if(*argv[1] == '1' || *argv[1] == '2' || *argv[1] == '0') {
        // 1D WON'T BE USED ANYMORE
        delete dtw_tests;
    }

    // PART 3

    if(*argv[1] == '3' || *argv[1] == '0') {

        dtw_tests3D->Start("DTW_D");

        dtw_tests3D->Start("DTW_i");
    }

    delete dtw_tests3D;

    // FINISHED
}
