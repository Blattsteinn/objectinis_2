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
        Studentas temp = student; // Copy the student
        student_list.push_back(temp);
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