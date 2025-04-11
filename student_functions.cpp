#include "my_library.h"
#include "my_functions.h"


// -- Outputs students into a console (generally avoid this function)
    void print_students(vector<Studentas> &studentas){

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
    void insert_student(vector<Studentas> &student_list, Studentas &student){
        student_list.push_back(std::move(student));
    }
// ---------- Sort functions for std::vector & std::deque ----------

    // --- Sorts students depending on user input  ---
    void sort_students(vector<Studentas> &student_list) {
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
                        [](const Studentas &a, const Studentas &b) { return a.getVardas() < b.getVardas(); });
                break;
            case 2:
                sort(student_list.begin(), student_list.end(),
                        [](const Studentas &a, const Studentas &b) { return a.getPavarde() < b.getPavarde(); });
                break;
            case 3:
                sort(student_list.begin(), student_list.end(),
                        [](const Studentas &a, const Studentas &b) { return a.getGalutinisVid() < b.getGalutinisVid(); });
                break;
            case 4:
                sort( student_list.begin(), student_list.end(),
                        [](const Studentas &a, const Studentas &b) { return a.getGalutinisMed() < b.getGalutinisMed(); });
                break;
            default:
                break;
        }
    }

    // --- Sorts students depending on the function paramater ---
    void sort_students(vector<Studentas> &student_list, int choice) {

    switch (choice) {
        case 1:
            sort(student_list.begin(), student_list.end(),
                      [](const Studentas &a, const Studentas &b) { return a.getVardas() < b.getVardas(); });
            break;
        case 2:
            sort(student_list.begin(), student_list.end(),
                      [](const Studentas &a, const Studentas &b) { return a.getPavarde() < b.getPavarde(); });
            break;
        case 3:
            sort(student_list.begin(), student_list.end(),
                      [](const Studentas &a, const Studentas &b) { return a.getGalutinisVid() < b.getGalutinisVid(); });
            break;
        case 4:
            sort( student_list.begin(), student_list.end(),
                      [](const Studentas &a, const Studentas &b) { return a.getGalutinisMed() < b.getGalutinisMed(); });
            break;
        default:
            break;
    }
}

// -- Actions depending on userChoice -->

    Studentas userChoice_1() {
        Studentas s;
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

        return s;
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