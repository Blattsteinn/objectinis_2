#include "my_library.h"
#include "my_functions.h"
string consoleText_testing12() {
    return R"(
        [Metodo pasirinkimas]
        
1 - copy constructor, 
2 - move constructor, 
3 - copy assignment operator 
4 - move assignment operator, 

5 - I/O (<< / >>) testing,

6 - exit testing

            [Pasirinkimas]: )";
}

    template<typename Func>
    double measureTime(Func func) {
        auto start = std::chrono::high_resolution_clock::now();
        func();
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double>(end - start).count();
    }

    void iterpimo_testavimas(string file_name, int i){
           
        double readingTime;
        Vector<Studentas> studentList;
        fs::path full_path = fs::path("Archive") / file_name;      // Combine folder and file name

        auto overall_start = std::chrono::high_resolution_clock::now();   /// <--- sparta pradedama skaiciuoti cia
        try{
            // ----- reading whole file into a string ------
                    // Open the file in binary mode with the pointer at the end.
                    ifstream file(full_path.string(), ios::binary | ios::ate);
                    if (!file) {
                        throw "[Klaida] Failas neegzistuoja / neatsidaro.\n";
                    }
                    
                    // Get file size and seek back to the beginning.
                    std::streamsize size = file.tellg();
                    file.seekg(0, ios::beg);
                    
                    // Pre-allocate a string of the appropriate size.
                    string content;
                    content.resize(size);
                    
                    // Read the file content directly into the string.
                    if (!file.read(&content[0], size)) {
                        throw "[Klaida] Skaitymo klaida!\n";
                    }
            // ---------------------        
            
            istringstream iss(content);  // Creates a stream for parsing the file

            // ----- counts the amount of ND in the file ------
                    string header;
                    getline(iss, header);
                    istringstream headerStream(header);
                    Vector<string> words((std::istream_iterator<string>(headerStream)), std::istream_iterator<string>());
                    if (words.size() < 3) {
                        throw "[Klaida] Neteisinga failo antraste.";
                    }
                    // ND count is total words minus 3 (name, lastName, exam score)
                    int ndCount = words.size() - 3;
                 
            // DO-HERE !!    1) count how long it takes to read the file.
            readingTime = measureTime([&]() {
                studentList = Studentas::read_student_records(ndCount, iss);
            }); cout << "Reading time: " << readingTime << endl;
            
            // DO-HERE !! 
            // 2) count how long it takes to sort and calculate median/average
            readingTime = measureTime([&]() {
                for( auto &student : studentList){
                    student.calculate_everything();
                }
            }); cout << "Sorting and inserting students: " << readingTime << endl;
            
        } catch (const char* msg) {
            cerr << msg << endl;
        }
        // DO-HERE !!    3) count how long it takes to print to the file.
        readingTime = measureTime([&]() {
            Studentas::print_to_file(studentList,  "rezultatai" + std::to_string(i) + ".txt");
        }); cout << "Printing everything to a file: " << readingTime << endl;

    auto overall_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> overall = overall_end - overall_start;
    std::cout << "Overall reading time: " << overall.count() << "s" << std::endl;
    cout << endl;
}


    // 1 salygos testavimas
    void testing_v3__1() {
        for (int i = 4; i < 10; ++i) {

            unsigned int sz = pow(10, i);
            std::cout << "--- sz = " << sz << " ---\n";
    
            std::vector<int> v1;
            double t1 = measureTime([&](){
                for (unsigned i = 1; i <= sz; ++i)
                    v1.push_back(i);
            });
    
            Vector<int> v2;
            double t2 = measureTime([&](){
                for (unsigned i = 1; i <= sz; ++i)
                    v2.push_back(i);
            });

            cout << "  std::vector laikas: " << t1 << " s\n"
                << "  Vector<T>    laikas: " << t2 << " s\n"
                << "  skirtumas:       " << t2 - t1 << " s\n\n";
        }
    }

    // 2 salygos testavimas
    void testing_v3__2() {
        for (int i = 4; i < 10; ++i) {

            int v1_grow_count = 0;
            int v2_grow_count = 0;

            unsigned int sz = pow(10, i);
            cout << "--- sz = " << sz << " ---\n";
    
            std::vector<int> v1;
            for (unsigned j = 1; j <= sz; ++j){
                v1.push_back(j);
                if( v1.capacity() == v1.size()){ v1_grow_count++;}
            }
    
            Vector<int> v2;
            for (unsigned j = 1; j <= sz; ++j){
                v2.push_back(j);
                if( v2.capacity() == v2.size()){ v2_grow_count++;}
            }

            cout
            << "  std::vector growth count: " << v1_grow_count << "\n"
            << "  Vector<T>   growth count: " << v2_grow_count << "\n"
            << "  difference:               " << (v2_grow_count - v1_grow_count) << "\n\n";
        }
    }
    
void testing_v12(){
        int strategy_choice;   
        while(strategy_choice != 6){
            strategy_choice = check_the_value(consoleText_testing12(), "[Klaida] iveskite skaiciu nuo 1-6", 1,6);
    
            switch(strategy_choice) {
            case 1: {
                Vector<float> grades = {8.5f, 9.0f, 7.5f};
                Studentas A("John", "Doe", grades, 10);
    
                cout << "[Copy constructor method]" << endl;
                cout << "[Student A]: " << A << endl;
                cout << endl;
                

                cout << "Initializing B and copying from A" << endl;
                Studentas B(A);
                
                //--------------    
                cout << "\n" << "[End result] --->" << "\n\n";
                cout << "[Student B]: " << B << endl;
                cout << "[Student A]: " << A << endl;
            }
            break;
    
            case 2:  {
                Vector<float> grades = {8.5f, 9.0f, 7.5f};
                Studentas A("John", "Doe", grades, 10);
    
                cout << "[Move constructor method]" << endl;

                cout << "Student A: " << A << endl;
                cout << endl;
    
                cout << "Initializing B and moving A to B" << endl;
                Studentas B(std::move(A));

                //--------------    
                cout << "\n" << "[End result] --->" << "\n\n";
                cout << "[Student B]: " << B << endl;
                cout << "[Student A]: " << A << endl;
            }
            break;
    
            case 3: {
                Vector<float> grades = {8.5f, 9.0f, 7.5f};
                Studentas A("John", "Doe", grades, 10);
                Studentas B;

                cout << "[Copy constructor assignment method]" << endl;
                cout << "[Student A]: " << A << endl;
                cout << "[Student B]: " << B << endl;
                cout << endl;
               
                cout << "Assigning A to B" << endl;
                B = A;
    
                 //--------------    
                 cout << "\n" << "[End result] --->" << "\n\n";
                 cout << "[Student B]: " << B << endl;
                 cout << "[Student A]: " << A << endl;
            }
            break;
    
            case 4: {
                Vector<float> grades = {8.5f, 9.0f, 7.5f};
                Studentas A("John", "Doe", grades, 10);
                Studentas B;

                cout << "[Move constructor assignment]" << endl;
                cout << "[Student A]: " << A << endl;
                cout << "[Student B]: " << B << endl;
                cout << endl;
                

                cout << "Moving B to A" << endl;
                B = std::move(A);
    
                //--------------    
                cout << "\n" << "[End result] --->" << "\n\n";
                cout << "[Student B]: " << B << endl;
                cout << "[Student A]: " << A << endl;
            }
            break;
            
            // input/output test
            case 5: {
                Studentas B;
                cout << "[Testing operator>>]" << "\n\n";
                cout << "[Testing operator<<]" << "\n\n";
                cin >> B;
                cout << endl;
                cout << B;            
            }
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

        Vector<Studentas> list_of_students;
        double readingTime;
        cout << "------ Currently testing: " << file_name << " ------"  << endl; cout << endl;
        
        // --- Reading ---
            readingTime = measureTime([&]() {
                Studentas::appendingContainerViaFile(full_path.string(), list_of_students);
            });
                cout << "Reading completed." << endl;

        // --- Sorting ---
            readingTime = measureTime([&]() {
                sort_students(list_of_students, 3);
            });
                cout << "Sorting completed." << endl;

        

        // --- Splits students between two groups ---

        Vector<Studentas> worse_students;
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
Vector<Studentas> divide_students_unoptimized(const Vector<Studentas>& list_of_students, int choice) {

    Vector <Studentas> students;

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

        Vector<Studentas> list_of_students;

        cout << "--------------------------- Currently testing: " << file_name << endl; cout << endl;
        auto overall_start = std::chrono::high_resolution_clock::now();   /// <--- sparta pradedama skaiciuoti cia
        double readingTime;

        // --- Reading ---
        readingTime = measureTime([&]() {
            Studentas::appendingContainerViaFile(full_path.string(), list_of_students);
        });
            cout << "Reading time: " << readingTime << "s" << endl;

    // --- Sorting ---
        readingTime = measureTime([&]() {
            sort_students(list_of_students, 3);
        });
            cout << "Sorting time: " << readingTime << "s" << endl;


        

        // --- Splits students between two groups ---

        Vector<Studentas> worse_students;
        Vector<Studentas> good_students;

            readingTime = measureTime([&]() {
                worse_students = divide_students_unoptimized(list_of_students, 0); 
                good_students = divide_students_unoptimized(list_of_students, 1);
                });
                    cout << "Grouping time: " << readingTime << "s" << endl;

                    Studentas::print_to_file(worse_students, "blogi_studentai" + std::to_string(i) + ".txt");
                    Studentas::print_to_file(good_students, "geri_studentai" + std::to_string(i)+ ".txt");
    
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

        Vector<Studentas> list_of_students;
        double readingTime;
        cout << "--------------------------- Currently testing: " << file_name << endl; cout << endl;
        
        // --- Reading ---
            readingTime = measureTime([&]() {
                Studentas::appendingContainerViaFile(full_path.string(), list_of_students);
            });
                cout << "Reading completed." << endl;

        // --- Sorting ---
            readingTime = measureTime([&]() {
                sort_students(list_of_students, 3);
            });
                cout << "Sorting completed." << endl;

        

        // --- Splits students between two groups ---

        Vector<Studentas> worse_students;

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

        Vector<Studentas> list_of_students;
        double readingTime;
        cout << "--------------------------- Currently testing: " << file_name << endl; cout << endl;
        
        // --- Reading ---
            readingTime = measureTime([&]() {
                Studentas::appendingContainerViaFile(full_path.string(), list_of_students);
            });
                cout << "Reading completed." << endl;

        // --- Sorting ---
            readingTime = measureTime([&]() {
                sort_students(list_of_students, 3);
            });
                cout << "Sorting completed." << endl;

        

        // --- Splits students between two groups ---

        Vector<Studentas> worse_students;

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