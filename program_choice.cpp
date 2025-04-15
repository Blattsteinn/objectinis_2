#include "my_library.h"
#include "my_functions.h"

// -- Actions depending on userChoice -->

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