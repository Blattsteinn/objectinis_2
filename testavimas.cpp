#include "my_library.h"
#include "my_functions.h"

string consoleText_testing12() {
    return R"(
        [Metodo pasirinkimas]
        
1 - copy constructor, 
2 - move constructor, 
3 - copy assignment operator 
4 - move assignment operator, 

5 - exit testing

            [Pasirinkimas]: )";
}


    // Template function to measure the execution time of any callable
    template<typename Func>
    double measureTime(Func func) {
        auto start = std::chrono::high_resolution_clock::now();
        func();
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double>(end - start).count();
    }

void testing_v12(){
    int strategy_choice;

    
    while(strategy_choice != 5){
        strategy_choice = check_the_value(consoleText_testing12(), "[Klaida] iveskite skaiciu nuo 1-5", 1,5);

        switch(strategy_choice) {
        case 1: {
            vector<float> grades = {8.5f, 9.0f, 7.5f};
            Studentas A("John", "Doe", grades, 10);

            cout << "Move constructor" << endl;
            cout << "Student A: ";
            cout << A << endl;
            cout << endl;

            cout << "Initializing and copying to B" << endl;
            Studentas B = A;

            cout << "End result --->" << endl;
            cout << "Student B: ";
            cout << B << endl;

            cout << "Student A: ";
            cout << A << endl;
        }
        break;

        case 2:  {
            vector<float> grades = {8.5f, 9.0f, 7.5f};
            Studentas A("John", "Doe", grades, 10);

            cout << "Move constructor" << endl;
            cout << "Student A: ";
            cout << A << endl;
            cout << endl;

            cout << "Initializing and copying to B" << endl;
            Studentas B(std::move(A));

            cout << "End result --->" << endl;
            cout << "Student B: ";
            cout << B << endl;

            cout << "Student A: ";
            cout << A << endl;
        }
        break;

        case 3: {
            vector<float> grades = {8.5f, 9.0f, 7.5f};
            Studentas A("John", "Doe", grades, 10);

            cout << "Copy constructor assignment" << endl;
            cout << "Initializing student B " << endl;
            Studentas B;

            cout << "Student A: ";
            cout << A << endl;
            cout << endl;

            cout << "Assigning B to A" << endl;
            B = A;

            cout << "End result --->" << endl;
            cout << "Student B: ";
            cout << B << endl;

            cout << "Student A: ";
            cout << A << endl;
        }
        break;

        case 4: {
            vector<float> grades = {8.5f, 9.0f, 7.5f};
            Studentas A("John", "Doe", grades, 10);
            
            cout << "Move constructor assignment" << endl;
            cout << "Initializing student B " << endl;
            Studentas B;

            cout << "Student A: ";
            cout << A << endl;
            cout << endl;

            cout << "Moving B to A" << endl;
            B = std::move(A);

            cout << "End result --->" << endl;
            cout << "Student B: ";
            cout << B << endl;

            cout << "Student A: ";
            cout << A << endl;
        }
        break;

        case 5: return; 
        break;

        default: break;
    }
    }
}

void testing_v11(){
    for(int i=5; i<=6; i++){

        int file_size = pow(10, i);
        string file_name = "testavimasFailas" + to_string(file_size) + ".txt";
        string folder_name = create_folder("Archive");  // Creates a folder

        fs::path full_path = fs::path(folder_name) / file_name;      // Combine folder and file name

        vector<Studentas> list_of_students;
        double readingTime;
        cout << "------ Currently testing: " << file_name << " ------"  << endl; cout << endl;
        
        // --- Reading ---
            readingTime = measureTime([&]() {
                appendingContainerViaFile(full_path.string(), list_of_students);
            });
                cout << "Reading completed." << endl;

        // --- Sorting ---
            readingTime = measureTime([&]() {
                sort_students(list_of_students, 3);
            });
                cout << "Sorting completed." << endl;

        

        // --- Splits students between two groups ---

        vector<Studentas> worse_students;
        sort(list_of_students.begin(), list_of_students.end(),
            [](const Studentas &a, const Studentas &b) { return a.getGalutinisVid() > b.getGalutinisVid(); });

        readingTime = measureTime([&](){
            for (int i = list_of_students.size() - 1; i >= 0 && list_of_students[i].getGalutinisVid() < 5; --i) {
                    worse_students.push_back(list_of_students[i]);
                    list_of_students.pop_back();
                }
            });

            cout << "Grouping time: " << readingTime << "s" << endl;

        cout << "Finished!" << endl;
        cout << endl;
        cout << endl;
    }
}


// --- Divides students into two groups & splits them to seperate containers ---
vector<Studentas> divide_students_unoptimized(const vector<Studentas>& list_of_students, int choice) {

    vector <Studentas> students;

    // --- returns list of students whose final grade is below 5
    if(choice == 0) { 
    for(auto student : list_of_students){
        if (student.getGalutinisVid() < 5){
            students.push_back(student);
        }
    }
    return students;
    }

    // --- returns list of students whose final grade is above 5
    else if(choice == 1) { 
        for(auto student : list_of_students){
            if (student.getGalutinisVid() >= 5){
                students.push_back(student);
            }
        }
        return students;
    }
    return students;
}

// --- Strategy 1 ---
void strategy_1(){
    for(int i=3; i<=7; i++){

        int file_size = pow(10, i);
        string file_name = "testavimasFailas" + to_string(file_size) + ".txt";
        string folder_name = create_folder("Archive");  // Creates a folder

        fs::path full_path = fs::path(folder_name) / file_name;      // Combine folder and file name

        vector<Studentas> list_of_students;

        cout << "--------------------------- Currently testing: " << file_name << endl; cout << endl;
        auto overall_start = std::chrono::high_resolution_clock::now();   /// <--- sparta pradedama skaiciuoti cia
        double readingTime;

        // --- Reading ---
        readingTime = measureTime([&]() {
            appendingContainerViaFile(full_path.string(), list_of_students);
        });
            cout << "Reading time: " << readingTime << "s" << endl;

    // --- Sorting ---
        readingTime = measureTime([&]() {
            sort_students(list_of_students, 3);
        });
            cout << "Sorting time: " << readingTime << "s" << endl;


        

        // --- Splits students between two groups ---

        vector<Studentas> worse_students;
        vector<Studentas> good_students;

            readingTime = measureTime([&]() {
                worse_students = divide_students_unoptimized(list_of_students, 0); 
                good_students = divide_students_unoptimized(list_of_students, 1);
                });
                    cout << "Grouping time: " << readingTime << "s" << endl;

        // --- Bendras skaitymo laikas

                auto overall_end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> overall = overall_end - overall_start;
                std::cout << "Overall reading time: " << overall.count() << "s" << std::endl;

        cout << endl;
        cout << endl;

        worse_students.clear();
        good_students.clear();
        list_of_students.clear();

    }
}

// --- Strategy 2 ---
void strategy_2(){
    for(int i=3; i<=7; i++){

        int file_size = pow(10, i);
        string file_name = "testavimasFailas" + to_string(file_size) + ".txt";
        string folder_name = create_folder("Archive");  // Creates a folder

        fs::path full_path = fs::path(folder_name) / file_name;      // Combine folder and file name

        vector<Studentas> list_of_students;
        double readingTime;
        cout << "--------------------------- Currently testing: " << file_name << endl; cout << endl;
        
        // --- Reading ---
            readingTime = measureTime([&]() {
                appendingContainerViaFile(full_path.string(), list_of_students);
            });
                cout << "Reading completed." << endl;

        // --- Sorting ---
            readingTime = measureTime([&]() {
                sort_students(list_of_students, 3);
            });
                cout << "Sorting completed." << endl;

        

        // --- Splits students between two groups ---

        vector<Studentas> worse_students;

            cout << "Conteineris yra vektorius" << endl;
            sort(list_of_students.begin(), list_of_students.end(),
            [](const Studentas &a, const Studentas &b) { return a.getGalutinisVid() > b.getGalutinisVid(); });

            readingTime = measureTime([&](){
                for (int i = list_of_students.size() - 1; i >= 0 && list_of_students[i].getGalutinisVid() < 5; --i) {
                    worse_students.push_back(list_of_students[i]);
                    list_of_students.pop_back();
                }
            });


            cout << "Grouping time: " << readingTime << "s" << endl;

        cout << "Finished!" << endl;
        cout << endl;
        cout << endl;
    }
}

// --- Strategy 3 ---
void strategy_3(){
    for(int i=3; i<=7; i++){

        int file_size = pow(10, i);
        string file_name = "testavimasFailas" + to_string(file_size) + ".txt";
        string folder_name = create_folder("Archive");  // Creates a folder

        fs::path full_path = fs::path(folder_name) / file_name;      // Combine folder and file name

        vector<Studentas> list_of_students;
        double readingTime;
        cout << "--------------------------- Currently testing: " << file_name << endl; cout << endl;
        
        // --- Reading ---
            readingTime = measureTime([&]() {
                appendingContainerViaFile(full_path.string(), list_of_students);
            });
                cout << "Reading completed." << endl;

        // --- Sorting ---
            readingTime = measureTime([&]() {
                sort_students(list_of_students, 3);
            });
                cout << "Sorting completed." << endl;

        

        // --- Splits students between two groups ---

        vector<Studentas> worse_students;

        readingTime = measureTime([&]() {
            auto it = std::find_if(list_of_students.begin(), list_of_students.end(),
            [](const Studentas& s) { return s.getGalutinisVid() >= 5.0; });
            
                worse_students.assign(list_of_students.begin(), it);  // Copy failing students
                list_of_students.erase(list_of_students.begin(), it);   // Remove failing students
        
            });
            cout << "Grouping time: " << readingTime << "s" << endl;
        
        cout << "Finished!" << endl;
        cout << endl;
        cout << endl;
    }
}