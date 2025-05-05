#include "my_library.h"
#include "my_functions.h"


// --- returns a random number within wanted range a <= x <= b;
    int randomNumber(int a, int b) {
        static std::mt19937 gen{std::random_device{}()}; // paleidziama tik karta
        std::uniform_int_distribution<int> distr(a, b);
        return distr(gen);
    }

    Vector<float> random_grade(){
        Vector<float> grades;

        int amount_to_generate = randomNumber(2,8);  // Generates a random number to determine how many grades the student will have
        for(int i = 0; i< amount_to_generate; i++){
            int random_generated_grade = randomNumber(1, 10);   // Generates a grade
            grades.push_back(random_generated_grade);
        }

        return grades;
    }

// --- Generates random name & last name
    string random_name() {
        Vector<std::string> vardai = {"John", "Alice", "Michael", "Emily", "David", "Sophia"};
        auto it = vardai.begin();
        std::advance(it, randomNumber(0, vardai.size() - 1));
        return *it;
    }

    string random_last_name() {
        Vector<std::string> vardai = {"Smith", "Johnson", "Brown", "Williams", "Jones", "Miller"};
        auto it = vardai.begin();
        std::advance(it, randomNumber(0, vardai.size() - 1));
        return *it;
    }
