#include <iostream>
#include <string>
#include <vector>
#include <algorithm>  // For transform()
using namespace std;

class Book {
public:
    int id;
    string title, author, publisher, issuedTo;
    bool isIssued;

    Book(int id, string title, string author, string publisher) 
        : id(id), title(title), author(author), publisher(publisher), isIssued(false), issuedTo("") {}

    void displayBookDetails() {
        cout << id << " | " << title << " | " << author << " | "
             << (isIssued ? "Issued to " + issuedTo : "Available") << endl;
    }
};

class Library {
    vector<Book> books;

    Book* findBookById(int id) {
        for (auto& book : books) {
            if (book.id == id) return &book;
        }
        return nullptr;
    }

public:
    void addBook(int id, string title, string author, string publisher) {
        if (findBookById(id)) {
            cout << "A book with ID " << id << " already exists.\n";
            return;
        }
        books.push_back(Book(id, title, author, publisher));
        cout << "Book added successfully.\n";
    }

    void searchBookById(int id) {
        Book* book = findBookById(id);
        if (book) {
            cout << "Book found by ID " << id << ": " << book->title << " by " << book->author << endl;
        } else {
            cout << "Book not found.\n";
        }
    }

    void issueBook(int id, string issuedTo) {
        Book* book = findBookById(id);
        if (book) {
            if (!book->isIssued) {
                book->isIssued = true;
                book->issuedTo = issuedTo;
                cout << "Book with ID " << id << " has been issued to " << issuedTo << ".\n";
            } else {
                cout << "Book already issued to " << book->issuedTo << ".\n";
            }
        } else {
            cout << "Book not found.\n";
        }
    }

    void returnBook(int id) {
        Book* book = findBookById(id);
        if (book) {
            if (book->isIssued) {
                book->isIssued = false;
                book->issuedTo = "";
                cout << "Book with ID " << id << " has been returned.\n";
            } else {
                cout << "Book was not issued.\n";
            }
        } else {
            cout << "Book not found.\n";
        }
    }

    void deleteBook(int id) {
        auto it = remove_if(books.begin(), books.end(), [id](Book& book) {
            return book.id == id;
        });

        if (it != books.end()) {
            books.erase(it, books.end());
            cout << "Book with ID " << id << " has been deleted.\n";
        } else {
            cout << "Book not found.\n";
        }
    }

    void displayAllBooks() {
        if (books.empty()) {
            cout << "No books available in the library.\n";
            return;
        }
        cout << "All Books:\n";
        for (auto& book : books) {
            book.displayBookDetails();
        }
    }
};

int main() {
    Library lib;
    lib.addBook(2, "1984", "George Orwell", "Penguin");
    lib.addBook(1, "The Great Gatsby", "F. Scott Fitzgerald", "Scribner");
    lib.addBook(3, "To Kill a Mockingbird", "Harper Lee", "J.B. Lippincott & Co.");

    cout << "\nAll books after adding:\n";
    lib.displayAllBooks();

    cout << "\nSearch for a book by ID:\n";
    lib.searchBookById(2);

    cout << "\nIssue a book:\n";
    lib.issueBook(2, "John Doe");

    cout << "\nAll books after issuing:\n";
    lib.displayAllBooks();

    cout << "\nReturn a book:\n";
    lib.returnBook(2);

    cout << "\nAll books after returning:\n";
    lib.displayAllBooks();

    cout << "\nDelete a book:\n";
    lib.deleteBook(1);

    cout << "\nAll books after deletion:\n";
    lib.displayAllBooks();

    return 0;
}
