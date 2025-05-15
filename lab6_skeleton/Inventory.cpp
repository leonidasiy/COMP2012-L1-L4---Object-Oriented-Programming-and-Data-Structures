#include "Inventory.h"
#include <algorithm>

// Default constructor
Inventory::Inventory() : items(nullptr), size(0) {}

// Copy constructor
Inventory::Inventory(const Inventory& other)
    : items(nullptr), size(0)
{
    if (other.size > 0) {
        size = other.size;
        items = new Item<int>[size];
        for (int i = 0; i < size; i++) {
            items[i] = other.items[i];
        }
    }
}

// Destructor
Inventory::~Inventory() {
    delete[] items;
}

// Task 5: Implement operator=
Inventory& Inventory::operator=(const Inventory& other) {
    // TODO: Task 5
    if (this == &other) {
        return *this;
    }
    size = other.size;
    Item<int>* copy = new Item<int>[size];
    for (int i = 0; i < size; i++) {
        copy[i] = other.items[i];
    }
    items = copy;
    return *this;
}

// Task 6: Implement operator+
Inventory operator+(const Inventory& lhs, const Inventory& rhs) {
    // TODO: Task 6
    int total_size = lhs.size + rhs.size;
    Item<int>* all_items = new Item<int>[total_size];
    for (int i = 0; i < total_size; i++) {
        all_items[i] = i < lhs.size ? lhs.items[i] : rhs.items[i - lhs.size];
    }
    Inventory new_inv = Inventory();
    new_inv.items = all_items;
    new_inv.size = total_size;
    return new_inv;
}

// Add an item to the end of the inventory
void Inventory::addItem(const Item<int>& newItem) {
    Item<int>* temp = new Item<int>[size + 1];
    for (int i = 0; i < size; i++) {
        temp[i] = items[i];
    }
    temp[size] = newItem;
    delete[] items;
    items = temp;
    size++;
}

// Printing the inventory
std::ostream& operator<<(std::ostream& os, const Inventory& inv) {
    os << "[";
    for (int i = 0; i < inv.size; i++) {
        os << inv.items[i];
        if (i < inv.size - 1) os << ", ";
    }
    os << "]";
    return os;
}