#pragma once

#include "my_library.h"
#include "my_functions.h"

//---------------------- Median calculation

// --- sort for std::vector & std::list
    template<typename Container>
    void sortGrades(Container& grades) {
        std::sort(grades.begin(), grades.end());
    }

// --- sort for std::list<float>
    inline void sortGrades(std::list<float>& grades) {
        grades.sort();
    }

// --- calculates median
    template<template<typename, typename...> class Container>
    float median(Studentas temp) {
        float mediana = 0; 
        if (temp.pazymiai.empty()) {
            cout << "[Klaida] Negalima apskaiciuoti vidurkio, nes nera ivertinimu. Mediana - 0" << endl;
            return 0;
        }

        // Use the helper function
        sortGrades(temp.pazymiai);

        int pazymiu_kiekis = temp.pazymiai.size();

        if(pazymiu_kiekis % 2 == 1) { // Odd number of elements
            // For non-list, you need to get the element via iterators
            auto it = temp.pazymiai.begin();
            std::advance(it, pazymiu_kiekis / 2);
            mediana = *it;
            return mediana;
        } else { // Even number of elements
            auto it1 = temp.pazymiai.begin();
            std::advance(it1, pazymiu_kiekis / 2);

            auto it2 = temp.pazymiai.begin();
            std::advance(it2, (pazymiu_kiekis / 2) - 1);

            mediana = (*it1 + *it2) / 2.0;
            return mediana;
        }
    }
