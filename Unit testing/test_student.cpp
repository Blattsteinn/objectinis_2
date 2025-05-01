// tests.cpp
// Unit tests using the Catch2 framework

#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "student.h"
#include "my_library.h"
#include <sstream>

TEST_CASE("Vidurkio skaiciavimas", "[Studentas]") {
    vector<float> grades{4.0f, 6.0f, 8.0f};
    Studentas s("", "", grades, 10);
    REQUIRE(s.calculateMean() == Approx((4.0f + 6.0f + 8.0f) / 3.0f));
}

TEST_CASE("Medianos funkcijos testavimas, [NELYGINIS] skaicius", "[Studentas]") {
    vector<float> grades{5.0f, 1.0f, 3.0f};
    Studentas s("", "", grades, 6);
    REQUIRE(s.calculateMedian() == Approx(3.0f));
}

TEST_CASE("Medianos funkcijos testavimas, [LYGINIS] skaicius", "[Studentas]") {
    vector<float> grades{3.0f, 7.0f, 1.0f, 9.0f};
    Studentas s("", "", grades, 8);
    // Sorted: 1, 3, 7, 9 -> median = (3 + 7) / 2 = 5
    REQUIRE(s.calculateMedian() == Approx(5.0f));
}

TEST_CASE("calculate_everything() funkcijos testavimas", "[Studentas]") {
    vector<float> grades{2.0f, 4.0f, 6.0f};
    int examScore = 8;
    Studentas s("Dave", "White", grades, examScore);
    float expectedMean = (2 + 4 + 6) / 3.0f;
    float expectedMed = 4.0f;
    REQUIRE(s.getGalutinisVid() == Approx(expectedMean * 0.4f + examScore * 0.6f));
    REQUIRE(s.getGalutinisMed() == Approx(expectedMed * 0.4f + examScore * 0.6f));
}

// Rule of Five tests

// COPY CONSTRUCTOR
TEST_CASE("COPY CONSTRUCTOR", "[RuleOfFive]") {
    string name = "Johnas";
    string last_name = "Snoop";
    vector<float> grades{2.0f, 4.0f};
    int examScore = 4;

    Studentas A(name, last_name, grades, examScore);
    Studentas B(A);  // < ---- copying

    REQUIRE(B.getVardas()             == A.getVardas() );
    REQUIRE(B.getPavarde()            == A.getPavarde() );
    REQUIRE(B.getPazymiai()           == A.getPazymiai());
    REQUIRE(B.getEgzaminoRezultatas() == A.getEgzaminoRezultatas() );
    REQUIRE(B.getGalutinisVid()       == Approx(A.getGalutinisVid()));
    REQUIRE(B.getGalutinisMed()       == Approx(A.getGalutinisMed()));
}

// MOVE CONSTRUCTOR
TEST_CASE("MOVE CONSTRUCTOR", "[RuleOfFive]") {
    string name = "Johnas";
    string last_name = "Snoop";
    vector<float> grades{2.0f, 4.0f};
    int examScore = 4;

    Studentas A(name, last_name, grades, examScore);

    float oldMean = A.getGalutinisVid();
    float oldMed = A.getGalutinisMed();

    Studentas B(std::move(A));  // moving

    REQUIRE(B.getVardas()             == name);
    REQUIRE(B.getPavarde()            == last_name);
    REQUIRE(B.getPazymiai()           == grades);
    REQUIRE(B.getEgzaminoRezultatas() == examScore);
    REQUIRE(B.getGalutinisVid()       == Approx(oldMean));
    REQUIRE(B.getGalutinisMed()       == Approx(oldMed));

    // A should be empty 
    REQUIRE(A.getEgzaminoRezultatas() == 0);
    REQUIRE(A.getGalutinisVid()       == Approx(0.0f));
    REQUIRE(A.getGalutinisMed()       == Approx(0.0f));
}

// COPY ASSIGNMENT OPERATOR
TEST_CASE("COPY ASSIGNMENT OPERATOR", "[RuleOfFive]") {
    string name = "Johnas";
    string last_name = "Snoop";
    vector<float> grades{2.0f, 4.0f};
    int examScore = 4;

    Studentas A(name, last_name, grades, examScore);
    Studentas B;
    B = A;  // copy assign

    REQUIRE(B.getVardas()             == A.getVardas() );
    REQUIRE(B.getPavarde()            == A.getPavarde() );
    REQUIRE(B.getPazymiai()           == A.getPazymiai());
    REQUIRE(B.getEgzaminoRezultatas() == A.getEgzaminoRezultatas() );
    REQUIRE(B.getGalutinisVid()       == Approx(A.getGalutinisVid()));
    REQUIRE(B.getGalutinisMed()       == Approx(A.getGalutinisMed()));
}

// MOVE ASSIGNMENT OPERATOR
TEST_CASE("MOVE ASSIGNMENT OPERATOR", "[RuleOfFive]") {
    string name = "Johnas";
    string last_name = "Snoop";
    vector<float> grades{2.0f, 4.0f};
    int examScore = 4;

    Studentas A(name, last_name, grades, examScore);

    float oldMean = A.getGalutinisVid();
    float oldMed = A.getGalutinisMed();

    Studentas B;
    B = std::move(A);  // move assign

    REQUIRE(B.getVardas()             == name);
    REQUIRE(B.getPavarde()            == last_name);
    REQUIRE(B.getPazymiai()           == grades);
    REQUIRE(B.getEgzaminoRezultatas() == examScore);
    REQUIRE(B.getGalutinisVid()       == Approx(oldMean));
    REQUIRE(B.getGalutinisMed()       == Approx(oldMed));

    // A should be empty
    REQUIRE(A.getEgzaminoRezultatas() == 0);
    REQUIRE(A.getGalutinisVid() == Approx(0.0f));
    REQUIRE(A.getGalutinisMed() == Approx(0.0f));
}

// FILE READING LOGIC
TEST_CASE("FILE READING LOGIC", "[File][appendingContainerViaFile]"){
    vector <Studentas> student_list;

    REQUIRE_NOTHROW(
      Studentas::appendingContainerViaFile("../Test files/test_input.txt",
            student_list)
    );

    Studentas expected1("Good", "Dog", 
        vector<float>{10.0f, 10.0f, 10.0f},
        10);

    Studentas expected2("Boom", "God", 
        vector<float>{9.0f,  8.0f,  4.0f},
        7);

    REQUIRE(expected1.getVardas()             == student_list[0].getVardas() );
    REQUIRE(expected1.getPavarde()            == student_list[0].getPavarde() );
    REQUIRE(expected1.getPazymiai()           == student_list[0].getPazymiai());
    REQUIRE(expected1.getEgzaminoRezultatas() == student_list[0].getEgzaminoRezultatas() );
    REQUIRE(expected1.getGalutinisVid()       == Approx(student_list[0].getGalutinisVid()));
    REQUIRE(expected1.getGalutinisMed()       == Approx(student_list[0].getGalutinisMed()));

    REQUIRE(expected2.getVardas()             == student_list[1].getVardas() );
    REQUIRE(expected2.getPavarde()            == student_list[1].getPavarde() );
    REQUIRE(expected2.getPazymiai()           == student_list[1].getPazymiai());
    REQUIRE(expected2.getEgzaminoRezultatas() == student_list[1].getEgzaminoRezultatas() );
    REQUIRE(expected2.getGalutinisVid()       == Approx(student_list[1].getGalutinisVid()));
    REQUIRE(expected2.getGalutinisMed()       == Approx(student_list[1].getGalutinisMed()));
}

// PRINT TO FILE LOGIC
TEST_CASE("PRINT TO FILE LOGIC", "[File][print_to_file]") {
    namespace fs = std::filesystem;

    string name = "Gooder";
    string last_name = "Dooger";
    vector<float> grades{9.0f,  8.0f,  4.0f};
    int examScore = 7;

    Studentas A(name, last_name, grades, examScore);
    vector<Studentas> students{ A };

    // Invoke the function under test
    const string outName = "test_output.txt";

    Studentas::print_to_file(students, outName);
    
    // Helper to read a file into a single string
    auto readAll = [&](const string &p) {
        std::ifstream in(p, std::ios::binary);
        std::ostringstream buf;
        buf << in.rdbuf();
        return buf.str();
    };

    string actualContent = readAll("Rezultatai/test_output.txt");
    string expectedContent = readAll("../Test files/expected.txt");

    // 5) Compare them byte-for-byte
    REQUIRE(actualContent == expectedContent);
}
