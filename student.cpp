#include "my_library.h"
#include "student.h"

    void Studentas::sortGrades() {
    sort(pazymiai.begin(), pazymiai.end());
}

    // --- calculates the average score
    float Studentas::calculateMean(){
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
    float Studentas::calculateMedian() {
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

    void Studentas::calculate_everything(){
        galutinisVid = calculateMean() * 0.4 + egzaminoRezultatas *0.6;
        galutinisMed = calculateMedian() * 0.4 + egzaminoRezultatas *0.6;

    }

