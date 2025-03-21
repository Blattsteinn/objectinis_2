#pragma once

#include "my_library.h"
#include "my_functions.h"

// --- Generates random amount of grades
    template <template<typename, typename...> class Container>
    Container<float> random_grade(){
        Studentas temp;

        int amount_to_generate = randomNumber(2,8);  // Generates a random number to determine how many grades the student will have
        for(int i = 0; i< amount_to_generate; i++){
            int random_generated_grade = randomNumber(1, 10);   // Generates a grade
            temp.pazymiai.push_back(random_generated_grade);
        }

        return temp.pazymiai;
    }

    
// --- Generates random name & last name

    template <template<typename, typename...> class Container>
    string random_name() {
        Container<std::string> vardai = {"John", "Alice", "Michael", "Emily", "David", "Sophia"};
        auto it = vardai.begin();
        std::advance(it, randomNumber(0, vardai.size() - 1));
        return *it;
    }

    template <template<typename, typename...> class Container>
    string random_last_name() {
        Container<std::string> vardai = {"Smith", "Johnson", "Brown", "Williams", "Jones", "Miller"};
        auto it = vardai.begin();
        std::advance(it, randomNumber(0, vardai.size() - 1));
        return *it;
    }
