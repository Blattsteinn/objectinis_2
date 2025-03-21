#pragma once

#include "my_library.h"
#include "my_functions.h"

// -- Outputs students into a console (generally avoid this function)
    template <typename Container>
    void print_students(Container &studentas){

        // Create an output string stream
        std::ostringstream buffer;

            buffer <<'\n' 
            << left << setw(15) << "Pavarde" 
            << setw(15) << "Vardas" 
            << setw(15) << "Galutinis (Vid.)  /  " 
            << setw(15) << "Galutinis (Med.)" 
            << "\n-------------------------------------------------------------\n";

        for (auto& s : studentas) {
            buffer << s;
        }

        // Print the entire buffered content at once
        cout << buffer.str();
    }

// --- Inserts a student into container<Studentas>  ---
    template <typename Container>
    void insert_student(Container &student_list, Studentas &student){
        Studentas temp = student; // Copy the student
        student_list.push_back(temp);
    }


// --- Manual user entry for grades ---
    template <template<typename, typename...> class Container>
    Container<float> enter_grades_manually() {
        Container<float> grades;  // <--- This is a container of floats
        float grade;
        int track_grades = 1;

        std::cout << "[Pazymiu ivedimas] ivedant -1 nutraukiamas darbas" << std::endl;
        while (true) {
            std::string prompt = std::to_string(track_grades) + " pazymys: ";
            grade = check_the_value(prompt, "[Klaida] ivertinimo ribos nuo 1 iki 10", -1, 10);

            if (grade == -1) {
                break;
            } else if (grade == 0) {
                std::cout << "[Klaida] ivertinimo ribos nuo 1 iki 10" << std::endl;
                continue;
            }

            track_grades++;
            grades.push_back(grade);
        }

        return grades;
    }


// ---------- Sort functions for std::vector & std::deque ----------

    // --- Sorts students depending on user input  ---
    template <typename Container>
    void sort_students(Container &student_list) {
        std::string rikiavimo_pasirinkimas = R"([Rikiavimo pasirinkimas]
        1 - rikiuoti pagal vardus (abeceliskai), 
        2 - rikiuoti pagal pavardes (abeceliskai),
        3 - rikiuoti pagal vidurki (didejant),
        4 - rikiuoti pagal mediana (didejant),
                [Pasirinkimas]: )";
        
        int choice = check_the_value(rikiavimo_pasirinkimas, "[Klaida] Pasirinkite skaiciu tarp [1-4]", 1, 4);

        switch (choice) {
            case 1:
                sort(student_list.begin(), student_list.end(),
                        [](const Studentas &a, const Studentas &b) { return a.vardas < b.vardas; });
                break;
            case 2:
                sort(student_list.begin(), student_list.end(),
                        [](const Studentas &a, const Studentas &b) { return a.pavarde < b.pavarde; });
                break;
            case 3:
                sort(student_list.begin(), student_list.end(),
                        [](const Studentas &a, const Studentas &b) { return a.galutinisVid < b.galutinisVid; });
                break;
            case 4:
                sort( student_list.begin(), student_list.end(),
                        [](const Studentas &a, const Studentas &b) { return a.galutinisMed < b.galutinisMed; });
                break;
            default:
                break;
        }
    }

    // --- Sorts students depending on the function paramater ---
    template <typename Container>
    void sort_students(Container &student_list, int choice) {

    switch (choice) {
        case 1:
            sort(student_list.begin(), student_list.end(),
                      [](const Studentas &a, const Studentas &b) { return a.vardas < b.vardas; });
            break;
        case 2:
            sort(student_list.begin(), student_list.end(),
                      [](const Studentas &a, const Studentas &b) { return a.pavarde < b.pavarde; });
            break;
        case 3:
            sort(student_list.begin(), student_list.end(),
                      [](const Studentas &a, const Studentas &b) { return a.galutinisVid < b.galutinisVid; });
            break;
        case 4:
            sort( student_list.begin(), student_list.end(),
                      [](const Studentas &a, const Studentas &b) { return a.galutinisMed < b.galutinisMed; });
            break;
        default:
            break;
    }
}


// ---------- Exact same functions as above just for for std::list ----------

    template <>
    inline void sort_students<std::list<Studentas>>(std::list<Studentas> &student_list) {

        std::string rikiavimo_pasirinkimas = R"([Rikiavimo pasirinkimas]
        1 - rikiuoti pagal vardus (abeceliskai), 
        2 - rikiuoti pagal pavardes (abeceliskai),
        3 - rikiuoti pagal vidurki (didejant),
        4 - rikiuoti pagal mediana (didejant),
                [Pasirinkimas]: )";
        
        int choice = check_the_value(rikiavimo_pasirinkimas, "[Klaida] Pasirinkite skaiciu tarp [1-4]", 1, 4);
        
        switch (choice) {
            case 1:
                student_list.sort([](const Studentas &a, const Studentas &b) { return a.vardas < b.vardas; });
                break;
            case 2:
                student_list.sort([](const Studentas &a, const Studentas &b) { return a.pavarde < b.pavarde; });
                break;
            case 3:
                student_list.sort([](const Studentas &a, const Studentas &b) { return a.galutinisVid < b.galutinisVid; });
                break;
            case 4:
                student_list.sort([](const Studentas &a, const Studentas &b) { return a.galutinisMed < b.galutinisMed; });
                break;
            default:
                break;
        }
    }

    template <>
    inline void sort_students<std::list<Studentas>>(std::list<Studentas> &student_list, int choice) {
        switch (choice) {
            case 1:
                student_list.sort([](const Studentas &a, const Studentas &b) { return a.vardas < b.vardas; });
                break;
            case 2:
                student_list.sort([](const Studentas &a, const Studentas &b) { return a.pavarde < b.pavarde; });
                break;
            case 3:
                student_list.sort([](const Studentas &a, const Studentas &b) { return a.galutinisVid < b.galutinisVid; });
                break;
            case 4:
                student_list.sort([](const Studentas &a, const Studentas &b) { return a.galutinisMed < b.galutinisMed; });
                break;
            default:
                break;
        }
    }
