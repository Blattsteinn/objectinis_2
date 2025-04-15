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
       // cout << "Destruktorius iskviestas" << endl;
    }
    
    // Copy constructor
    Studentas(const Studentas& other);

    // Move constructor
    Studentas(Studentas&& other) noexcept;
    
    // Copy constructor operator
    Studentas& operator=(const Studentas& other);

    // Move constructor operator
    Studentas& operator=(Studentas&& other);


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


    // Friend function for printing
    friend ostream& operator<<(ostream &out, const Studentas &s);

    // Friend function for input
    friend std::istream& operator>>(std::istream& in, Studentas& s);

    // File functions 
    static void appendingContainerViaFile(string file_name, vector <Studentas> &student_list);
    static vector<Studentas> read_student_records(int ndCount, std::istringstream& iss);
    static void print_to_file(vector<Studentas> list_of_students, string file_name);
};

