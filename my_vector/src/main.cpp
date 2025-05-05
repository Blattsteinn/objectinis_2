#include "my_library.h"
#include "my_functions.h"

int main(){

        cout  << "Testas" << endl;
        cout << "----------------------------------------------------------------------------" << endl;
        testing_v3__2();


    Vector<Studentas> list_of_students;
    Studentas temp;   

    int program_choice{};
    int strategy_choice{};
    cout << "This is v3.0!" << endl;

    //strategy_1();
    //cout << "strategy 1 done" << endl;
    
    cin >> program_choice;
    while(true){ 
        
        program_choice = check_the_value(consoleText_userChoice(), "[Klaida] iveskite skaiciu nuo 1-6", 1,6);
        cout << endl;

        if(program_choice == 5) { break; } // Nutraukiamas programos darbas
        switch(program_choice){
            case 1:   // 1 - ivedimas rankas
                cin >> temp;
                insert_student(list_of_students, temp);

                break;
            
            case 2:   // 2 - atsitiktinis pazymiu generavimas
                temp = userChoice_2();
                insert_student(list_of_students, temp);

                break;

            case 3:   // 3 - generuoti ir pazymius ir studentu vardus, pavardes
                temp = userChoice_3();
                insert_student(list_of_students, temp);

                break;

            case 4: {   // 4 - Duomenu failo skaitymas
                Studentas::appendingContainerViaFile("kursiokai.txt", list_of_students);
                cout << "Duomenys sekmingai nuskaityti is failo." << endl;

                break;  
            }

            case 6: // File generating
                for(int i = 3; i <= 7; i++){
                    generate_files(i);
                }
                break;

            case 7:

            default: break;  // The program shouldn't reach this point


        }
    }

    if(list_of_students.size() != 0){
        sort_students(list_of_students);
        Studentas::print_to_file(list_of_students, "rezultatai.txt");
    
    } else {
        cout << "Nieko ivesta nebuvo. Programa baigta.";
    }

    return 0;
}