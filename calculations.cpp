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

// --- calculates final score for average & median
    void calculate_everything(Studentas &temp){
        temp.galutinisVid = average(temp) * 0.4 + temp.egzaminoRezultatas *0.6;
        temp.galutinisMed = median<StudentContainer>(temp) * 0.4 + temp.egzaminoRezultatas *0.6;

    }

// --- checks whenever a value is within a needed range
    int check_the_value(string message, string errorMessage,int minVal,int maxVal){
        while (true)
        {
            cout << message;
            int value; 
            if (!(cin >> value)){  // <-- if cin fails
                cout << errorMessage << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;  // <-- prompt back again
            }

            if (value < minVal || value > maxVal){  // <-- if the number is not within the given range 
                cout << errorMessage << endl;
                continue;  // <-- prompt back again
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }

// --- returns a menu
    string consoleText_userChoice() {
        return R"(
            [Programos eigos pasirinkimas]
            
    1 - rankinis ivedimas, 
    2 - generuoti pazymius, 
    3 - generuoti ir pazymius, ir studentu vardus, pavardes, 
    4 - nuskaityti duomenis is failo, 
    5 - baigti darba

    6 - failu generavimas
    7 - testavimas

                [Pasirinkimas]: )";
    }

// --- returns a random number within wanted range a <= x <= b;
    int randomNumber(int a, int b) {
        static std::mt19937 gen{std::random_device{}()}; // paleidziama tik karta
        std::uniform_int_distribution<int> distr(a, b);
        return distr(gen);
    }
