#include "Group.h"

Group::Group(std::size_t _size, Faculty _faculty)
: capacity(_size), faculty(_faculty) {}

std::size_t Group::getGroupCapacity() const
{
    return capacity;
}

std::size_t Group::getGroupSize() const
{
    return students.getSize();
}

Faculty Group::getGroupFaculty() const
{
    return faculty;
}

LinkedList<Student> Group::getStudents() const
{
    return students;
}

void Group::addStudent(Student& student)
{
    students.push(student);
}
