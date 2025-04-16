#include "my_library.h"
#include "my_functions.h"

int main(){

    vector<Studentas> list_of_students;
    Studentas temp;   

    int program_choice{};
    int strategy_choice{};

   // Human a("Boo", "Foo22");    // <--- will not work

    cout << "This is v1.5!" << endl;
    while(true){ 
        
        program_choice = check_the_value(consoleText_userChoice(), "[Klaida] iveskite skaiciu nuo 1-7", 1,7);
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
            strategy_choice = check_the_value("Testavimo strategijos pasirinkimas (1,2 arba 3), 4 - grupavimo testavimas, 5 - rule of 5: "
                , "[Klaida] iveskite skaiciu nuo 1-6", 1,5);
            
            switch(strategy_choice){
                case 1:
                    strategy_1();
                    break;
                case 2:
                    strategy_2();
                    break;
                case 3: 
                    strategy_3();
                    break;
                case 4:
                    cout << "Grupavimo testavimas" << endl;
                    for(int i=1; i<6; i++){
                        cout << i << " testas" << endl;
                        testing_v11();
                    }
                case 5:
                    testing_v12();
                    break;
                    
                default: break;
            }
                break;
            
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