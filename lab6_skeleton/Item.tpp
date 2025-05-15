#include "Item.h"
// ================== CLASS TEMPLATE DEFINITIONS ==================

template <typename T>
Item<T>::Item(const string& name, T value, T weight)
    : name(name), value(value), weight(weight)
{
}


// ================== SAME-TYPE OPERATORS ==================

// Task 1.1: Implement operator+ (Item<T> + Item<T>) => Item<T>
template <typename T>
Item<T> Item<T>::operator+(const Item<T>& other) const {
    // TODO: Task 1.1
    // Notice: For the returned Item<T>, Keep the same name as this->name.
    string name = this->name;
    T value = this->value + other.value;
    T weight = this->weight + other.weight;
    return Item<T>(name, value, weight);
}

// Task 1.2: Implement operator* (Item<T> * T) => Item<T>
template <typename T>
Item<T> Item<T>::operator*(const T &scalar) const {
    // TODO: Task 1.2
    // Notice: For the returned Item<T>, Keep the same name as this->name.
    string name = this->name;
    T value = this->value * scalar;
    T weight = this->weight * scalar;
    return Item<T>(name, value, weight);
}

// Task 2: Implement operator==
template <typename T>
bool Item<T>::operator==(const Item<T>& other) const {
    // TODO: Task 2
    if (this->name == other.name && this->value == other.value && this->weight == other.weight) {
        return true;
    }
    return false;
}

// Task 3: Implement operator<
template <typename T>
bool Item<T>::operator<(const Item<T>& other) const {
    // TODO: Task 3
    if (this->value < other.value) {
        return true;
    }
    return false;
}

template <typename U>
ostream& operator<<(ostream& os, const Item<U>& i) {
    os << i.name << " (Value: " << i.value 
       << ", Weight: " << i.weight << ")";
    return os;
}

// --------------------------------------------------------------------
// CROSS-TYPE FREE FUNCTIONS (Always returning Item<double>)
// --------------------------------------------------------------------
// Task 4.1: Implement operator+ (Item<T1> + Item<T2>) => Item<double>
template <typename T1, typename T2>
Item<double> operator+(const Item<T1>& lhs, const Item<T2>& rhs) {
    // TODO: Task 4.1
    // Notice: For the returned Item<T>, Keep the same name as lhs->name.
    string name = lhs.name;
    double value = lhs.value + rhs.value * 1.0;
    double weight = lhs.weight + rhs.weight * 1.0;
    return Item<double>(name, value, weight);
}

// Task 4.1: Implement operator* (Item<T1> * T2) => Item<double>
template <typename T1, typename T2>
Item<double> operator*(const Item<T1>& item, const T2& scalar) {
    // TODO: Task 4.2
    string name = item.name;
    double value = item.value * scalar * 1.0;
    double weight = item.weight * scalar * 1.0;
    return Item<double>(name, value, weight);
}
