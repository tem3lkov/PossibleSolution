#pragma once
#include "Student.h"

struct StudentExitTimePair {
    Student student;
    std::size_t exitTime;

    bool operator<(const StudentExitTimePair& other) const
    {
        return exitTime < other.exitTime;
    }

    bool operator>(const StudentExitTimePair& other) const
    {
        return exitTime > other.exitTime;
    }

    bool operator<=(const StudentExitTimePair& other) const
    {
        return exitTime <= other.exitTime;
    }
    
    bool operator>=(const StudentExitTimePair& other) const
    {
        return exitTime >= other.exitTime;
    }
};