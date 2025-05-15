#include "employee.h"
#include <iostream> // for std::cout, std::endl, etc.

using namespace std;

// Getter methods
string Employee::getName() const
{
    // TODO: Return the name
    return name; 
}

double Employee::getSalary() const
{
    // TODO: Return the salary
    return salary;
}

char Employee::getGender() const
{
    // TODO: Return the gender
    return gender; 
}

string Employee::getTitle() const
{
    // TODO: Return the title
    return title;
}

// Setter methods
void Employee::setName(const string &newName)
{
    // TODO: Set the name
    name = newName;
}

void Employee::setSalary(double newSalary)
{
    // TODO: Set the salary
    salary = newSalary;
}

void Employee::setGender(char newGender)
{
    // TODO: Set the gender
    gender = newGender;
}

void Employee::setTitle(const string &newTitle)
{
    // TODO: Set the title
    title = newTitle;
}

// Print method
void Employee::print() const
{
    // TODO: Print in the format:
    // [Name: <name>, Title: <title>, Gender: <gender>, Salary: <salary>]
    cout << "[Name: " << name << ", Title: " << title << ", Gender: " << gender << ", Salary: " << salary << "]" << endl;
}