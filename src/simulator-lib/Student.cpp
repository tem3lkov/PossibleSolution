#include "Student.h"

Faculty Student::getFacultyFromString(const std::string &facultyString)
{
    if (facultyString == "Fraud") {
        return Faculty::FRAUD;
    } else if (facultyString == "International Schemes") {
        return Faculty::INTERNATIONAL_SCHEMES;
    } else if (facultyString == "Creative Nihilism")
    {
        return Faculty::CREATIVE_NIHILISM;
    } else if (facultyString == "Subjective Researches")
    {
        return Faculty::SUBJECTIVE_RESEARCHERS;
    } else if (facultyString == "File Analizis")
    {
        return Faculty::FILE_ANALIZIS;
    } else if (facultyString == "Micromanagement")
    {
        return Faculty::MICROMANAGEMENT;
    } else if (facultyString == "Applied Materialization")
    {
        return Faculty::APPLIED_MATERIALIZATION;
    } else if (facultyString == "Subjectivistics")
    {
        return Faculty::SUBJECTIVISTICS;
    } else if (facultyString == "Magnetism and Clearing")
    {
        return Faculty::MAGNETISM_AND_CLEARING;
    } else {
        throw std::invalid_argument("Invalid faculty");
    }
}

std::string Student::getFacultyString(Faculty faculty)
{
    switch (faculty)  {
        case Faculty::FRAUD:
            return "Fraud";
        case Faculty::INTERNATIONAL_SCHEMES:
            return "International Schemes";
        case Faculty::CREATIVE_NIHILISM:
            return "Creative Nihilism";
        case Faculty::SUBJECTIVE_RESEARCHERS:
            return "Subjective Researches";
        case Faculty::FILE_ANALIZIS:
            return "File Analizis";
        case Faculty::MICROMANAGEMENT:
            return "Micromanagement";
        case Faculty::APPLIED_MATERIALIZATION:
            return "Applied Materialization";
        case Faculty::SUBJECTIVISTICS:
            return "Subjectivistics";
        case Faculty::MAGNETISM_AND_CLEARING:
            return "Magnetism and Clearing";
        default:
            throw std::invalid_argument("Invalid faculty");
    }
}

Student::Student(std::size_t _FN, std::size_t _arrivalTime, std::size_t _enthusiasm, Faculty _faculty)
    : FN(0), arrivalTime(_arrivalTime), enthusiasm(_enthusiasm), faculty(_faculty)
{
    setFN(_FN);
}  

Student::Student(): Student(0,0,0,Faculty::FRAUD) {}

std::size_t Student::getFN() const
{
    return FN;
}

std::size_t Student::getArrivalTime() const
{
    return arrivalTime;
}

std::size_t Student::getEnthusiasm() const
{
    return enthusiasm;
}


Faculty Student::getFaculty() const
{
    return faculty;
}

bool Student::operator==(const Student& other) const
{
    return FN == other.FN;
}

bool Student::operator!=(const Student& other) const
{
    return !(*this == other);
}

bool Student::operator<(const Student& other) const
{
    return arrivalTime < other.arrivalTime;
}

bool Student::operator>(const Student& other) const
{
    return arrivalTime > other.arrivalTime;
}

bool Student::operator<=(const Student& other) const
{
    return arrivalTime <= other.arrivalTime;
}

bool Student::operator>=(const Student& other) const
{
    return arrivalTime >= other.arrivalTime;
}

void Student::setFN(std::size_t _FN)
{
    // FN should be less then 9 digits
    if (_FN > 999999999) {
        throw std::invalid_argument("FN should be less then 9 digits");
    }
    FN = _FN;
}

