#include "my_library.h"
#include "my_functions.h"


    // --- Reads the entire file into a string ---
    string readFileToString(const string &file_name) {
        // Open the file in binary mode with the pointer at the end.
        ifstream file(file_name, ios::binary | ios::ate);
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
        
        return content;
    }

    // --- Counts the number of ND in the header ---
    int wordCount(istringstream& iss) {
        string header;
        getline(iss, header);
        istringstream headerStream(header);
        vector<string> words((std::istream_iterator<string>(headerStream)), std::istream_iterator<string>());
        if (words.size() < 3) {
            throw "[Klaida] Neteisinga failo antraste.";
        }
        // ND count is total words minus 3 (name, lastName, exam score)
        return words.size() - 3;
    }

    // --- Reads student records  ---   
    //  ndCount - instances of NDn in the file; &iss - stream of the file.
    //  Skips processing further records if any record is malformed.
    //  Returns a container of Studentas objects 
    vector<Studentas> read_student_records(int ndCount, std::istringstream& iss) {
        vector<Studentas> records;

        while (true) {
            string vardas, pavarde;
            float egzaminoRezultatas;

            if (!(iss >> vardas >> pavarde))
                break;  // End of file or read error.
            
            
            vector<float> pazymiai;
            pazymiai.clear();

            for (int i = 0; i < ndCount; i++) {
                float grade;
                if (!(iss >> grade)) {
                    throw "[Klaida] Netinkamas duomenu failas!";
                }
                pazymiai.push_back(grade);
            }
            
            // Read exam score.
            if (!(iss >> egzaminoRezultatas)) {
                throw "[Klaida] Netinkamas duomenu failas!";
            }
            
            Studentas temp(vardas, pavarde, pazymiai, egzaminoRezultatas);
            records.push_back(temp);
        }
        return records;
    }


    // --- Appends the student container and calculates everything ---
    // file_name -  ***.txt file
    // &student_list - container of Student structs
    void appendingContainerViaFile(string file_name, vector <Studentas> &student_list){
        {   
            try{
                string content = readFileToString(file_name);
                istringstream iss(content);  // Stream for parsing the file
                int ndCount = wordCount(iss);
            
        
                vector<Studentas> studentList = read_student_records(ndCount, iss);
                
                for( auto &student : studentList){
                    student.calculate_everything();
                    insert_student(student_list, student);
                }
            } catch (const char* msg) {
                cerr << msg << endl;
            }
        }
    }

    // -- Outputs students into a .txt file (preferred way)
    void print_to_file(vector<Studentas> list_of_students, string file_name){

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
            buffer << s;   // Check class Studentas for printing logic

        }
        isvedimas << buffer.str();
        isvedimas.close();

        cout << endl;
        cout << "Rezultatai issaugoti: " << full_path.string() << '\n' << endl; 

    }

// --- File / folder generating
    string create_folder(string folder_name) {
        // Define the folder path relative to the current working directory.
        fs::path folderPath = fs::current_path() / folder_name;
    
        // Create the folder if it does not exist.
        if (!fs::exists(folderPath)) {
            if (!fs::create_directories(folderPath)) {
                std::cerr << "[Klaida]: Nepavyko sukurti aplanko: " << folderPath << std::endl;
                return "";
            }
        }
        return folderPath.string();
    }


    void generate_files(int student_size) { // size = 10^student_size
    
        int size = pow(10, student_size);
        string file_name = "testavimasFailas" + to_string(size) + ".txt";
        string folder_name = create_folder("Generated Files");  // Creates a folder

        fs::path full_path = fs::path(folder_name) / file_name;      // Combine folder and file name

        std::ofstream output(full_path.string());
    
        
    
        int nd_to_generate = 5; // or use this for randomness---> randomNumber(5,12);
    
        std::ostringstream buffer;
        buffer << std::left << std::setw(25) << "Vardas"
            << std::left << std::setw(27) << "Pavarde";
    
        for (int i = 1; i <= nd_to_generate; i++) {
            buffer << std::left << std::setw(10) << ("ND" + std::to_string(i));
        }
        buffer << std::left << std::setw(10) << "EGZ.";
        buffer << '\n';
    
    
        for(int i = 1; i <= size; i++){
            string vardas = "VardasNr" + std::to_string(i);;
            string pavarde = "PavardeNr" + std::to_string(i);
    
            buffer << std::left << std::setw(25) << vardas
                      << std::left << std::setw(27) << pavarde;
                      
            for (int j = 0; j < nd_to_generate; j++) {
                buffer << std::left << std::setw(10) << randomNumber(1, 10);
            } 
            buffer << std::left << std::setw(10) << randomNumber(1, 10);
            buffer << '\n';
        }
    
    
        output << buffer.str();
        output.close();
    
        // ----
            cout << "Sukurtas naujas failas." << endl;
            cout << "Failo vieta: " << full_path.string() << endl; 
            cout << endl;
        // ----
    }

