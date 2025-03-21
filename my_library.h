#pragma once

// --- Containers ---
#include <vector>
using std::vector;

#include <list>
using std::list;

#include <deque>
using std::deque;

template <typename T>
using StudentContainer = vector<T>;  // Can be changed to list<T> or deque<T> as needed.

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
struct Studentas {
    string vardas;
    string pavarde;
    
    StudentContainer<float> pazymiai;
    int egzaminoRezultatas;
    
    float galutinisVid;
    float galutinisMed;
    
    friend ostream& operator<<(ostream &out, Studentas &s) {
        out << left << setw(15) << s.pavarde
            << setw(15) << s.vardas
            << fixed << setprecision(2) << setw(22) << s.galutinisVid
            << fixed << setprecision(2) << setw(15) << s.galutinisMed
            << "\n";
        return out;
    }
};
