#pragma once

#include "my_library.h"
#include "student.h"

    /// \file functions.h
    /// \brief Declarations for file handling, student utilities, user choices,
    ///        random data, input validation, and testing routines.

    // ------------------------
    /// \brief Functions for file operations (file_functions.cpp)
    namespace fs = std::filesystem;

    /// \brief Create a folder if it does not exist.
    /// \param folder_name Name of the folder to create.
    /// \return Path of the created or existing folder.
    string create_folder(string folder_name);

    /// \brief Generate test files with random student data.
    /// \param student_size Exponent for count: will generate 10^student_size entries.
    void generate_files(int student_size);

    // ---------------------------
    /// \brief Student list utilities (student_functions.cpp)

    /// \brief Print all students to the console.
    /// \param studentas Vector of Studentas objects to print.
    void print_students(Vector<Studentas> &studentas);

    /// \brief Insert a student into the list.
    /// \param student_list Vector to append to.
    /// \param student      Studentas instance to add.
    void insert_student(Vector<Studentas> &student_list, Studentas &student);

    /// \brief Sort students by default criterion.
    /// \param student_list Vector of students to sort.
    void sort_students(Vector<Studentas> &student_list);

    /// \brief Sort students by a specific choice.
    /// \param student_list Vector of students to sort.
    /// \param choice       Criterion identifier.
    void sort_students(Vector<Studentas> &student_list, int choice);

    // ---------------------------
    /// \brief User input routines (program_choice.cpp)

    /// \brief Create a student by manual name and random grades.
    /// \return Initialized Studentas.
    Studentas userChoice_2();

    /// \brief Create a student with random name and grades.
    /// \return Initialized Studentas.
    Studentas userChoice_3();

    // ---------------------------
    /// \brief Random data generators (random_generating.cpp)

    /// \brief Generate a random integer in [a,b].
    /// \param a Minimum value.
    /// \param b Maximum value.
    /// \return Random integer between a and b.
    int randomNumber(int a, int b);

    /// \brief Generate a random list of grades.
    /// \return Vector of random float grades.
    Vector<float> random_grade();

    /// \brief Generate a random first name.
    /// \return Random name string.
    string random_name();

    /// \brief Generate a random last name.
    /// \return Random surname string.
    string random_last_name();

    // ---------------------------
    /// \brief Input helpers (additional_functions.cpp)

    /// \brief Read a menu choice from console.
    /// \return Raw input string.
    string consoleText_userChoice();

    /// \brief Prompt and validate integer input within a range.
    /// \param message      Prompt to display.
    /// \param errorMessage Error on invalid input.
    /// \param minVal       Minimum valid value.
    /// \param maxVal       Maximum valid value.
    /// \return Validated integer.
    int check_the_value(string message, string errorMessage, int minVal, int maxVal);

    // ---------------------------
    /// \brief Testing routines (testing.cpp)

    void testing_v3__1();
    void testing_v3__2();
    /// \brief Run test suite v1.2.
    void testing_v12();

    /// \brief Run test suite v1.1.
    void testing_v11();

    /// \brief Execute performance strategy 1.
    void strategy_1();

    /// \brief Execute performance strategy 2.
    void strategy_2();

    /// \brief Execute performance strategy 3.
    void strategy_3();