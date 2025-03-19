#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

struct Student {
    string id;
    string firstName;
    string lastName;
    string course;
    double gpa;
};

void displayMenu() {
    cout << "\n--- Menu ---" << endl;
    cout << "[1] Add Student" << endl;
    cout << "[2] Edit Student" << endl;
    cout << "[3] Delete Student" << endl;
    cout << "[4] View Student" << endl;
    cout << "[5] Exit Program" << endl;
    cout << "Enter your choice: ";
}


void addStudent(vector<Student>& students) {
    Student newStudent;

    while (true) {
        cout << "Enter Student ID: ";
        cin >> newStudent.id;

        bool duplicate = false;
        for (const auto& student : students) {
            if (student.id == newStudent.id) {
                cout << "Error: Student ID already exists." << endl;
                duplicate = true;
                break;
            }
        }
        if (!duplicate) {
            break;
        }
    }


    cout << "Enter Student First Name: ";
    cin.ignore();
    getline(cin, newStudent.firstName);


    cout << "Enter Student Last Name: ";
    getline(cin, newStudent.lastName);


    cout << "Enter Student Course: ";
    getline(cin, newStudent.course);

    while (true) {
        cout << "Enter Previous Semestral GPA: ";
        cin >> newStudent.gpa;

        if (cin.fail()) {
            cout << "Error: Invalid GPA input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }

    students.push_back(newStudent);
    cout << "Student added successfully!" << endl;
}

void editStudent(vector<Student>& students) {
    if (students.empty()) {
        cout << "No student records found." << endl;
        return;
    }

    string searchId;
    cout << "Enter Student ID to edit: ";
    cin >> searchId;

    for (auto& student : students) {
        if (student.id == searchId) {
            cout << "Student found:" << endl;
            cout << "ID: " << student.id << endl;
            cout << "First Name: " << student.firstName << endl;
            cout << "Last Name: " << student.lastName << endl;
            cout << "Course: " << student.course << endl;
            cout << "GPA: " << student.gpa << endl;

            cout << "Enter new Student First Name (or press Enter to keep current): ";
            cin.ignore();
            string newFirstName;
            getline(cin, newFirstName);
            if (!newFirstName.empty()) {
                student.firstName = newFirstName;
            }

            cout << "Enter new Student Last Name (or press Enter to keep current): ";
            string newLastName;
            getline(cin, newLastName);
            if (!newLastName.empty()) {
                student.lastName = newLastName;
            }

            cout << "Enter new Student Course (or press Enter to keep current): ";
            string newCourse;
            getline(cin, newCourse);
            if (!newCourse.empty()) {
                student.course = newCourse;
            }

            cout << "Enter new Previous Semestral GPA (or press Enter to keep current): ";
            string newGpaStr;
            getline(cin, newGpaStr);
            if (!newGpaStr.empty()) {
                try {
                    student.gpa = stod(newGpaStr);
                } catch (const invalid_argument& e) {
                    cout << "Error: Invalid GPA input. GPA not changed." << endl;
                }
            }

            cout << "Student data updated successfully!" << endl;
            return;
        }
    }

    cout << "Student ID not found." << endl;
}

void deleteStudent(vector<Student>& students) {
    if (students.empty()) {
        cout << "No student records found." << endl;
        return;
    }

    string searchId;
    cout << "Enter Student ID to delete: ";
    cin >> searchId;

    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->id == searchId) {
            cout << "Student found:" << endl;
            cout << "ID: " << it->id << endl;
            cout << "First Name: " << it->firstName << endl;
            cout << "Last Name: " << it->lastName << endl;
            cout << "Course: " << it->course << endl;
            cout << "GPA: " << it->gpa << endl;

            char confirm;
            cout << "Are you sure you want to delete this student? (y/n): ";
            cin >> confirm;

            if (confirm == 'y' || confirm == 'Y') {
                students.erase(it);
                cout << "Student deleted successfully!" << endl;
                return;
            } else {
                cout << "Deletion cancelled." << endl;
                return;
            }
        }
    }

    cout << "Student ID not found." << endl;
}

void viewStudents(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No student records found." << endl;
        return;
    }

    cout << "View students by:" << endl;
    cout << "[1] Alphabetical order" << endl;
    cout << "[2] GPA (ascending)" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;

    vector<Student> sortedStudents = students;

    if (choice == 1) {
        sort(sortedStudents.begin(), sortedStudents.end(), [](const Student& a, const Student& b) {
            string fullNameA = a.firstName + " " + a.lastName;
            string fullNameB = b.firstName + " " + b.lastName;
            return fullNameA < fullNameB;
        });
    } else if (choice == 2) {
        sort(sortedStudents.begin(), sortedStudents.end(), [](const Student& a, const Student& b) {
            return a.gpa < b.gpa;
        });
    } else {
        cout << "Invalid choice." << endl;
        return;
    }

    for (const auto& student : sortedStudents) {
        cout << "ID: " << student.id << ", Name: " << student.firstName << " " << student.lastName << ", Course: " << student.course << ", GPA: " << student.gpa << endl;
    }
}

int main() {
    vector<Student> students;
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent(students);
                break;
            case 2:
                editStudent(students);
                break;
            case 3:
                deleteStudent(students);
                break;
            case 4:
                viewStudents(students);
                break;
            case 5:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 5);

    return 0;
}
