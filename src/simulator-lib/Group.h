#pragma once
#include "LinkedList.h"
#include "Student.h"

class Group
{
    public:
        Group(std::size_t _capacity, Faculty _faculty);

        std::size_t getGroupCapacity() const;
        std::size_t getGroupSize() const;
        
        Faculty getGroupFaculty() const;
        LinkedList<Student> getStudents() const;

        void addStudent(Student& student);
    private:
        std::size_t capacity;
        LinkedList<Student> students;
        Faculty faculty;
};