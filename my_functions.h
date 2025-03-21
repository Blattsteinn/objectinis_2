#pragma once

#include "my_library.h"


    // ------------------------
    /// calculations.cpp
    /// moved to a class



    // ------------------------
    /// file_functions.cpp
    namespace fs = std::filesystem;
    string create_folder(string folder_name);

    string readFileToString(const string &file_name);
    int wordCount(istringstream& iss);

    void generate_files(int student_size);

    vector<Studentas> read_student_records(int ndCount, std::istringstream& iss);
    void appendingContainerViaFile(string file_name, vector <Studentas> &student_list);
    void print_to_file(vector<Studentas> list_of_students, string file_name);
    
    // ---------------------------
    /// student_functions.cpp

    void print_students(vector<Studentas> &studentas);
    void insert_student(vector<Studentas> &student_list, Studentas &student);
    vector<float> enter_grades_manually();

    void sort_students(vector<Studentas> &student_list);
    void sort_students(vector<Studentas> &student_list, int choice);

    // ---------------------------
    // random_generating.cpp
    
    int randomNumber(int a, int b);
    vector<float> random_grade();
    string random_name();
    string random_last_name();


    // ---------------------------
    // additional_functions.cpp
    string consoleText_userChoice();
    int check_the_value(string message, string errorMessage,int minVal,int maxVal);  // checks if a give value is within range./