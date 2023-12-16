#include "bar-simulator.h"
#include "LinkedList.h"
#include "Student.h"
#include "Bar.h"
#include "Group.h"
#include "StudentExitPair.h"
#include <iostream>

///
/// @brief Simulate the student bar problem
///
/// @param input
///   The stream, which contains the simulation commands
/// @param output
///   The stream, where the steps of simulation have to be printed.
///
void simulate_bar(std::istream& input, std::ostream& output)
{
    // K = club capacity
    std::size_t K = 0;
    input >> K;

    // G = number of max people in the group
    std::size_t G = 0;
    input >> G;

    // N = number of students
    std::size_t N = 0;
    input >> N;

    // Check for edge cases
    if((K == 0 && G == 0 && N == 0) || N == 0)
    {
        return;
    }
    else if (K == 0) 
    {
        throw std::runtime_error("The simulation parameters are incorrect: No club capacity");
    }
    else if (G == 0) 
    {
        throw std::runtime_error("The simulation parameters are incorrect: No group capacity");
    }


    // Queue for the students
    LinkedList<Student> studentQueue;;
    
    // Read the input
    for(int i = 0; i < N; i++)
    {
        try
        {
            // have dummy variable that checks if students arrive in incorrect (not monotonous) arrival time
            std::size_t lastArrivalTime = 0;


            int FN, arrivalTime, enthusiasm;
            std::string facultyString, wholeString;

            // Read the FN and arrival time from the input
            input >> FN >> arrivalTime;

            // Check if the students arrive in incorrect (not monotonous) arrival time
            if(arrivalTime < lastArrivalTime)
            {
                throw std::invalid_argument("Invalid input");
            }
            lastArrivalTime = arrivalTime;

            // Get the rest of the string due to spaces in the faculty name
            std::getline(input, wholeString, '\n');

            // Get the faculty name and enthusiasm
            std::size_t lastSpace = wholeString.find_last_of(' ');
            facultyString = wholeString.substr(1, lastSpace -1);

            enthusiasm = std::stoi (wholeString.substr(lastSpace + 1));

            // Check if the input is valid
            if(FN < 0 || arrivalTime < 0 || enthusiasm < 0)
            {
                throw std::invalid_argument("Invalid input");
            }

            Student student(FN, arrivalTime, enthusiasm, Student::getFacultyFromString(facultyString));
            studentQueue.push(student);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            throw incorrect_simulation("The simulation parameters are incorrect");
        }      
    }

    // Sort the queue by arrival time
    studentQueue.sort();

    // Add a group queue for the groups
    LinkedList<Group> groupQueue;

    // Create the bar with capacity K
    Bar bar(K);

    // Start of the simulation
    std::size_t time = 0;
    while(!studentQueue.empty() || !bar.empty())
    {
        // Remove the students that have to leave the bar
        while(!bar.empty() && bar.getStudents().front().exitTime <= time)
        {
            output << time << " " << bar.getStudents().front().student.getFN() << " exit" << std::endl;
            bar.removeStudent();
        }

        // Add the students that have arrived to a group
        while(!studentQueue.empty() && studentQueue.front().getArrivalTime() <= time)
        {
            std::size_t studentCountBefore = studentQueue.getSize();

            // Find if for the new student there is a group with the same faculty
            for(Group& group : groupQueue )
            {
                if(group.getGroupFaculty() == studentQueue.front().getFaculty() && group.getGroupSize() < group.getGroupCapacity())
                {
                    group.addStudent(studentQueue.front());
                    studentQueue.pop_front();
                    break;
                }
            }

            if(studentQueue.getSize() == studentCountBefore)
            {
                // If there is no group with the same faculty, create a new one
                Group newGroup(G, studentQueue.front().getFaculty());
                newGroup.addStudent(studentQueue.front());
                studentQueue.pop_front();
                groupQueue.push(newGroup);
            }            
        }


        // Check if there is a group that can enter the bar
        LinkedList<Group>::Iterator it = groupQueue.begin();
        while (!bar.full() && it != groupQueue.end()) {
            Group& group = *it;

            if (group.getGroupSize() <= bar.getBarCapacity() - bar.getBarSize()) {
                for (Student& student : group.getStudents()) {
                    bar.addStudent(student, time);
                    output << time << " " << student.getFN() << " enter" << std::endl;
                }

                it = groupQueue.erase(it); 
            } else {
                ++it; 
            }
        }
        time++;
    }
}
