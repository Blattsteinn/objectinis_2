#include "my_library.h"
#include "my_functions.h"

// --- calculates the average score
    float average(Studentas temp){
        float sum = 0;
        float vidurkis = 0;

        if(temp.pazymiai.size() == 0 ) {
            cout << "[Klaida] Negalima apskaiciuoti vidurkio, nes nera ivertinimu. Vidurkis - 0" << endl;
            return 0;
        }

        sum = accumulate(temp.pazymiai.begin(), temp.pazymiai.end(), 0);

        vidurkis = sum/temp.pazymiai.size();
        return vidurkis;

    }

// --- calculates median
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

// --- calculates final score for average & median
    void calculate_everything(Studentas &temp){
        temp.galutinisVid = average(temp) * 0.4 + temp.egzaminoRezultatas *0.6;
        temp.galutinisMed = median(temp) * 0.4 + temp.egzaminoRezultatas *0.6;

    }

// --- sort for std::vector & std::list
    void sortGrades(vector<float>& grades) {
        std::sort(grades.begin(), grades.end());
    }