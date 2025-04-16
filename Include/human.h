#pragma once

#include "my_library.h"

class Human {
    protected:
        string vardas;
        string pavarde;

    public:

    Human()
        : vardas(""), pavarde("") {}

        string getVardas() const { return vardas; }
        string getPavarde() const { return pavarde; }
};