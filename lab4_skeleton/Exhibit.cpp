#include <iostream>
#include "Exhibit.h"
//TODO 1.1: complete the constructor of Exhibit (name and area_code)
Exhibit::Exhibit(const string& name, int area_code) {
    this->name = name;
    this->area_code = area_code;
    this->type = ""; //Set the default empty type
}
//TODO 1.2: complete the get_name(), get_area_code()
string Exhibit::get_name() const {
    return name;
}

int Exhibit::get_area_code() const {
    return area_code;
}

