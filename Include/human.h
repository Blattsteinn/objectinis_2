#pragma once

#include "my_library.h"

class Human {
    protected:
        string vardas;
        string pavarde;

    public:
    Human(const string& vardas, const string& pavarde)
        : vardas(vardas), pavarde(pavarde)
         { }

        string getVardas() const { return vardas; }
        string getPavarde() const { return pavarde; }

        virtual void unusedFunction() const = 0;

        // Virtual destructor for proper cleanup
        virtual ~Human() {}

};