/*
 * Project: High-Performance Library Management System
 * Author: [유영준]
 * Description: 
 * A C++ based library management system implementing BST and Hash Table 
 * from scratch to optimize search time complexities.
 * - Search by ID: O(1) using Hash Table (Chaining)
 * - Search by Title: O(log N) using Binary Search Tree
 */

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iomanip>

using namespace std;

// 도서 정보 구조체
struct Book {
    int id;
    string title;
    string author;
    bool isAvailable;

    Book(int _id, string _title, string _author) 
        : id(_id), title(_title), author(_author), isAvailable(true) {}
        
    void printDetails() const {
        cout << "[" << id << "] " 
             << left << setw(25) << title 
             << " | " << left << setw(15) << author 
             << " | " << (isAvailable ? "Available" : "Checked Out") << endl;
    }
};

// ---------------------------------------------------------
// Hash Table Implementation
// Purpose: Fast lookups by ID (Average O(1))
// ---------------------------------------------------------
class HashTable {
private:
    static const int TABLE_SIZE = 101; // Prime number to reduce collisions
    list<Book*> table[TABLE_SIZE];     // Linked list for chaining

    int hashFunction(int key) const {
        return key % TABLE_SIZE;
    }

public:
    void insert(Book* book) {
        int index = hashFunction(book->id);
        table[index].push_back(book);
    }

    Book* search(int id) {
        int index = hashFunction(id);
        for (Book* book : table[index]) {
            if (book->id == id) {
                return book;
            }
        }
        return nullptr;
    }
};

// ---------------------------------------------------------
// Binary Search Tree (BST) Implementation
// Purpose: Sorted storage & Search by Title (Average O(log N))
// ---------------------------------------------------------
struct BSTNode {
    Book* book;
    BSTNode* left;
    BSTNode* right;

    BSTNode(Book* b) : book(b), left(nullptr), right(nullptr) {}
};

class BST {
private:
    BSTNode* root;

    BSTNode* insertRecursive(BSTNode* node, Book* book) {
        if (node == nullptr) {
            return new BSTNode(book);
        }
        
        // Compare titles lexicographically
        if (book->title < node->book->title) {
            node->left = insertRecursive(node->left, book);
        } else if (book->title > node->book->title) {
            node->right = insertRecursive(node->right, book);
        }
        return node;
    }

    Book* searchRecursive(BSTNode* node, const string& title) {
        if (node == nullptr) return nullptr;
        
        if (node->book->title == title) return node->book;
        
        if (title < node->book->title) {
            return searchRecursive(node->left, title);
        } else {
            return searchRecursive(node->right, title);
        }
    }

    void inorderPrint(BSTNode* node) {
        if (node == nullptr) return;
        inorderPrint(node->left);
        node->book->printDetails();
        inorderPrint(node->right);
    }

    // Helper to clear memory
    void deleteTree(BSTNode* node) {
        if (node) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

public:
    BST() : root(nullptr) {}
    ~BST() { deleteTree(root); }

    void insert(Book* book) {
        root = insertRecursive(root, book);
    }

    Book* search(const string& title) {
        return searchRecursive(root, title);
    }

    void printAll() {
        if (!root) cout << "No books in the library." << endl;
        else inorderPrint(root);
    }
};

// ---------------------------------------------------------
// Library Manager (Controller)
// Manages memory ownership and updates indexes
// ---------------------------------------------------------
class LibraryManager {
private:
    vector<Book*> books;    // Master storage (owns memory)
    HashTable idIndex;      // Index for ID
    BST titleIndex;         // Index for Title

public:
    ~LibraryManager() {
        for (Book* book : books) {
            delete book;
        }
    }

    void addBook(int id, string title, string author) {
        if (idIndex.search(id) != nullptr) {
            cout << "Error: Book ID " << id << " already exists." << endl;
            return;
        }

        Book* newBook = new Book(id, title, author);
        books.push_back(newBook);
        
        // Update indexes
        idIndex.insert(newBook);
        titleIndex.insert(newBook);

        cout << "Added: " << title << endl;
    }

    void searchById(int id) {
        Book* res = idIndex.search(id);
        if (res) {
            cout << "\n[Found by ID]" << endl;
            res->printDetails();
        } else {
            cout << "Book not found (ID: " << id << ")" << endl;
        }
    }

    void searchByTitle(string title) {
        Book* res = titleIndex.search(title);
        if (res) {
            cout << "\n[Found by Title]" << endl;
            res->printDetails();
        } else {
            cout << "Book not found (Title: " << title << ")" << endl;
        }
    }

    void showAllBooks() {
        cout << "\n=== Library Catalog (Sorted by Title) ===" << endl;
        titleIndex.printAll();
        cout << "=========================================" << endl;
    }
    
    void loadSampleData() {
        addBook(1001, "The C++ Programming Language", "B. Stroustrup");
        addBook(2042, "Clean Code", "Robert C. Martin");
        addBook(1005, "Introduction to Algorithms", "T. Cormen");
        addBook(3099, "Operating System Concepts", "A. Silberschatz");
        addBook(5001, "Computer Networking", "J. Kurose");
        cout << "Sample data loaded.\n" << endl;
    }
};

int main() {
    LibraryManager lib;
    lib.loadSampleData();

    int choice;
    while (true) {
        cout << "\n1. Add Book\n2. Search (ID)\n3. Search (Title)\n4. Show All\n0. Exit\n>> ";
        if (!(cin >> choice)) { // Input validation
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (choice == 0) break;

        int id;
        string title, author;

        switch (choice) {
            case 1:
                cout << "ID: "; cin >> id;
                cin.ignore();
                cout << "Title: "; getline(cin, title);
                cout << "Author: "; getline(cin, author);
                lib.addBook(id, title, author);
                break;
            case 2:
                cout << "ID: "; cin >> id;
                lib.searchById(id);
                break;
            case 3:
                cin.ignore();
                cout << "Title: "; getline(cin, title);
                lib.searchByTitle(title);
                break;
            case 4:
                lib.showAllBooks();
                break;
            default:
                cout << "Invalid option." << endl;
        }
    }
    return 0;
}
