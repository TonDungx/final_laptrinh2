#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <conio.h>
#define MAX_COURSES 3
#define MAX_STUDENTS 100

using namespace std;

class Course {
public:
    string courseName;
    float marks;
    float credit;

    Course() {
        courseName = "";
        marks = 0;
        credit = 0;
    }
    Course(string name, float mark, float cred) {
        courseName = name;
        marks = mark;
        credit = cred;
    }
};

class Student {
public:
    string id;
    string name;
    string gender;
    Course courses[MAX_COURSES];
    int courseCount;
    float gpa;

    Student() {
        id = "";
        name = "";
        gender = "";
        courseCount = 0;
        gpa = 0;
    }
    Student(string id, string name, string gender) {
        this->id = id;
        this->name = name;
        this->gender = gender;
        courseCount = 0;
        gpa = 0;
    }

    void calculateGPA() {
        float totalScore = 0;
        float totalCredit = 0;
        for (int i = 0; i < courseCount; ++i) {
            totalCredit += courses[i].credit;
            totalScore += courses[i].marks * courses[i].credit;
        }
        if (totalCredit > 0) {
            gpa = (totalScore / totalCredit) / 10 * 4;
        }
        else {
            gpa = 0;
        }
    }
};

class Enrollment {
private:
    Student students[MAX_STUDENTS];
    int studentCount;

    void saveToFile() {
        ofstream fout("student.txt", ios::out); // Change to write mode
        for (int i = 0; i < studentCount; ++i) {
            fout << students[i].id << " \"" << students[i].name << "\" " << students[i].gender << " " << students[i].gpa << " " << students[i].courseCount << " ";
            for (int j = 0; j < students[i].courseCount; ++j) {
                fout << students[i].courses[j].courseName << " " << students[i].courses[j].marks << " " << students[i].courses[j].credit << " ";
            }
            fout << endl;
        }
        fout.close();
    }

    void loadFromFile() {
        ifstream fin("student.txt", ios::in); // Open the file in read mode
        studentCount = 0;
        string line;
        while (getline(fin, line)) {
            istringstream iss(line);
            string id, name, gender;
            float gpa;
            int courseCount;

            iss >> id;
            iss.ignore(); // ignore space
            getline(iss, name, '\"'); // read until the first quote
            getline(iss, name, '\"'); // read the name inside quotes
            iss >> gender >> gpa >> courseCount;

            Student newStudent(id, name, gender);
            newStudent.gpa = gpa;
            newStudent.courseCount = courseCount;

            for (int i = 0; i < courseCount; ++i) {
                string courseName;
                float marks, credit;
                iss >> courseName >> marks >> credit;
                newStudent.courses[i] = Course(courseName, marks, credit);
            }
            students[studentCount++] = newStudent;
        }
        fin.close();
    }

public:
    Enrollment() : studentCount(0) {
        loadFromFile();
    }

    void addNewStudent() {
        if (studentCount >= MAX_STUDENTS) {
            cout << "Maximum student limit reached." << endl;
            system("pause");
            return;
        }

        string id, name, gender;
        cout << "Enter ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter name: ";
        getline(cin, name);
        cout << "Enter gender: ";
        getline(cin, gender);
        Student newStudent(id, name, gender);

        cout << "Enter number of courses (max 3): ";
        cin >> newStudent.courseCount;
        cin.ignore();
        for (int i = 0; i < newStudent.courseCount; ++i) {
            string courseName;
            float marks, credit;
            cout << "Enter course name: ";
            getline(cin, courseName);
            cout << "Enter marks: ";
            cin >> marks;
            cout << "Enter credit: ";
            cin >> credit;
            cin.ignore();
            newStudent.courses[i] = Course(courseName, marks, credit);
        }
        newStudent.calculateGPA();
        students[studentCount++] = newStudent;
        saveToFile();

        cout << "Student added successfully." << endl;
        system("pause");
    }

    void updateStudent() {
        string id;
        cout << "Enter ID of the student to update: ";
        cin >> id;
        cin.ignore();

        for (int i = 0; i < studentCount; ++i) {
            if (students[i].id == id) {
                string input;
                cout << "Update name? (Y/N): ";
                cin >> input;
                cin.ignore();
                if (input == "Y" || input == "y") {
                    cout << "Enter new name: ";
                    getline(cin, students[i].name);
                }

                cout << "Update gender? (Y/N): ";
                cin >> input;
                cin.ignore();
                if (input == "Y" || input == "y") {
                    cout << "Enter new gender: ";
                    getline(cin, students[i].gender);
                }

                cout << "Update courses? (Y/N): ";
                cin >> input;
                cin.ignore();
                if (input == "Y" || input == "y") {
                    cout << "Enter number of courses (max 3): ";
                    cin >> students[i].courseCount;
                    cin.ignore();
                    for (int j = 0; j < students[i].courseCount; ++j) {
                        string courseName;
                        float marks, credit;
                        cout << "Enter course name: ";
                        getline(cin, courseName);
                        cout << "Enter marks: ";
                        cin >> marks;
                        cout << "Enter credit: ";
                        cin >> credit;
                        cin.ignore();
                        students[i].courses[j] = Course(courseName, marks, credit);
                    }
                    students[i].calculateGPA();
                }

                saveToFile();
                cout << "Student updated successfully." << endl;
                system("pause");
                return;
            }
        }

        cout << "Student ID not found." << endl;
        system("pause");
    }

    void searchStudentByID() {
        string id;
        cout << "Enter ID of the student to search: ";
        cin >> id;
        cin.ignore();

        for (int i = 0; i < studentCount; ++i) {
            if (students[i].id == id) {
                cout << "ID: " << students[i].id << endl;
                cout << "Name: " << students[i].name << endl;
                cout << "Gender: " << students[i].gender << endl;
                cout << "GPA: " << students[i].gpa << endl;
                for (int j = 0; j < students[i].courseCount; ++j) {
                    cout << "Course " << (j + 1) << ": " << students[i].courses[j].courseName << ", Marks: " << students[i].courses[j].marks << ", Credit: " << students[i].courses[j].credit << endl;
                }
                system("pause");
                return;
            }
        }

        cout << "Student ID not found." << endl;
        system("pause");
    }

    void searchStudentByName() {
        string name;
        cout << "Enter name of the student to search: ";
        cin.ignore();
        getline(cin, name);

        bool found = false;
        for (int i = 0; i < studentCount; ++i) {
            if (students[i].name == name) {
                cout << "ID: " << students[i].id << endl;
                cout << "Name: " << students[i].name << endl;
                cout << "Gender: " << students[i].gender << endl;
                cout << "GPA: " << students[i].gpa << endl;
                for (int j = 0; j < students[i].courseCount; ++j) {
                    cout << "Course " << (j + 1) << ": " << students[i].courses[j].courseName << ", Marks: " << students[i].courses[j].marks << ", Credit: " << students[i].courses[j].credit << endl;
                }
                found = true;
                cout << "-----------------------------------" << endl;
            }
        }

        if (!found) {
            cout << "Student name not found." << endl;
        }
        system("pause");
    }

    void removeStudent() {
        string id;
        cout << "Enter ID of the student to remove: ";
        cin >> id;
        cin.ignore();

        for (int i = 0; i < studentCount; ++i) {
            if (students[i].id == id) {
                for (int j = i; j < studentCount - 1; ++j) {
                    students[j] = students[j + 1];
                }
                studentCount--;
                saveToFile();

                cout << "Student removed successfully." << endl;
                system("pause");
                return;
            }
        }

        cout << "Student ID not found." << endl;
        system("pause");
    }

    void listAllStudents() {
        for (int i = 0; i < studentCount; ++i) {
            cout << "ID: " << students[i].id << endl;
            cout << "Name: " << students[i].name << endl;
            cout << "Gender: " << students[i].gender << endl;
            cout << "GPA: " << students[i].gpa << endl;
            for (int j = 0; j < students[i].courseCount; ++j) {
                cout << "Course " << (j + 1) << ": " << students[i].courses[j].courseName << ", Marks: " << students[i].courses[j].marks << ", Credit: " << students[i].courses[j].credit << endl;
            }
            cout << "-----------------------------------" << endl;
        }
        system("pause");
    }
};

int main() {
    int choice;
    Enrollment system1; // Initialize Enrollment object outside the loop
    system("cls");
    cout << "\n\n\n\n\n";
    cout << "\n\t\t\t        WELCOME TO MANAGEMENT SYSTEM         ";
    cout << "\n\t\t\t               GROUP ONE        ";
    cout << "\n\n\n\t\t\t\tEnter any key to continue.....";

    _getch();
    system("cls");
    while (true) {
        system("cls");
        cout << "\n\t\t\tSTUDENT MANAGEMENT SYSTEM" << endl;
        cout << "\n\t\t\t1. Add New Student" << endl;
        cout << "\n\t\t\t2. Update Existing Student" << endl;
        cout << "\n\t\t\t3. Search for a Student by ID" << endl;
        cout << "\n\t\t\t4. Search for a Student by Name" << endl;
        cout << "\n\t\t\t5. Remove a Student" << endl;
        cout << "\n\t\t\t6. List All Students" << endl;
        cout << "\n\t\t\t7. Exit" << endl;
        cout << "\n\t\t\tEnter your choice: ";
        cin >> choice;
        system("cls");

        switch (choice) {
        case 1:
            system1.addNewStudent();
            break;
        case 2:
            system1.updateStudent();
            break;
        case 3:
            system1.searchStudentByID();
            break;
        case 4:
            system1.searchStudentByName();
            break;
        case 5:
            system1.removeStudent();
            break;
        case 6:
            system1.listAllStudents();
            break;
        case 7:
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }
}
