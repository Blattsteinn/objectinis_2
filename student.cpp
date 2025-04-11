#include "my_library.h"
#include "student.h"

#include "my_functions.h"


    // Copy constructor
    Studentas::Studentas(const Studentas& other): 
        vardas{other.vardas},
        pavarde{other.pavarde},
        pazymiai{other.pazymiai},
        egzaminoRezultatas{other.egzaminoRezultatas},
        galutinisVid{other.galutinisVid},
        galutinisMed{other.galutinisMed}
    {

    }

    // Move constructor
    Studentas::Studentas(Studentas&& other) noexcept:   // guaranteed not to throw any exceptions
        vardas{std::move(other.vardas)},
        pavarde{std::move(other.pavarde)},
        pazymiai{std::move(other.pazymiai)},
        egzaminoRezultatas{other.egzaminoRezultatas},
        galutinisVid{other.galutinisVid},
        galutinisMed{other.galutinisMed}
    {

    }

    // Copy constructor operator
    Studentas& Studentas::operator=(const Studentas& other) {
        
        if(&other != this){

        vardas = other.vardas;
        pavarde = other.pavarde;
        pazymiai = other.pazymiai;
        egzaminoRezultatas = other.egzaminoRezultatas;
        galutinisVid = other.galutinisVid;
        galutinisMed = other.galutinisMed;
        }
        return *this;
    }

    // Move constructor operator
    Studentas& Studentas::operator=(Studentas&& other){
        if(&other != this){
            vardas = std::move(other.vardas);
            pavarde = std::move(other.pavarde);
            pazymiai = std::move(other.pazymiai);

            egzaminoRezultatas = other.egzaminoRezultatas;
            galutinisVid = other.galutinisVid;
            galutinisMed = other.galutinisMed;

            other.egzaminoRezultatas = 0;
            other.galutinisVid = 0.0f;
            other.galutinisMed = 0.0f;
        }
        return *this;
    }
    
        // --- Calculation functions    
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

    float Studentas::calculateMedian() {
        if (pazymiai.empty()) {
            cout << "[Klaida] Negalima apskaiciuoti vidurkio, nes nera ivertinimu. Mediana - 0" << endl;
            return 0;
        }
        
        sort(pazymiai.begin(), pazymiai.end());
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