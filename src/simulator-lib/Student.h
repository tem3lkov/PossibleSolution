#pragma once
#include <iostream>
#include <cstring>


enum class Faculty {
    FRAUD,
    INTERNATIONAL_SCHEMES,
    CREATIVE_NIHILISM,
    SUBJECTIVE_RESEARCHERS,
    FILE_ANALIZIS,
    MICROMANAGEMENT,
    APPLIED_MATERIALIZATION,
    SUBJECTIVISTICS,
    MAGNETISM_AND_CLEARING,
    NUMBER_OF_FACULTIES
};

class Student
{
    public:
        static Faculty getFacultyFromString(const std::string& facultyString);
        static std::string getFacultyString(Faculty faculty);

    public:
        Student(std::size_t FN, std::size_t arrivalTime, std::size_t enthusiasm, Faculty faculty);

        Student();

        // Getters for student's properties
        std::size_t getFN() const;
        std::size_t getArrivalTime() const;
        std::size_t getEnthusiasm() const;
        Faculty getFaculty() const;

        // Operators for comparing students
        bool operator==(const Student& other) const;
        bool operator!=(const Student& other) const;

        bool operator<(const Student& other) const;
        bool operator>(const Student& other) const;

        bool operator<=(const Student& other) const; 
        bool operator>=(const Student& other) const;

    private:
        std::size_t FN;
        std::size_t arrivalTime;
        std::size_t enthusiasm;
        Faculty faculty;

        void setFN(std::size_t _FN);
};