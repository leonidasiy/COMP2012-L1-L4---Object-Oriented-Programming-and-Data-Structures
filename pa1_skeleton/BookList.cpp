#include "BookList.h"
#include "Book.h"

BookList::BookList()
{
    head = nullptr;
}

BookList::BookList(const BookList &other)
{
    if (!other.head) {
        head = nullptr;
        return;
    }

    head = new Node(other.head->data);
    Node *this_cur = head;
    Node *other_cur = other.head->next;
    while (other_cur) {
        this_cur->next = new Node(other_cur->data);
        this_cur = this_cur->next;
        other_cur = other_cur->next;
    }
}

BookList::~BookList()
{
    Node *cur_node = head;
    Node *next_node = nullptr;
    while(cur_node) {
        next_node = cur_node->next;
        // delete cur_node->data;
        delete cur_node;
        cur_node = next_node;
    }
}

bool BookList::isEmpty() const
{
    return !head;
}

void BookList::insertBook(Book *book)
{
    if (isEmpty()) {
        head = new Node(book);
        return;
    }

    Node *cur_node = head;
    while (cur_node->next) {
        if (cur_node->next->data == book) {
            cur_node->next->data->changeInventoryCount(1);
            return;
        }
        cur_node = cur_node->next;
    }
    cur_node->next = new Node(book);
}

void BookList::removeBook(Book *book)
{
    if (isEmpty()) {
        return;
    }

    if (head->data == book) {
        head->data->changeInventoryCount(-1);
        if (head->data->getInventoryCount() < 1) {
            Node *new_head = head->next;
            delete head;
            head = new_head;
        }
        return;
    }
    
    Node *prev_node = head;
    Node *cur_node = prev_node->next;
    while (cur_node) {
        if (cur_node->data == book) {
            cur_node->data->changeInventoryCount(-1);
            if (cur_node->data->getInventoryCount() < 1) {
                prev_node->next = cur_node->next;
                delete cur_node;
            }
            return;
        }
        prev_node = prev_node->next;
        cur_node = prev_node->next;
    }
}

void BookList::displayBooks() const
{
    cout << "Library Book Details:" << endl;
    if (isEmpty()) {
        cout << "The book list is empty." << endl;
    } else {
        Node *cur_node = head;
        while (cur_node) {
            cout << "ID: " << cur_node->data->getId() << " - Title: " << cur_node->data->getTitle() << " - Author: " << cur_node->data->getAuthor() << " - Rating: " << cur_node->data->getRating() << endl;
            cur_node = cur_node->next;
        }
    }
}

void BookList::sortBooks(SortCriteria criteria)
{
    if (isEmpty()) {
        return;
    }

    bool sorted = true;
    if (criteria == BY_RATING) {
        while (sorted) {
            sorted = false;
            Node *prev_node = head;
            Node *cur_node = prev_node->next;
            Book *temp;
            while (cur_node) {
                if (prev_node->data->getRating() < cur_node->data->getRating()) {
                    temp = prev_node->data;
                    prev_node->data = cur_node->data;
                    cur_node->data = temp;
                    sorted = true;
                }
                prev_node = cur_node;
                cur_node = prev_node->next;
            }
        }
    } else {
        // int i = 0;
        while (sorted) {
            // cout << i << "th iteration";
            // i++;
            sorted = false;
            Node *prev_node = head;
            Node *cur_node = prev_node->next;
            Book *temp;
            while (cur_node) {
                if (prev_node->data->getTitle().compare(cur_node->data->getTitle()) > 0) {
                    temp = prev_node->data;
                    prev_node->data = cur_node->data;
                    cur_node->data = temp;
                    sorted = true;
                }
                prev_node = cur_node;
                cur_node = prev_node->next;
            }
        }
    }
}

Book *BookList::searchList(int bookId) const
{
    Node *cur_node = head;
    while(cur_node) {
        if (cur_node->data->getId() == bookId) {
            return cur_node->data;
        }
        cur_node = cur_node->next;
    }
    return nullptr;
}

int BookList::countBooks() const
{
    int count = 0;
    Node *cur_node = head;
    while(cur_node) {
        count += cur_node->data->getInventoryCount();
        cur_node = cur_node->next;
    }
    return count;
}

void BookList::rateBook(int bookId, double newRating)
{
    Book *book = searchList(bookId);
    if (book) {
        book->addRating(newRating);
        cout << "Rating updated for Book " << bookId << ". New rating: " << book->getRating() << endl;
    } else {
        cout << "Book with ID " << bookId << " not found." << endl;
    }
}

Book *BookList::getBookWithMaxRating() const
{
    Book *book = nullptr;
    if (isEmpty()) {
        cout << "The book list is empty." << endl;
        return book;
    }

    Node *cur_node = head;
    double max_rating = -1.0;
    while(cur_node) {
        if (cur_node->data->getRating() > max_rating) {
            book = cur_node->data;
            max_rating = cur_node->data->getRating();
        }
        cur_node = cur_node->next;
    }
    return book;
}

Book *BookList::getBookWithMinRating() const
{
    Book *book = nullptr;
    if (isEmpty()) {
        cout << "The book list is empty." << endl;
        return book;
    }

    Node *cur_node = head;
    double min_rating = 6.0;
    while(cur_node) {
        if (cur_node->data->getRating() < min_rating) {
            book = cur_node->data;
            min_rating = cur_node->data->getRating();
        }
        cur_node = cur_node->next;
    }
    return book;
}

void BookList::reverseBooksByRating()
{
    if (isEmpty()) {
        return;
    }

    bool sorted = true;
    while (sorted) {
        sorted = false;
        Node *prev_node = head;
        Node *cur_node = prev_node->next;
        Book *temp;
        while (cur_node) {
            if (prev_node->data->getRating() > cur_node->data->getRating()) {
                temp = prev_node->data;
                prev_node->data = cur_node->data;
                cur_node->data = temp;
                sorted = true;
            }
            prev_node = cur_node;
            cur_node = prev_node->next;
        }
    }
}