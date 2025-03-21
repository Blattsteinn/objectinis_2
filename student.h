#pragma once

#include "my_library.h"

class Studentas {
    public:
    string vardas;
    string pavarde;
    
    vector<float> pazymiai;
    int egzaminoRezultatas;
    
    float galutinisVid;
    float galutinisMed;


    void sortGrades();
    float calculateMean();
	float calculateMedian();
    void calculate_everything();

    friend ostream& operator<<(ostream &out, Studentas &s) {
        out << left << setw(15) << s.pavarde
            << setw(15) << s.vardas
            << fixed << setprecision(2) << setw(22) << s.galutinisVid
            << fixed << setprecision(2) << setw(15) << s.galutinisMed
            << "\n";
        return out;
    }
};