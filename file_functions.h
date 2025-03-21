#pragma once

#include "my_library.h"

string readFileToString(const string &file_name);
int wordCount(istringstream& iss);
void generate_files(int student_size);

namespace fs = std::filesystem;
string create_folder(string folder_name);

// --- Reads student records  ---   
    //  ndCount - instances of NDn in the file; &iss - stream of the file.
    //  Skips processing further records if any record is malformed.
    //  Returns a container of Studentas objects 
    
    template<template<typename, typename...> class Container>
    Container<Studentas> read_student_records(int ndCount, std::istringstream& iss) {
        Container<Studentas> records;
        while (true) {
            Studentas r;
            if (!(iss >> r.vardas >> r.pavarde))
                break;  // End of file or read error.
            
            // Clear any existing grades (if any) and read exactly ndCount grades.
            r.pazymiai.clear();
            for (int i = 0; i < ndCount; i++) {
                float grade;
                if (!(iss >> grade)) {
                    throw "[Klaida] Netinkamas duomenu failas!";
                }
                r.pazymiai.push_back(grade);
            }
            
            // Read exam score.
            if (!(iss >> r.egzaminoRezultatas)) {
                throw "[Klaida] Netinkamas duomenu failas!";
            }
            
            records.push_back(r);
        }
        return records;
    }


// --- Appends the student container and calculates everything ---
    // file_name - needed .txt file
    // &student_list - container of Student structs

    template<template<typename,typename ...> class Container>
    void appendingContainerViaFile(string file_name, Container <Studentas> &student_list){
        {   
            try{
                string content = readFileToString(file_name);
                istringstream iss(content);  // Stream for parsing the file
                int ndCount = wordCount(iss);
            
        
                Container<Studentas> studentList = read_student_records<Container>(ndCount, iss);
                
                for( auto student : studentList){
                    calculate_everything(student);
                    insert_student(student_list, student);
                }
            } catch (const char* msg) {
                cerr << msg << endl;
            }
        }
    }

    // -- Outputs students into a .txt file (preferred way)
    template <template<typename, typename...> class Container>
    void print_to_file(Container<Studentas> list_of_students, string file_name){

        // Create an output string stream
        std::ostringstream buffer;

            buffer <<'\n' 
            << left << setw(15) << "Pavarde" 
            << setw(15) << "Vardas" 
            << setw(15) << "Galutinis (Vid.)  /  " 
            << setw(15) << "Galutinis (Med.)" 
            << "\n-------------------------------------------------------------\n";

        string folder_name = create_folder("Rezultatai");
        fs::path full_path = fs::path(folder_name) / file_name;      // Combine folder and file name

        ofstream isvedimas(full_path.string());
        for (auto& s : list_of_students) {
            buffer << s;   //Check struct Studentas for printing logic

        }
        isvedimas << buffer.str();
        isvedimas.close();

        cout << endl;
        cout << "Rezultatai issaugoti: " << full_path.string() << '\n' << endl; 

    }
