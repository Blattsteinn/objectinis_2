#include "my_library.h"
#include "my_functions.h"

    // Template function to measure the execution time of any callable
    template<typename Func>
    double measureTime(Func func) {
        auto start = std::chrono::high_resolution_clock::now();
        func();
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double>(end - start).count();
    }

void testing(){
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