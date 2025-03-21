#include "my_library.h"
#include "my_functions.h"


// --- Reads the entire file into a string in a universal way ---
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

// --- Counts the number of ND (NDn) in the header ---
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