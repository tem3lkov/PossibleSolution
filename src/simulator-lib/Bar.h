#pragma once
#include "LinkedList.h"
#include "StudentExitPair.h"
#include "Student.h"

class Bar
{
    public:
        Bar(std::size_t _capacity);

        std::size_t getBarCapacity() const;
        std::size_t getBarSize() const;
        std::size_t empty() const;
        std::size_t full() const;

        LinkedList<StudentExitTimePair> getStudents() const;

        void addStudent(Student &student, std::size_t arrivalTime);
        void removeStudent();

    private:
        std::size_t capacity;
        LinkedList<StudentExitTimePair> students;
};