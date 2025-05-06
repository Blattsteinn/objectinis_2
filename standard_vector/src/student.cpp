#include "my_library.h"
#include "student.h"

#include "my_functions.h"

    void Studentas::unusedFunction() const { }

   // --- Calculation functions    
        float Studentas::calculateMean(){
            float sum = 0;
            float vidurkis = 0;

            if(pazymiai.size() == 0 ) {
                cout << "[Klaida] Negalima apskaiciuoti vidurkio, nes nera ivertinimu. Vidurkis - 0" << endl;
                return 0;
            }

            sum = accumulate(pazymiai.begin(), pazymiai.end(), 0);

            vidurkis = sum/pazymiai.size();
            return vidurkis;

        }

        float Studentas::calculateMedian() {
            if (pazymiai.empty()) {
                cout << "[Klaida] Negalima apskaiciuoti vidurkio, nes nera ivertinimu. Mediana - 0" << endl;
                return 0;
            }
            
            sort(pazymiai.begin(), pazymiai.end());
            size_t n = pazymiai.size();
            
            if (n % 2 != 0) {
                return pazymiai[n / 2];
            } else {
                return (pazymiai[n / 2] + pazymiai[n / 2 - 1]) / 2.0;
            }
            
        }

        void Studentas::calculate_everything(){
            galutinisVid = calculateMean() * 0.4 + egzaminoRezultatas *0.6;
            galutinisMed = calculateMedian() * 0.4 + egzaminoRezultatas *0.6;
        }


    // Copy constructor
    Studentas::Studentas(const Studentas& other): 
        Human(other),
        pazymiai{other.pazymiai},
        egzaminoRezultatas{other.egzaminoRezultatas},
        galutinisVid{other.galutinisVid},
        galutinisMed{other.galutinisMed}
    {

    }

    // Move constructor
    Studentas::Studentas(Studentas&& other) noexcept:   // guaranteed not to throw any exceptions
        Human(other),
        pazymiai{std::move(other.pazymiai)},
        egzaminoRezultatas{other.egzaminoRezultatas},
        galutinisVid{other.galutinisVid},
        galutinisMed{other.galutinisMed}

    {
        other.egzaminoRezultatas = 0;
        other.galutinisVid = 0.0f;
        other.galutinisMed = 0.0f;
    }

    // Copy constructor operator
    Studentas& Studentas::operator=(const Studentas& other) {
        
        if(&other != this){

        vardas = other.vardas;
        pavarde = other.pavarde;
        pazymiai = other.pazymiai;
        egzaminoRezultatas = other.egzaminoRezultatas;
        galutinisVid = other.galutinisVid;
        galutinisMed = other.galutinisMed;
        }
        return *this;
    }

    // Move constructor operator
    Studentas& Studentas::operator=(Studentas&& other) noexcept{
        if(&other != this){
            vardas = std::move(other.vardas);
            pavarde = std::move(other.pavarde);
            pazymiai = std::move(other.pazymiai);

            egzaminoRezultatas = other.egzaminoRezultatas;
            galutinisVid = other.galutinisVid;
            galutinisMed = other.galutinisMed;

            other.egzaminoRezultatas = 0;
            other.galutinisVid = 0.0f;
            other.galutinisMed = 0.0f;
        }
        return *this;
    }
    
    // --- Friend functions
        // Operator << (printing)
        ostream& operator<<(ostream &out, const Studentas &s) {
            out << left << setw(15) << s.pavarde
                << setw(15) << s.vardas
                << fixed << setprecision(2) << setw(22) << s.galutinisVid
                << fixed << setprecision(2) << setw(15) << s.galutinisMed
                << "\n";
            return out;
        }

        // Operator >> (input)
        std::istream& operator>>(std::istream& in, Studentas& s){
            cout << "Vardas: "; in >> s.pavarde;
            cout << "Pavarde: "; in >> s.vardas;

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
                s.pazymiai.push_back(grade);
            }
            
            cout << "Egzamino rezultatas: "; in >> s.egzaminoRezultatas;
            
            s.calculate_everything();

            return in;
        }


    // --- File functions 
        vector<Studentas> Studentas::read_student_records(int ndCount, std::istringstream& iss) {
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
                    if(grade > 10 || grade < 1){
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

        // Appends the student container and calculates everything, 
        // file_name -  txt file, &student_list - container of Student class
        void Studentas::appendingContainerViaFile(string file_name, vector <Studentas> &student_list){
            {   
                try{
                    // ----- reading whole file into a string ------
                            // Open the file in binary mode with the pointer at the end.
                            ifstream file(file_name, ios::binary | ios::ate);
                            if (!file) {
                                throw "[Klaida] Failas neegzistuoja / neatsidaro.\n";
                            }
                            cout << "size: ";
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
                            vector<string> words((std::istream_iterator<string>(headerStream)), std::istream_iterator<string>());
                            if (words.size() < 3) {
                                throw "[Klaida] Neteisinga failo antraste.";
                            }
                            // ND count is total words minus 3 (name, lastName, exam score)
                            int ndCount = words.size() - 3;
                        
            
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

        // Outputs students into a .txt file (preferred way)
        void Studentas::print_to_file(vector<Studentas> list_of_students, string file_name){

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

            //cout << endl;
            //cout << "Rezultatai issaugoti: " << full_path.string() << '\n' << endl; 

        }