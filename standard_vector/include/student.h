#pragma once

#include "human.h"
#include "my_library.h"

/// \file student.h
/// \brief Declaration of the Studentas class, extending Human to manage grades and compute final scores.

/// \class Studentas
/// \brief Represents a student with homework grades and an exam score,
///        providing calculations for mean- and median-based final grades.
class Studentas : public Human {
    private:
    vector<float> pazymiai;   ///< Homework grades
        int egzaminoRezultatas;    ///< Exam score
        float galutinisVid;        ///< Final grade by average
        float galutinisMed;        ///< Final grade by median
        
    public:
        /// \brief Default constructor.
        Studentas()
            : Human("", ""), egzaminoRezultatas(0),
            galutinisVid(0.0f), galutinisMed(0.0f) {}

        /**
         * \brief Parameterized constructor.
         * Initializes student name, surname, grades vector, and exam result,
         * then computes final grades.
         * \param vardas            First name of the student.
         * \param pavarde           Surname of the student.
         * \param pazymiai          Vector of homework grades.
         * \param egzaminoRezultatas  Integer score of the exam.
         */
        Studentas(const string& vardas,
                const string& pavarde,
                const vector<float>& pazymiai,
                const int& egzaminoRezultatas)
            : Human(vardas, pavarde), pazymiai(pazymiai), egzaminoRezultatas(egzaminoRezultatas) {
            calculate_everything();
        }

        /// \brief Destructor.
        ~Studentas() {
            vardas.clear();
            pavarde.clear();
            pazymiai.clear();
            egzaminoRezultatas = 0;
            galutinisVid = 0.0f;
            galutinisMed = 0.0f;
        }

        /// \brief Copy constructor.
        Studentas(const Studentas& other);

        /// \brief Move constructor.
        Studentas(Studentas&& other) noexcept;

        /// \brief Copy assignment operator.
        Studentas& operator=(const Studentas& other);

        /// \brief Move assignment operator.
        Studentas& operator=(Studentas&& other) noexcept;

        // Setters
        void setVardas(const string& v) { vardas = v; }
        void setPavarde(const string& p) { pavarde = p; }
        void setGrades(const vector<float>& g) { pazymiai = g; }
        void setExam(const int& exam) { egzaminoRezultatas = exam; }

        // Getters
        vector<float> getPazymiai() const { return pazymiai; }
        int getEgzaminoRezultatas() const { return egzaminoRezultatas; }
        float getGalutinisVid() const { return galutinisVid; }
        float getGalutinisMed() const { return galutinisMed; }

        /// \brief Implementation of unused pure virtual from Human.
        void unusedFunction() const override;

        /// \brief Calculate mean of homework grades.
        float calculateMean();

        /// \brief Calculate median of homework grades.
        float calculateMedian();

        /// \brief Compute both mean- and median-based final grades.
        void calculate_everything();

        /// \brief Print surname, name, and final grades.
        friend ostream& operator<<(ostream &out, const Studentas &s);

        /// \brief Prompt for surname, name, grades, and exam; then compute final grades.
        friend std::istream& operator>>(std::istream& in, Studentas& s);

        /// \brief Read students from a text file and append to a container.
        /// \param file_name     Input file name.
        /// \param student_list  Vector to append parsed Studentas objects.
        static void appendingContainerViaFile(string file_name,
            vector<Studentas>& student_list);

        /// \brief Parse student records from a stream.
        /// \param ndCount  Number of grades per record.
        /// \param iss      Input string stream.
        /// \return         Vector of parsed Studentas.
        static vector<Studentas> read_student_records(int ndCount,
                                                    istringstream& iss);

        /// \brief Write a list of students to a text file in "Rezultatai".
        /// \param list_of_students  Vector of Studentas to write.
        /// \param file_name         Name of output file.
        static void print_to_file(vector<Studentas> list_of_students,
                                string file_name);

};