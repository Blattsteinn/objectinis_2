#include "my_library.h"
#include "my_functions.h"


// --- checks whenever a value is within a needed range
int check_the_value(string message, string errorMessage,int minVal,int maxVal){
    while (true)
    {
        cout << message;
        int value; 
        if (!(cin >> value)){  // <-- if cin fails
            cout << errorMessage << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;  // <-- prompt back again
        }

        if (value < minVal || value > maxVal){  // <-- if the number is not within the given range 
            cout << errorMessage << endl;
            continue;  // <-- prompt back again
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return value;
    }
}

// --- returns a menu
string consoleText_userChoice() {
    return R"(
        [Programos eigos pasirinkimas]
        
1 - rankinis ivedimas, 
2 - generuoti pazymius, 
3 - generuoti ir pazymius, ir studentu vardus, pavardes, 
4 - nuskaityti duomenis is failo, 
5 - baigti darba

6 - failu generavimas
7 - testavimas

            [Pasirinkimas]: )";
}