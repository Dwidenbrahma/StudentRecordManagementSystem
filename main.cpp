// ✅ Cleaner, more maintainable version

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <limits>
using namespace std;

// Color Macros
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"
#define RESET   "\033[0m"

class Student {
private:
    int studentID, age;
    string firstName, lastName, fatherName, gender, address;

public:
    Student() {}
    Student(int id, int ag, string fn, string ln, string father, string gen, string addr)
        : studentID(id), age(ag), firstName(fn), lastName(ln), fatherName(father), gender(gen), address(addr) {}

    int getID() const { return studentID; }
    string getFirstName() const { return firstName; }
    string getLastName() const { return lastName; }
    string getFatherName() const { return fatherName; }
    string getAddress() const { return address; }

    string serialize() const {
        return to_string(studentID) + "," + to_string(age) + "," + firstName + "," + lastName + "," +
               fatherName + "," + gender + "," + address;
    }

    void display() const {
        cout << left << setw(8) << studentID
             << setw(5) << age
             << setw(12) << firstName
             << setw(12) << lastName
             << setw(15) << fatherName
             << setw(8) << gender
             << setw(20) << address << "\n";
    }

    static vector<Student> loadAll() {
        vector<Student> students;
        ifstream in("student_database.txt");
        string line;
        while (getline(in, line)) {
            stringstream ss(line);
            vector<string> data;
            string token;
            while (getline(ss, token, ',')) data.push_back(token);
            if (data.size() == 7) {
                students.emplace_back(stoi(data[0]), stoi(data[1]), data[2], data[3], data[4], data[5], data[6]);
            }
        }
        return students;
    }

    static void saveAll(const vector<Student> &students) {
        ofstream out("student_database.txt", ios::trunc);
        for (const auto &s : students) {
            out << s.serialize() << "\n";
        }
    }
};

bool idExists(int id) {
    for (const auto &s : Student::loadAll()) {
        if (s.getID() == id) return true;
    }
    return false;
}

void pause() {
    cout << YELLOW << "\nPress Enter to continue..." << RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void addStudent() {
    int id, age;
    string fn, ln, father, gender, addr;

    cout << YELLOW << "Enter ID: " << RESET;
    cin >> id;
    if (idExists(id)) { cout << RED << "❌ ID already exists!\n" << RESET; pause(); return; }

    cout << "Enter Age: ";
    cin >> age; cin.ignore();
    cout << "Enter First Name: "; getline(cin, fn);
    cout << "Enter Last Name: "; getline(cin, ln);
    cout << "Enter Father's Name: "; getline(cin, father);
    cout << "Enter Gender: "; getline(cin, gender);
    cout << "Enter Address: "; getline(cin, addr);

    auto students = Student::loadAll();
    students.emplace_back(id, age, fn, ln, father, gender, addr);
    Student::saveAll(students);
    cout << GREEN << "✅ Student added!\n" << RESET;
    pause();
}

void viewStudentByID() {
    int id;
    cout << YELLOW << "Enter Student ID: " << RESET;
    cin >> id;

    auto students = Student::loadAll();
    for (const auto &s : students) {
        if (s.getID() == id) {
            cout << CYAN << "\nID     Age  FirstName   LastName    FatherName      Gender  Address\n";
            cout << "-------------------------------------------------------------------\n" << RESET;
            s.display(); pause(); return;
        }
    }
    cout << RED << "❌ Student not found!\n" << RESET; pause();
}

void searchStudent() {
    cin.ignore();
    string keyword;
    cout << YELLOW << "Enter search keyword: " << RESET;
    getline(cin, keyword);

    transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);

    auto students = Student::loadAll();
    bool found = false;
    cout << CYAN << "\nID     Age  FirstName   LastName    FatherName      Gender  Address\n";
    cout << "-------------------------------------------------------------------\n" << RESET;

    for (const auto &s : students) {
        string combined = s.getFirstName() + " " + s.getLastName() + " " + s.getFatherName() + " " + s.getAddress();
        string lowerCombined = combined;
        transform(lowerCombined.begin(), lowerCombined.end(), lowerCombined.begin(), ::tolower);

        if (lowerCombined.find(keyword) != string::npos) {
            s.display(); found = true;
        }
    }
    if (!found) cout << RED << "❌ No match found!\n" << RESET;
    pause();
}

void updateStudent() {
    int id;
    cout << YELLOW << "Enter Student ID to update: " << RESET;
    cin >> id;

    auto students = Student::loadAll();
    for (auto &s : students) {
        if (s.getID() == id) {
            int age;
            string fn, ln, father, gender, addr;
            cout << "Enter New Age: "; cin >> age; cin.ignore();
            cout << "Enter New First Name: "; getline(cin, fn);
            cout << "Enter New Last Name: "; getline(cin, ln);
            cout << "Enter New Father's Name: "; getline(cin, father);
            cout << "Enter New Gender: "; getline(cin, gender);
            cout << "Enter New Address: "; getline(cin, addr);

            s = Student(id, age, fn, ln, father, gender, addr);
            Student::saveAll(students);
            cout << GREEN << "✅ Updated successfully!\n" << RESET; pause(); return;
        }
    }
    cout << RED << "❌ Student not found!\n" << RESET; pause();
}

void deleteStudent() {
    int id;
    cout << YELLOW << "Enter Student ID to delete: " << RESET;
    cin >> id;

    auto students = Student::loadAll();
    vector<Student> updated;
    bool deleted = false;

    for (const auto &s : students) {
        if (s.getID() != id) updated.push_back(s);
        else deleted = true;
    }

    if (deleted) {
        Student::saveAll(updated);
        cout << GREEN << "✅ Deleted successfully!\n" << RESET;
    } else {
        cout << RED << "❌ Student not found!\n" << RESET;
    }
    pause();
}

void listAllStudents() {
    auto students = Student::loadAll();
    if (students.empty()) { cout << RED << "No records found.\n" << RESET; pause(); return; }

    cout << CYAN << "\nID     Age  FirstName   LastName    FatherName      Gender  Address\n";
    cout << "-------------------------------------------------------------------\n" << RESET;
    for (const auto &s : students) s.display();
    cout << YELLOW << "Total Records: " << students.size() << RESET << "\n";
    pause();
}

int main() {
    int choice;
    while (true) {
        cout << CYAN << "\n===== STUDENT RECORD MANAGEMENT SYSTEM =====\n" << RESET;
        cout << "1) Add Student\n2) View Student by ID\n3) Search Student\n4) Update Student\n";
        cout << "5) Delete Student\n6) List All Students\n7) Exit\n";
        cout << YELLOW << "Enter choice: " << RESET;
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudentByID(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: listAllStudents(); break;
            case 7: return 0;
            default: cout << RED << "❌ Invalid choice!\n" << RESET; pause();
        }
    }
}
