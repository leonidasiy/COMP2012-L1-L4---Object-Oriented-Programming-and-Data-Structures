#include "User.h"
#include "Book.h"

User::User()
{
    userId = 0;
    name = "";
    numBooksBorrowed = 0;
    maxBooks = 5;
    booksBorrowed = new Book *[maxBooks];
    for (int i = 0; i < maxBooks; ++i) {
        booksBorrowed[i] = nullptr;
    }
}

User::User(int id, const string &n, int borrow, int max)
{
    userId = id;
    name = n;
    numBooksBorrowed = borrow;
    maxBooks = max;
    booksBorrowed = new Book *[maxBooks];
    for (int i = 0; i < maxBooks; ++i) {
        booksBorrowed[i] = nullptr;
    }
}

User::~User()
{
    for (int i = 0; i < maxBooks && booksBorrowed[i]; ++i) {
        delete booksBorrowed[i];
    }
    delete[] booksBorrowed;
}

void User::borrowBook(Book *book)
{
    if (numBooksBorrowed == maxBooks) {
        cout << "You cannot borrow more books." << endl;
    } else if (book->getInventoryCount() < 1) {
        cout << "This book is currently unavailable." << endl;
    } else {
        int i = 0;
        for (; i < maxBooks && booksBorrowed[i]; ++i) {
            if (booksBorrowed[i]->getId() == book->getId()) {
                booksBorrowed[i]->changeInventoryCount(1);
                numBooksBorrowed++;
                book->changeInventoryCount(-1);
                cout << "Successfully borrowed: "<< book->getTitle() << endl;
                return;
            }
        }
        booksBorrowed[i] = new Book(book->getId(), book->getTitle(), book->getAuthor());
        numBooksBorrowed++;
        book->changeInventoryCount(-1);
        cout << "Successfully borrowed: "<< book->getTitle() << endl;
    }
}

void User::returnBook(Book *book)
{
    for (int i = 0; i < maxBooks && booksBorrowed[i]; ++i) {
        if (booksBorrowed[i]->getId() == book->getId()) {
            booksBorrowed[i]->changeInventoryCount(-1);
            if (booksBorrowed[i]->getInventoryCount() < 1) {
                delete booksBorrowed[i];
                int j = i + 1;
                while (j < maxBooks && booksBorrowed[j]) {
                    booksBorrowed[i] = booksBorrowed[j];
                    ++j;
                }
                booksBorrowed[j-1] = nullptr;
            }
            --numBooksBorrowed;
            book->changeInventoryCount(1);
            cout << "Successfully returned: " << book->getTitle() << endl;
            return;
        }
    }
    cout << "This book was not borrowed by you." << endl;
}

int User::getNumBooksBorrowed() const
{
    return numBooksBorrowed;
}

int User::getUserId() const
{
    return userId;
}

string User::getUserName() const
{
    return name;
}

int User::getMaxBooks() const
{
    return maxBooks;
}

void User::viewBorrowedBooks() const
{
    // cout << booksBorrowed[0];
    // cout << !booksBorrowed[0];
    if (!booksBorrowed[0]) {
        cout << name << " has not borrowed any books." << endl;
    } else {
        bool sorted = true;
        while (sorted) {
            sorted = false;
            int i = 1;
            // Book *prev_book = booksBorrowed[i];
            // Book *cur_book = booksBorrowed[i+1];
            Book *temp;
            while (i < maxBooks && booksBorrowed[i]) {
                if (booksBorrowed[i]->getTitle().compare(booksBorrowed[i-1]->getTitle()) > 0) {
                    temp = booksBorrowed[i];
                    booksBorrowed[i] = booksBorrowed[i-1];
                    booksBorrowed[i-1] = temp;
                    sorted = true;
                }
                ++i;
                // prev_book = cur_book;
                // cur_book = booksBorrowed[(++i)+1];
            }
        }

        cout << name << "'s Borrowed Books:" << endl;
        for (int i = 0; i < maxBooks && booksBorrowed[i]; ++i) {
            Book *&book = booksBorrowed[i];
            cout << book->getTitle() << " (x" << book->getInventoryCount() << ")" << endl;
        }
    }
}

void User::giveRating(BookList &list, int bookId, double newRating)
{
    if (numBooksBorrowed == maxBooks) {
        cout << "User is blocked and cannot rate books." << endl;
    } else {
        list.rateBook(bookId, newRating);
    }
}

void User::updateMaxBooks(int additionalSlots)
{
    if (additionalSlots < 1) {
        cout << "Invalid number of additional slots." << endl;
    } else {
        int temp = maxBooks;
        maxBooks += additionalSlots;
        Book **temp_arr = booksBorrowed;
        booksBorrowed = new Book *[maxBooks];
        for (int i = 0; i < maxBooks; ++i) {
            if (i < temp) {
                booksBorrowed[i] = temp_arr[i];
            } else {
                booksBorrowed[i] = nullptr;
            }
        }
        delete[] temp_arr;
        cout << "Max books updated to: " << maxBooks << endl;
    }
}