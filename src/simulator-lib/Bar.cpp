#include "Bar.h"

Bar::Bar(std::size_t _capacity)
: capacity(_capacity) {}

std::size_t Bar::getBarCapacity() const
{
    return capacity;
}

std::size_t Bar::getBarSize() const
{
    return students.getSize();
}

std::size_t Bar::empty() const
{
    return students.empty();
}

std::size_t Bar::full() const
{
    return students.getSize() == capacity;
}

LinkedList<StudentExitTimePair> Bar::getStudents() const
{
    return students;
}

void Bar::addStudent(Student &student, std::size_t arrivalTime)
{
    StudentExitTimePair pair;
    pair.student = student;
    pair.exitTime = arrivalTime + student.getEnthusiasm();

    students.push(pair);
    students.sort();
}

void Bar::removeStudent(){
    students.pop_front();
};