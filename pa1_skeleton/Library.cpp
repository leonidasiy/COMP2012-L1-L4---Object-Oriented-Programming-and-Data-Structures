#include "Library.h"

// Constructor
Library::Library(int initialCapacity)
{
    userCount = 0;
    capacity = initialCapacity;
    totalRevenue = 0.0;
    libraryInventory = BookList();

    users = new User *[capacity];
    for (int i = 0; i < capacity; ++i) {
        users[i] = nullptr;
    }
}

// Destructor
Library::~Library()
{
    for (int i = 0; i < userCount; ++i) {
        delete users[i];
    }
    delete[] users;
}

void Library::addUser(int id, const string &name)
{
    if (userCount == capacity) {
        capacity *= 2;
        User **temp = users;
        users = new User *[capacity];
        for (int i = 0; i < capacity; ++i) {
            if (i < userCount) {
                users[i] = temp[i];
            } else {
                users[i] = nullptr;
            }
        }
        delete[] temp;
    }
    users[userCount++] = new User(id, name);
    totalRevenue += 5.0;
}

void Library::upgradeUserSlots(int userId, int additionalSlots)
{
    for (int i = 0; i < userCount; ++i) {
        if (users[i]->getUserId() == userId) {
            users[i]->updateMaxBooks(additionalSlots);
            totalRevenue += additionalSlots;
            cout << "User ID " << userId << " upgraded by " << additionalSlots << " slots." << endl;
            return;
        }
    }
    cout << "User ID " << userId << " not found." << endl;
}

double Library::getTotalRevenue() const
{
    return totalRevenue;
}

void Library::displayUsers() const
{
    for (int i = 0; i < userCount; ++i) {
        User *&user = users[i];
        cout << "User ID: " << user->getUserId() << ", Name: " << user->getUserName() << ", Borrowed Books: " << user->getNumBooksBorrowed() << ", Max Books: " << user->getMaxBooks() << endl;
    }
}

User *Library::getUserById(int userId) const
{
    for (int i = 0; i < userCount; ++i) {
        if (users[i]->getUserId() == userId) {
            return users[i];
        }
    }
    return nullptr;
}

void Library::addNewBook(Book *book)
{
    if (totalRevenue < 2) {
        cout << "Insufficient funds to add the book '" << book->getTitle() << "'." << endl;
    } else {
        totalRevenue -= 2;
        libraryInventory.insertBook(book);
        cout << "Book '" << book->getTitle() << "' added to the library." << endl;
    }
}

void Library::removeBook(int bookId)
{
    Book *book = libraryInventory.searchList(bookId);
    if (book) {
        int copies = book->getInventoryCount();
        for (int i = 0; i < copies; ++i) {
            libraryInventory.removeBook(book);
            totalRevenue++;
        }
    } else {
        cout << "Book with ID " << bookId << " not found in the library." << endl;
    }
}

void Library::displayBooks() const
{
    libraryInventory.displayBooks();
}

BookList &Library::getLibraryInventory()
{
    return libraryInventory;
}