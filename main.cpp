#include "my_library.h"
#include "my_functions.h"

int main(){

    vector<Studentas> list_of_students;
    Studentas temp;   

    int program_choice{};
    int strategy_choice{};

    cout << "This is v1.1 !" << endl;
    while(true){ 
        
        program_choice = check_the_value(consoleText_userChoice(), "[Klaida] iveskite skaiciu nuo 1-5", 1,7);
        cout << endl;

        temp.pazymiai.clear();
        if(program_choice == 5) { break; } // Nutraukiamas programos darbas
        switch(program_choice){
            case 1:   // 1 - ivedimas rankas
                cout << "Vardas: ";   cin >> temp.vardas;
                cout << "Pavarde: ";  cin >> temp.pavarde;

                    // --- Rankinis pazymiu ivedimas --- 
                temp.pazymiai = enter_grades_manually();
                temp.egzaminoRezultatas = check_the_value("Egzamino ivertinimas: ", "[Klaida] iveskite skaiciu nuo 1-10", 1, 10);
            
                temp.calculate_everything();
                insert_student(list_of_students, temp);

                break;

            case 2:   // 2 - atsitiktinis pazymiu generavimas
                cout << "Vardas: ";   cin >> temp.vardas;
                cout << "Pavarde: ";  cin >> temp.pavarde;

                temp.pazymiai = random_grade();
                temp.egzaminoRezultatas = randomNumber(1, 10); cout << "Egzamino rezultatas: " << temp.egzaminoRezultatas << endl;
                temp.calculate_everything();
                
                insert_student(list_of_students, temp);

                break;

            case 3:   // 3 - generuoti ir pazymius ir studentu vardus, pavardes
                temp.vardas = random_name();  cout << "Sugeneruotas vardas: " << temp.vardas << endl;
                temp.pavarde = random_last_name(); cout << "Sugeneruota pavarde: " << temp.pavarde << endl;
                temp.pazymiai = random_grade();
                temp.egzaminoRezultatas = randomNumber(1, 10); cout << "Egzamino rezultatas: " << temp.egzaminoRezultatas << endl;

                temp.calculate_everything();
                insert_student(list_of_students, temp);
                break;

            case 4: {   // 4 - skaityti duomenu faila
                appendingContainerViaFile("kursiokai.txt", list_of_students);
                cout << "Duomenys sekmingai nuskaityti is failo." << endl;

                break;  
            }

            case 6: // File generating
                for(int i = 3; i <= 7; i++){
                    generate_files(i);
                }
                break;

            case 7: 
                strategy_choice = check_the_value("Testavimo strategijos pasirinkimas (1,2 arba 3): ", "[Klaida] iveskite skaiciu nuo 1-3", 1,3);
                switch(strategy_choice){
                    case 1:
                        cout << "Hello! 1";
                        break;
                    case 2:
                        cout << "Hello! 2";
                        break;
                    case 3: 
                        cout << "Hello! 3";
                        break;
                    default: break;
                }
                
                break;           

            default: break;  // The program shouldn't reach this point


        }
    }

    if(list_of_students.size() != 0){
        sort_students(list_of_students);

        //print_students(list_of_students);
        print_to_file(list_of_students, "rezultatai.txt");
    
    } else {
        cout << "Nieko ivesta nebuvo. Programa baigta.";
    }

    return 0;
}