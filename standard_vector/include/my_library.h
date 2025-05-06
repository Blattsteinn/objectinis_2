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