#pragma once



// --- Containers ---
#include <vector>
using std::vector;

// --- I/O Streams ---
#include <iostream>
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::ostream;
using std::ios;

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <sstream>
using std::istringstream;
using std::ostringstream;

// --- String and Formatting ---
#include <string>
using std::string;
using std::to_string;

#include <iomanip>
using std::setw;
using std::fixed;
using std::setprecision;
using std::left;

// --- Algorithms and Iterators ---
#include <algorithm>
using std::sort;

#include <iterator>
using std::istream_iterator;

// --- Numeric Utilities ---
#include <limits>
using std::numeric_limits;
using std::streamsize;

#include <numeric>
using std::accumulate;

// --- Random Number Generation ---
#include <random>
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

// --- Math ---
#include <cmath>

// --- Time Utilities ---
#include <chrono>
using std::chrono::high_resolution_clock;
using std::chrono::duration;

#include <filesystem>

// --- The Student Structure ---
class Studentas {
    public:
    string vardas;
    string pavarde;
    
    vector<float> pazymiai;
    int egzaminoRezultatas;
    
    float galutinisVid;
    float galutinisMed;

    // --- sort for std::vector & std::list
    void sortGrades() {
        sort(pazymiai.begin(), pazymiai.end());
    }

        // --- calculates the average score
        float calculateMean(){
            float sum = 0;
            float vidurkis = 0;
    
            if(pazymiai.size() == 0 ) {
                cout << "[Klaida] Negalima apskaiciuoti vidurkio, nes nera ivertinimu. Vidurkis - 0" << endl;
                return 0;
            }
    
            sum = accumulate(pazymiai.begin(), pazymiai.end(), 0);
    
            vidurkis = sum/pazymiai.size();
            return vidurkis;
    
        }
    
        // --- calculates median
        float calculateMedian() {
            if (pazymiai.empty()) {
                cout << "[Klaida] Negalima apskaiciuoti vidurkio, nes nera ivertinimu. Mediana - 0" << endl;
                return 0;
            }
            
            sortGrades();
            size_t n = pazymiai.size();
            
            if (n % 2 != 0) {
                return pazymiai[n / 2];
            } else {
                return (pazymiai[n / 2] + pazymiai[n / 2 - 1]) / 2.0;
            }
            
        }
    
        void calculate_everything(){
            galutinisVid = calculateMean() * 0.4 + egzaminoRezultatas *0.6;
            galutinisMed = calculateMedian() * 0.4 + egzaminoRezultatas *0.6;
    
        }
    
    
    friend ostream& operator<<(ostream &out, Studentas &s) {
        out << left << setw(15) << s.pavarde
            << setw(15) << s.vardas
            << fixed << setprecision(2) << setw(22) << s.galutinisVid
            << fixed << setprecision(2) << setw(15) << s.galutinisMed
            << "\n";
        return out;
    }
};