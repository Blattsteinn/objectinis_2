#include "my_library.h"
#include "my_functions.h"

// -- Actions depending on userChoice -->

std::istream& operator>>(std::istream& in, Studentas& s) {
    string name, surname;
    vector<float> grades;
    int exam;

    cout << "Vardas: "; cin >> name;
    s.setVardas(name);

    cout << "Pavarde: "; cin >> surname;
    s.setPavarde(surname);

    // --- Read grades manually -----------------------------
            float grade;
            int track_grades = 1;
            cout << "[Pazymiu ivedimas] ivedant -1 nutraukiamas darbas" << std::endl;

            while (true) {
                string prompt = to_string(track_grades) + " pazymys: ";
                grade = check_the_value(prompt, "[Klaida] ivertinimo ribos nuo 1 iki 10", -1, 10);
    
                if (grade == -1) {
                    break;
                } else if (grade == 0) {
                    cout << "[Klaida] ivertinimo ribos nuo 1 iki 10" << std::endl;
                    continue;
                }

                track_grades++;
                grades.push_back(grade);
    }
    s.setGrades(grades);

    exam = check_the_value("Egzamino ivertinimas: ", "[Klaida] iveskite skaiciu nuo 1-10", 1, 10);
    s.setExam(exam);

    s.calculate_everything();

    return in;
}

Studentas userChoice_2() {
    Studentas s;
    string name, surname;
    vector<float> grades;
    int exam;

    cout << "Vardas: "; cin >> name;
    s.setVardas(name);

    cout << "Pavarde: "; cin >> surname;
    s.setPavarde(surname);

    // --- Get random grades -----------------------------  
    grades = random_grade();
            cout << "Gauti pazymiai: ";
            for(auto const &grade : grades){
                cout << grade << " ";
            }
            cout << endl;
    s.setGrades(grades);

    exam = randomNumber(1,10);
    s.setExam(exam);
    cout << "Sugeneruotas egzamino rezultatas: " << exam << endl;
    s.calculate_everything();

    return s;
}

Studentas userChoice_3() {
    Studentas s;
    string name, surname;
    vector<float> grades;
    int exam;

    name = random_name();
    s.setVardas(name);
    cout << "Sugeneruotas vardas: " << name << endl;

    surname = random_last_name();
    s.setPavarde(surname);
    cout << "Sugeneruota pavarde: " << surname << endl;


    // --- Get random grades -----------------------------  
    grades = random_grade();
            cout << "Gauti pazymiai: ";
            for(auto const &grade : grades){
                cout << grade << " ";
            }
            cout << endl;
    s.setGrades(grades);

    exam = randomNumber(1,10);
    s.setExam(exam);
    cout << "Sugeneruotas egzamino rezultatas: " << exam << endl;

    s.calculate_everything();

    return s;
}