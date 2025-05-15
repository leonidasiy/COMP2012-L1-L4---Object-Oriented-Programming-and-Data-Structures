#include "company.h"
#include <iostream>
using namespace std;

void Company::init() 
{
    // TODO
    currSize = 0;
    for (Employee *&employee : employees) {
        employee = nullptr;
    }
}

void Company::addEmployee(Employee* emp)
{
    // Check if the employee already exists by name
    if (hasEmployee(emp->getName())) {
        cout << "Employee " << emp->getName() << " already exists in the company" << endl;
        return;
    }

    // Check if company is full
    if (currSize == COMPANY_MAX_SIZE) {
        cout << "Company is full" << endl;
        return;
    }

    // Otherwise, add the employee
    employees[currSize] = emp;
    currSize++;
    cout << "Employee " << emp->getName() << " is hired" << endl;
}

int Company::findEmployee(const string& empName) const
{
    // TODO
    for (int i = 0; i < currSize; i++) {
        if (employees[i]->getName() == empName) {
            return i;
        }
    }
    return -1;
}

bool Company::hasEmployee(const string& empName) const
{
    return findEmployee(empName) != -1;
}

void Company::fireEmployee(const string& empName)
{
    // TODO
    int i = findEmployee(empName);
    if (i != -1) {
        for (int j = i; j < currSize - 1; j++) {
            employees[j] = employees[j + 1];
        }
        employees[currSize - 1] = nullptr;
        currSize--;
        cout << "Employee " << empName << " is fired" << endl;
    } else {
        cout << "Employee " << empName << " is not found in the company" << endl;
    }
}

void Company::promoteEmployee(const string& empName, const string& newTitle)
{
    // TODO
    int i = findEmployee(empName);
    if (i != -1) {
        employees[i]->setTitle(newTitle);
        cout << "Employee " << empName << " is promoted to " << newTitle << endl;
    } else {
        cout << "Employee " << empName << " is not found in the company" << endl;
    }
}

void Company::adjustSalary(const string& empName, double amount)
{
    // Find the employee to adjust the salary.
    int index = findEmployee(empName);
    if (index == -1) {
        cout << "Employee " << empName << " is not found in the company" << endl;
        return;
    }

    // Adjust the salary.
    double updatedSalary = employees[index]->getSalary() + amount;
    employees[index]->setSalary(updatedSalary);
    cout << "Employee " << empName << "'s salary is changed by " << amount << endl;
}

void Company::print() const
{
    // TODO
    cout << "Company with " << currSize << " employees:" << endl;
    for (int i = 0; i < currSize; i++) {
        cout << "    ";
        employees[i]->print();
    }
}