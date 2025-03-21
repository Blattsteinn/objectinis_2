#pragma once

#include "my_library.h"

class Studentas {
    private:
    string vardas;
    string pavarde;
    
    int egzaminoRezultatas;

    public:

    vector<float> pazymiai;

    
    float galutinisVid;
    float galutinisMed;

    // Default constructor: initializes members to default values.
    Studentas()
        : vardas(""), pavarde(""), egzaminoRezultatas(0),
          galutinisVid(0.0f), galutinisMed(0.0f) {}

    // Parameterized constructor: initializes with provided values and calculates final scores.
    Studentas(const string& vardas, const string& pavarde, const vector<float>& pazymiai, int egzaminoRezultatas)
        : vardas(vardas), pavarde(pavarde), pazymiai(pazymiai), egzaminoRezultatas(egzaminoRezultatas) {
        calculate_everything();
    }

    void initializeVardas(int i);
    void initializePavarde(int i);

    void initializeExam(int i);

    // Getters
    string getVardas() const { return vardas; }
    string getPavarde() const { return pavarde; }
    vector<float> getPazymiai() const { return pazymiai; }
    int getEgzaminoRezultatas() const { return egzaminoRezultatas; }
    float getGalutinisVid() const { return galutinisVid; }
    float getGalutinisMed() const { return galutinisMed; }


    // Member functions
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