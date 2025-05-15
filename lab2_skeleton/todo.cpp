#include "class.h"
#include <iostream>
#include <cstring>

using namespace std;

// Student constructor
Student::Student(const char* name)
{
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
    classes = new Class*[2];
    classCount = 0;
    classCapacity = 2;
    cout << "Student: " << name << " initialized!" << endl;
}

// Student destructor
Student::~Student() {
    int count = classCount;
    for (int i = 0; i < count; i++) {
        Class* cls = classes[0];
        cls->dropStudent(this);
    }
    cout << "Student: " << name << " destroyed!" << endl;
    delete[] name;
    delete[] classes;
}

// Class constructor
Class::Class(const char* name, int capacity) {
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
    students = new Student*[capacity];
    studentCount = 0;
    this->capacity = capacity;
    cout << "Class: " << name << " created with capacity " << capacity << "." << endl;
}

// Class destructor
Class::~Class() {
    cout << "Class: " << name << " destroyed." << endl;
    delete[] name;  
    delete[] students;
}



// Enroll a student in the class
bool Class::enrollStudent(Student* student) {
    if (studentCount == capacity) {
        cout << "Class " << name << " is full. Cannot enroll student!" << endl;
        return false;
    }

    students[studentCount++] = student;
    student->enrollInClass(this);
    cout << "Student " << student->getName() << " enrolled in class " << name << "." << endl;
    return true;
}

// Drop a student from the class
bool Class::dropStudent(Student* student) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i] == student) {
            for (int j = i; j < studentCount-1; j++) {
                students[j] = students[j+1];
            }
            // students[--studentCount] = nullptr;
            --studentCount;
            student->dropClass(this);
            cout << "Student " << student->getName() << " dropped from class " << name << "." << endl;
            return true;
        }
    }

    cout << "Student " << student->getName() << " is not in class " << name << "." << endl;
    return false;
}