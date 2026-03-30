#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

class Person {
public:
    class Address {
    private:
        string poBox;
        string postalCode;
        string city;
        string county;
    public:
        Address(string pb = "", string pc = "", string c = "", string co = "") 
            : poBox(pb), postalCode(pc), city(c), county(co) {}
        
        // Getters
        string getPoBox() const { return poBox; }
        string getPostalCode() const { return postalCode; }
        string getCity() const { return city; }
        string getCounty() const { return county; }

        // Setters
        void setPoBox(string pb) { poBox = pb; }
        void setPostalCode(string pc) { postalCode = pc; }
        void setCity(string c) { city = c; }
        void setCounty(string co) { county = co; }
    };

protected:
    string firstName;
    string middleName;
    string lastName;
    string dob;
    Address address;

public:
    Person(string fn = "", string mn = "", string ln = "", string d = "", Address addr = Address())
        : firstName(fn), middleName(mn), lastName(ln), dob(d), address(addr) {}

    // Getters
    string getFirstName() const { return firstName; }
    string getMiddleName() const { return middleName; }
    string getLastName() const { return lastName; }
    string getDob() const { return dob; }
    Address getAddress() const { return address; }

    // Setters
    void setFirstName(string fn) { firstName = fn; }
    void setMiddleName(string mn) { middleName = mn; }
    void setLastName(string ln) { lastName = ln; }
    void setDob(string d) { dob = d; }
    void setAddress(Address addr) { address = addr; }
};


class Student : public Person {
private:
    string studentNumber;
    string programmeOfStudy;
    int yearOfStudy;

public:
    Student(string fn = "", string mn = "", string ln = "", string d = "", Address addr = Address(),
            string sNum = "", string prog = "", int year = 1)
        : Person(fn, mn, ln, d, addr), studentNumber(sNum), programmeOfStudy(prog), yearOfStudy(year) {}

    // Getters
    string getStudentNumber() const { return studentNumber; }
    string getProgrammeOfStudy() const { return programmeOfStudy; }
    int getYearOfStudy() const { return yearOfStudy; }

    // Setters
    void setStudentNumber(string sNum) { studentNumber = sNum; }
    void setProgrammeOfStudy(string prog) { programmeOfStudy = prog; }
    void setYearOfStudy(int year) { yearOfStudy = year; }

    // Convert to delimited string for File I/O
    string serialize() const {
        return studentNumber + "|" + firstName + "|" + middleName + "|" + lastName + "|" + dob + "|" +
               address.getPoBox() + "|" + address.getPostalCode() + "|" + address.getCity() + "|" + address.getCounty() + "|" +
               programmeOfStudy + "|" + to_string(yearOfStudy);
    }
};

class Book {
private:
    string bookId;
    string title;
    string author;
    int yearPublished;
    string borrowerId; 
public:
    Book(string id = "", string t = "", string a = "", int y = 0, string bId = "NONE")
        : bookId(id), title(t), author(a), yearPublished(y), borrowerId(bId) {}

    // Getters
    string getBookId() const { return bookId; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYearPublished() const { return yearPublished; }
    string getBorrowerId() const { return borrowerId; }
    bool isAvailable() const { return borrowerId == "NONE"; }

    // Setters
    void setBookId(string id) { bookId = id; }
    void setTitle(string t) { title = t; }
    void setAuthor(string a) { author = a; }
    void setYearPublished(int y) { yearPublished = y; }
    void setBorrowerId(string bId) { borrowerId = bId; }

    // Convert to delimited string for File I/O
    string serialize() const {
        return bookId + "|" + title + "|" + author + "|" + to_string(yearPublished) + "|" + borrowerId;
    }
};


class LibraryManager {
private:
    vector<Student> students;
    vector<Book> books;
    const string STUDENT_FILE = "students.txt";
    const string BOOK_FILE = "books.txt";

    // Helper to split strings for file reading
    vector<string> split(const string& s, char delimiter) {
        vector<string> tokens;
        string token;
        istringstream tokenStream(s);
        while (getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

public:
    LibraryManager() {
        loadData();
    }

    void loadData() {
        ifstream sFile(STUDENT_FILE);
        string line;
        while (getline(sFile, line)) {
            vector<string> data = split(line, '|');
            if (data.size() == 11) {
                Person::Address addr(data[5], data[6], data[7], data[8]);
                students.push_back(Student(data[1], data[2], data[3], data[4], addr, data[0], data[9], stoi(data[10])));
            }
        }
        sFile.close();

        ifstream bFile(BOOK_FILE);
        while (getline(bFile, line)) {
            vector<string> data = split(line, '|');
            if (data.size() == 5) {
                books.push_back(Book(data[0], data[1], data[2], stoi(data[3]), data[4]));
            }
        }
        bFile.close();
    }

    void saveData() {
        ofstream sFile(STUDENT_FILE);
        for (const auto& s : students) sFile << s.serialize() << "\n";
        sFile.close();

        ofstream bFile(BOOK_FILE);
        for (const auto& b : books) bFile << b.serialize() << "\n";
        bFile.close();
    }

    void addStudent() {
        string fn, mn, ln, dob, pb, pc, c, co, sNum, prog;
        int yr;
        cout << "Enter Student Number: "; cin >> sNum;
        
        // Uniqueness check
        for (const auto& s : students) {
            if (s.getStudentNumber() == sNum) { cout << "Error: Student ID already exists!\n"; return; }
        }

        cout << "First Name: "; cin >> fn;
        cout << "Middle Name: "; cin >> mn;
        cout << "Last Name: "; cin >> ln;
        cout << "DOB (DD/MM/YYYY): "; cin >> dob;
        cout << "PO Box: "; cin >> pb;
        cout << "Postal Code: "; cin >> pc;
        cout << "City: "; cin >> c;
        cout << "County: "; cin >> co;
        cout << "Programme: "; cin >> prog;
        cout << "Year of Study: "; cin >> yr;

        Person::Address addr(pb, pc, c, co);
        students.push_back(Student(fn, mn, ln, dob, addr, sNum, prog, yr));
        saveData();
        cout << "Student added successfully!\n";
    }

    void addBook() {
        string id, title, author;
        int yr;
        cout << "Enter Book ID: "; cin >> id;

        // Uniqueness check
        for (const auto& b : books) {
            if (b.getBookId() == id) { cout << "Error: Book ID already exists!\n"; return; }
        }

        cin.ignore();
        cout << "Title: "; getline(cin, title);
        cout << "Author: "; getline(cin, author);
        cout << "Year Published: "; cin >> yr;

        books.push_back(Book(id, title, author, yr));
        saveData();
        cout << "Book added successfully!\n";
    }

    void borrowBook() {
        string sNum, bId;
        cout << "Enter Student Number: "; cin >> sNum;
        cout << "Enter Book ID: "; cin >> bId;

        // Find Book
        Book* targetBook = nullptr;
        for (auto& b : books) {
            if (b.getBookId() == bId) { targetBook = &b; break; }
        }

        if (!targetBook) { cout << "Book not found.\n"; return; }
        if (!targetBook->isAvailable()) { cout << "Book is currently borrowed out.\n"; return; }

        // Check Student Limits
        int borrowCount = 0;
        for (const auto& b : books) {
            if (b.getBorrowerId() == sNum) {
                borrowCount++;
                if (b.getTitle() == targetBook->getTitle()) {
                    cout << "Student is already holding a copy of this title. Cannot borrow again.\n";
                    return;
                }
            }
        }

        if (borrowCount >= 3) { cout << "Student has reached the maximum borrow limit (3 books).\n"; return; }

        // Success
        targetBook->setBorrowerId(sNum);
        saveData();
        cout << "Book successfully borrowed!\n";
    }

    void searchStudent() {
        string query;
        cout << "Enter Student Number or First Name: "; cin >> query;

        bool found = false;
        for (const auto& s : students) {
            if (s.getStudentNumber() == query || s.getFirstName() == query) {
                found = true;
                cout << "\n--- Student Found ---\n";
                cout << "Name: " << s.getFirstName() << " " << s.getLastName() << " | ID: " << s.getStudentNumber() << "\n";
                cout << "Programme: " << s.getProgrammeOfStudy() << "\n";
                
                cout << "Borrowed Books:\n";
                int count = 0;
                for (const auto& b : books) {
                    if (b.getBorrowerId() == s.getStudentNumber()) {
                        cout << " - " << b.getTitle() << " (ID: " << b.getBookId() << ")\n";
                        count++;
                    }
                }
                if (count == 0) cout << " None.\n";
            }
        }
        if (!found) cout << "Student not found.\n";
    }

    void searchBook() {
        cin.ignore();
        string query;
        cout << "Enter Book ID or Title: "; getline(cin, query);

        bool found = false;
        for (const auto& b : books) {
            if (b.getBookId() == query || b.getTitle() == query) {
                found = true;
                cout << "\n--- Book Found ---\n";
                cout << "ID: " << b.getBookId() << " | Title: " << b.getTitle() << "\n";
                cout << "Author: " << b.getAuthor() << " | Year: " << b.getYearPublished() << "\n";
                if (b.isAvailable()) {
                    cout << "Status: AVAILABLE\n";
                } else {
                    cout << "Status: BORROWED by Student ID " << b.getBorrowerId() << "\n";
                }
            }
        }
        if (!found) cout << "Book not found.\n";
    }
};


int main() {
    LibraryManager library;
    int choice = 0;

    while (choice != 6) {
        cout << "\n=== LIBRARY MANAGEMENT SYSTEM ===\n";
        cout << "1. Add Student\n";
        cout << "2. Add Book\n";
        cout << "3. Borrow Book\n";
        cout << "4. Search Student (Shows Borrowed Books)\n";
        cout << "5. Search Book (Shows Availability)\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1: library.addStudent(); break;
            case 2: library.addBook(); break;
            case 3: library.borrowBook(); break;
            case 4: library.searchStudent(); break;
            case 5: library.searchBook(); break;
            case 6: cout << "Exiting system. Goodbye!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}
