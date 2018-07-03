#include <vector>
#include <string>
#include <ctime>
#include <limits>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include "../label/label.hpp"
#include "../timeserie/timeserie.hpp"
#include "../util/util.hpp"
#include "dtw.hpp"

using namespace std;

/*
* ESTIMATED COMPLEXITY
* O(1)
*/
DTW::DTW(vector<Timeserie*>*& tests, vector<Timeserie*>*& trains, string s) {
    this->tests = tests;
    this->n = tests->size();

    this->trains = trains;
    this->m = trains->size();

    this->scores = 0;

    this->name = s;
}

/*
* ESTIMATED COMPLEXITY
* O(n * m * (n * m)) = O(n²m²)
*/
void DTW::Start() {
    this->scores = 0;

    this->startTime = clock ();
    cout << "Initializing " << this->name << endl;
    for(int i = 0; i < this->n; i++) {  // O(n)
        int currentMinimunIndex;
        float currentDistance = numeric_limits<float>::infinity();
        float optDistance;

        for(int j = 0; j < this->m; j++) {  // O(m)
            cout << "\rCurrent test: " << i << " " << j;
            optDistance = this->OPT((*this->tests)[i], (*this->trains)[j]);  // O(nm)
            if(optDistance < currentDistance) {
                currentMinimunIndex = j;
                currentDistance = optDistance;
            }
        }

        if((*this->tests)[i]->id == (*this->trains)[currentMinimunIndex]->id){
            this->scores++;
        }
    }

    this->deltaTime = (clock () - this->startTime)/CLOCKS_PER_SEC;
    cout << endl << "Finished with " << this->deltaTime << "s" << endl;

    cout << "Score: " << this->scores << "/" << this->n << " hits ";
    cout << "(" << setprecision(4) << (float) ((float) this->scores / this->n) * 100.00 << "%)" << endl;
}

/*
* ESTIMATED COMPLEXITY
* O(n * m * (n * m * r)) = O(n²m²r)
*/
void DTW::Start(int w) {
    this->scores = 0;

    this->startTime = clock ();
    cout << "\rInitializing " << this->name << " with " << w << "% of S-C Band width." << endl;
    for(int i = 0; i < this->n; i++) {  // O(n)
        int currentMinimunIndex;
        float currentDistance = numeric_limits<float>::infinity();
        float optDistance;

        for(int j = 0; j < this->m; j++) {  // O(m)
            optDistance = this->OPT((*this->tests)[i], (*this->trains)[j], w); // O(nmr)
            if(optDistance < currentDistance) {
                currentMinimunIndex = j;
                currentDistance = optDistance;
            }
        }

        if((*this->tests)[i]->id == (*this->trains)[currentMinimunIndex]->id){
            this->scores++;
        }
    }

    this->deltaTime = (clock () - this->startTime)/CLOCKS_PER_SEC;
    cout << endl << "Finished with " << this->deltaTime << "s" << endl;

    cout << "Score: " << this->scores << "/" << this->n << " hits ";
    cout << "(" << setprecision(4) << (float) ((float) this->scores / this->n) * 100.00 << "%)" << endl;
}


/*
* ESTIMATED COMPLEXITY
* O(n * m * (n + m + (n/3 * m/3)) = O(n²m²)
*/
void DTW::Start(string opt) {
    this->scores = 0;

    this->startTime = clock ();
    cout << "Initializing " << this->name << " with " << opt << endl;
    for(int i = 0; i < this->n; i++) {  // O(n)
        int currentMinimunIndex;
        float currentDistance = numeric_limits<float>::infinity();
        float optDistance;

        for(int j = 0; j < this->m; j++) {  // O(m)
            cout << "\rCurrent test: " << i << " " << j;
            if(opt == "DTW_D") {
                optDistance = this->OPT_D((*this->tests)[i], (*this->trains)[j]);  // O(n + m + n/3 * m/3) = O(nm)
            } else {
                optDistance = this->OPT_I((*this->tests)[i], (*this->trains)[j]);  // O(n + m + n/3 * m/3) = O(nm)
            }
            if(optDistance < currentDistance) {
                currentMinimunIndex = j;
                currentDistance = optDistance;
            }
        }

        if((*this->tests)[i]->id == (*this->trains)[currentMinimunIndex]->id){
            this->scores++;
        }
    }

    this->deltaTime = (clock () - this->startTime)/CLOCKS_PER_SEC;
    cout << endl << "Finished with " << this->deltaTime << "s" << endl;

    cout << "Score: " << this->scores << "/" << this->n << " hits ";
    cout << "(" << setprecision(4) << (float) ((float) this->scores / this->n) * 100.00 << "%)" << endl;
}

/*
* ESTIMATED COMPLEXITY
* O(n + m + n * m + n) = O(nm)
*/
float DTW::OPT(Timeserie* x, Timeserie* y) {
    int n = x->values.size();
    int m = y->values.size();
    float** M;

    M = new float*[n];
    for(int i = 0; i < n; i++) {  // O(n)
        M[i] = new float[m];
        M[i][0] = numeric_limits<float>::infinity();
    }

    for(int j = 0; j < m; j++) {  // O(m)
        M[0][j] = numeric_limits<float>::infinity();
    }

    M[0][0] = 0;

    // O(nm)
    for(int i = 1; i < n; i++) {  // O(n)
        for(int j = 1; j < m; j++) {  // O(m)
            M[i][j] =
                dist((*x)[i], (*y)[j]) +
                min(
                    M[i - 1][j],
                    min(
                        M[i][j - 1],
                        M[i - 1][j - 1]
                    )
                );
        }
    }

    float value = M[n - 1][m - 1];

    for(int i = 0; i < n; i++) {  // O(n)
        delete [] M[i];
    }
    delete [] M;
    return value;
}

/*
* ESTIMATED COMPLEXITY
* O(nm + n * m * r) = O(nmr)
*/
float DTW::OPT(Timeserie* x, Timeserie* y, int w) {
    int n = x->values.size();
    int m = y->values.size();
    float** M;

    int W = (int) ((float) m * ((float) w / 100.00));

    M = new float*[n];
    // O(nm)
    for(int i = 0; i < n; i++) {  //O(n)
        M[i] = new float[m];
        for(int j = 0; j < m; j++) {  // O(m)
            M[i][j] = numeric_limits<float>::infinity();
        }
    }

    M[0][0] = 0;

    // O(nmr)
    for(int i = 1; i < n; i++) {  // O(n)
        int windowStart = max(1, (int) i - W);
        int windowEnd   = min(m - 1, (int) i + W);
        for(int j = windowStart; j <= windowEnd; j++) { // O(mr)
            M[i][j] =
                dist((*x)[i], (*y)[j]) +
                min(
                    M[i - 1][j],
                    min(
                        M[i][j - 1],
                        M[i - 1][j - 1]
                    )
                );
        }
    }

    float value = M[n - 1][m - 1];

    for(int i = 0; i < n; i++) {  // O(n)
        delete [] M[i];
    }
    delete [] M;
    return value;
}

/*
* ESTIMATED COMPLEXITY
* O(n + m + n/3 + m/3 + n/3 * m/3 + n/3) = O(nm)
*/
float DTW::OPT_D(Timeserie* x, Timeserie* y) {
    int n = x->values.size();
    int m = y->values.size();

    float* x1   = new float[n/3];
    float* x2   = new float[n/3];
    float* x3   = new float[n/3];

    float* y1   = new float[m/3];
    float* y2   = new float[m/3];
    float* y3   = new float[m/3];

    int count = 0;
    for(int i = 0; i <= n - 3; i = i + 3) {  // O(n)
        x1[count] = (*x)[i];
        x2[count] = (*x)[i + 1];
        x3[count] = (*x)[i + 2];
        count++;
    }

    count = 0;
    for(int i = 0; i <= m - 3; i = i + 3) { // O(m)
        y1[count] = (*y)[i];
        y2[count] = (*y)[i + 1];
        y3[count] = (*y)[i + 2];
        count++;
    }

    float** M   = new float*[n/3];
    for(int i = 0; i < n/3; i++) {  // O(n)
        M[i] = new float[m/3];
        M[i][0] = numeric_limits<float>::infinity();
    }

    for(int j = 0; j < m/3; j++) {  // O(m)
        M[0][j] = numeric_limits<float>::infinity();
    }

    M[0][0] = 0;

    // O(nm)
    for(int i = 1; i < n/3; i++) {  // O(n)
        for(int j = 1; j < m/3; j++) {  // O(m)
            M[i][j] =
                (
                    dist(x1[i], y1[j]) +
                    dist(x2[i], y2[j]) +
                    dist(x3[i], y3[j])
                ) +
                min(
                    M[i - 1][j],
                    min(
                        M[i][j - 1],
                        M[i - 1][j - 1]
                    )
                );
        }
    }

    float value = M[(n/3) - 1][(m/3) - 1];

    // --------

    delete [] x1;
    delete [] x2;
    delete [] x3;

    delete [] y1;
    delete [] y2;
    delete [] y3;

    for(int i = 0; i < n/3; i++) {  // O(n)
        delete [] M[i];
    }
    delete [] M;

    return value;
}

/*
* ESTIMATED COMPLEXITY
* O(n + m + n/3 + m/3 + n/3 * m/3 + n/3) = O(nm)
*/
float DTW::OPT_I(Timeserie* x, Timeserie* y) {
    int n = x->values.size();
    int m = y->values.size();

    float* x1   = new float[n/3];
    float* x2   = new float[n/3];
    float* x3   = new float[n/3];

    float* y1   = new float[m/3];
    float* y2   = new float[m/3];
    float* y3   = new float[m/3];

    int count = 0;
    for(int i = 0; i <= n - 3; i = i + 3) {  // O(n)
        x1[count] = (*x)[i];
        x2[count] = (*x)[i + 1];
        x3[count] = (*x)[i + 2];
        count++;
    }

    count = 0;
    for(int i = 0; i <= m - 3; i = i + 3) {  // O(m)
        y1[count] = (*y)[i];
        y2[count] = (*y)[i + 1];
        y3[count] = (*y)[i + 2];
        count++;
    }

    float** M   = new float*[n/3];
    float** Mx  = new float*[n/3];
    float** My  = new float*[n/3];
    float** Mz  = new float*[n/3];

    for(int i = 0; i < n/3; i++) {  // O(n)
        M[i] = new float[m/3];
        M[i][0] = numeric_limits<float>::infinity();
        Mx[i] = new float[m/3];
        Mx[i][0] = numeric_limits<float>::infinity();
        My[i] = new float[m/3];
        My[i][0] = numeric_limits<float>::infinity();
        Mz[i] = new float[m/3];
        Mz[i][0] = numeric_limits<float>::infinity();
    }

    for(int j = 0; j < m/3; j++) {  // O(m)
        M[0][j] = numeric_limits<float>::infinity();
        Mx[0][j] = numeric_limits<float>::infinity();
        My[0][j] = numeric_limits<float>::infinity();
        Mz[0][j] = numeric_limits<float>::infinity();
    }

    M[0][0] = 0;
    Mx[0][0] = 0;
    My[0][0] = 0;
    Mz[0][0] = 0;

    // O(nm)
    for(int i = 1; i < n/3; i++) {  // O(n)
        for(int j = 1; j < m/3; j++) {  // O(m)
            Mx[i][j] =
                dist(x1[i], y1[j]) +
                min(
                    Mx[i - 1][j],
                    min(
                        Mx[i][j - 1],
                        Mx[i - 1][j - 1]
                    )
                );
            Mx[i][j] =
                dist(x2[i], y2[j]) +
                min(
                    My[i - 1][j],
                    min(
                        My[i][j - 1],
                        My[i - 1][j - 1]
                    )
                );
            Mz[i][j] =
                dist(x3[i], y3[j]) +
                min(
                    Mz[i - 1][j],
                    min(
                        Mz[i][j - 1],
                        Mz[i - 1][j - 1]
                    )
                );
            M[i][j] = Mx[i][j] + My[i][j] + Mz[i][j];
        }
    }

    float value = M[(n/3) - 1][(m/3) - 1];

    // --------

    delete [] x1;
    delete [] x2;
    delete [] x3;

    delete [] y1;
    delete [] y2;
    delete [] y3;

    for(int i = 0; i < n/3; i++) {  // O(n)
        delete [] Mx[i];
        delete [] My[i];
        delete [] Mz[i];
        delete [] M[i];
    }
    delete [] M;
    delete [] Mx;
    delete [] My;
    delete [] Mz;
    return value;
}
