#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// Book structure
struct Book {
    string title;
    string author;
    int yearPublished;
    bool isAvailable;

    Book(string title, string author, int yearPublished) {
        this->title = title;
        this->author = author;
        this->yearPublished = yearPublished;
        this->isAvailable = true;
    }
};

// Borrower structure
struct Borrower {
    string name;
    string contact;
    vector<Book*> borrowedBooks;

    Borrower(string name, string contact) {
        this->name = name;
        this->contact = contact;
    }
};

class LibraryManagementSystem {
private:
    map<string, Book*> books; // Map book title to book object
    map<string, Borrower*> borrowers; // Map borrower name to borrower object

public:
    // Add a new book
    void addBook(string title, string author, int yearPublished) {
        Book* book = new Book(title, author, yearPublished);
        books[title] = book;
    }

    // Add a new borrower
    void addBorrower(string name, string contact) {
        Borrower* borrower = new Borrower(name, contact);
        borrowers[name] = borrower;
    }

    // Borrow a book
    bool borrowBook(string borrowerName, string bookTitle) {
        Borrower* borrower = borrowers[borrowerName];
        Book* book = books[bookTitle];

        if (borrower != nullptr && book != nullptr && book->isAvailable) {
            borrower->borrowedBooks.push_back(book);
            book->isAvailable = false;
            cout << bookTitle << " borrowed successfully by " << borrowerName << endl;
            return true;
        } else {
            cout << "Borrowing failed: ";
            if (borrower == nullptr) {
                cout << "Borrower not found." << endl;
            } else if (book == nullptr) {
                cout << "Book not found." << endl;
            } else {
                cout << "Book is not available." << endl;
            }
            return false;
        }
    }

    // Return a book
    bool returnBook(string borrowerName, string bookTitle) {
        Borrower* borrower = borrowers[borrowerName];
        Book* book = books[bookTitle];

        if (borrower != nullptr && book != nullptr) {
            auto it = find(borrower->borrowedBooks.begin(), borrower->borrowedBooks.end(), book);
            if (it != borrower->borrowedBooks.end()) {
                borrower->borrowedBooks.erase(it);
                book->isAvailable = true;
                cout << bookTitle << " returned successfully by " << borrowerName << endl;
                return true;
            } else {
                cout << borrowerName << " has not borrowed this book." << endl;
                return false;
            }
        } else {
            cout << "Returning failed: ";
            if (borrower == nullptr) {
                cout << "Borrower not found." << endl;
            } else if (book == nullptr) {
                cout << "Book not found." << endl;
            }
            return false;
        }
    }

    // List all books
    void listBooks() {
        if (books.empty()) {
            cout << "No books available in the library." << endl;
        } else {
            cout << "List of Books:" << endl;
            for (auto bookPair : books) {
                cout << bookPair.first << " - " << bookPair.second->author << " (" << bookPair.second->yearPublished << ")"
                     << (bookPair.second->isAvailable ? " (Available)" : " (Borrowed)") << endl;
            }
        }
    }

    // List borrowed books for a borrower
    void listBorrowedBooks(string borrowerName) {
        Borrower* borrower = borrowers[borrowerName];

        if (borrower != nullptr) {
            if (borrower->borrowedBooks.empty()) {
                cout << borrowerName << " has not borrowed any books." << endl;
            } else {
                cout << "Books borrowed by " << borrowerName << ":" << endl;
                for (Book* book : borrower->borrowedBooks) {
                    cout << book->title << endl;
                }
            }
        } else {
            cout << "Borrower not found." << endl;
        }
    }
};

int main() {
    LibraryManagementSystem library;

    // Add some sample books
    library.addBook("The Lord of the Rings", "J. R. R. Tolkien", 1954);
    library.addBook("Pride and Prejudice", "Jane Austen", 1813);
    library.addBook("To Kill a Mockingbird", "Harper Lee", 1960);

    // Add some sample borrowers
    library.addBorrower("Alice", "alice@example.com");
    library.addBorrower("Bob", "bob@example.com");

    // Borrow and return books
    library.borrowBook("Alice", "The Lord of the Rings");
    library.borrowBook("Bob", "Pride and Prejudice");
    library.returnBook("Alice", "The Lord of the Rings");

    // List all books
    library.listBooks();

    // List borrowed books for Alice
    library.listBorrowedBooks("Alice");

    return 0;
}
