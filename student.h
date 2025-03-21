#pragma once

#include "my_library.h"

class Studentas {
    private:
    string vardas;
    string pavarde;

    vector<float> pazymiai;
    int egzaminoRezultatas;

    float galutinisVid;
    float galutinisMed;

    public:

    // Default constructor
    Studentas()
        : vardas(""), pavarde(""), egzaminoRezultatas(0),
          galutinisVid(0.0f), galutinisMed(0.0f) {}

    // Parameterized constructor
    Studentas(const string& vardas, const string& pavarde, const vector<float>& pazymiai, int egzaminoRezultatas)
        : vardas(vardas), pavarde(pavarde), pazymiai(pazymiai), egzaminoRezultatas(egzaminoRezultatas) {
        calculate_everything();
    }

    // Destructor
    ~Studentas() {
        vardas.clear();
        pavarde.clear();
        pazymiai.clear();

        egzaminoRezultatas = 0;
        galutinisVid = 0.0f;
        galutinisMed = 0.0f;
    }
    

    // Initializations
    void initializeVardas(int i);
    void initializePavarde(int i);

    void initializeGrades(int i);
    void initializeExam(int i);


    // Getters
    string getVardas() const { return vardas; }
    string getPavarde() const { return pavarde; }
    vector<float> getPazymiai() const { return pazymiai; }
    int getEgzaminoRezultatas() const { return egzaminoRezultatas; }
    float getGalutinisVid() const { return galutinisVid; }
    float getGalutinisMed() const { return galutinisMed; }


    // Member functions
    float calculateMean();
	float calculateMedian();
    void calculate_everything();  // Calls both calculateMean and calculateMedian and assigns them.


    // Friend function for easier printing
    friend ostream& operator<<(ostream &out, Studentas &s) {
        out << left << setw(15) << s.pavarde
            << setw(15) << s.vardas
            << fixed << setprecision(2) << setw(22) << s.galutinisVid
            << fixed << setprecision(2) << setw(15) << s.galutinisMed
            << "\n";
        return out;
    }
};