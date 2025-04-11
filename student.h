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
    
    // Copy constructor
    Studentas(const Studentas& other): 
        vardas{other.vardas},
        pavarde{other.pavarde},
        pazymiai{other.pazymiai},
        egzaminoRezultatas{other.egzaminoRezultatas},
        galutinisVid{other.galutinisVid},
        galutinisMed{other.galutinisMed}
    {

    }

    // Move constructor
    Studentas(Studentas&& other) noexcept:   // guaranteed not to throw any exceptions
        vardas{std::move(other.vardas)},
        pavarde{std::move(other.pavarde)},
        pazymiai{std::move(other.pazymiai)},
        egzaminoRezultatas{other.egzaminoRezultatas},
        galutinisVid{other.galutinisVid},
        galutinisMed{other.galutinisMed}
    {
        // Optionally, you might reset other members if needed.
    }

    // Setters
    void setVardas(const string& v) { vardas = v; }
    void setPavarde(const string& p) { pavarde = p; }
    void setGrades(const vector<float>& g) { pazymiai = g; }
    void setExam(int exam) { egzaminoRezultatas = exam; }

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
    friend ostream& operator<<(ostream &out, const Studentas &s) {
        out << left << setw(15) << s.pavarde
            << setw(15) << s.vardas
            << fixed << setprecision(2) << setw(22) << s.galutinisVid
            << fixed << setprecision(2) << setw(15) << s.galutinisMed
            << "\n";
        return out;
    }
    
};