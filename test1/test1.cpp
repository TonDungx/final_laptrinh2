#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <stdlib.h>

using namespace std;

const int MAX_COURSES = 3;
const int MAX_STUDENTS = 100;

class Course {
public:
    string courseName;
    float marks;
    float credit;

    Course() : courseName(""), marks(0), credit(0) {}
    Course(string name, float mark, float cred) : courseName(name), marks(mark), credit(cred) {}
};

class Student {
public:
    string id;
    string name;
    string gender;
    Course courses[MAX_COURSES];
    int courseCount;
    float gpa;

    Student() : id(""), name(""), gender(""), courseCount(0), gpa(0) {}
    Student(string id, string name, string gender) : id(id), name(name), gender(gender), courseCount(0), gpa(0) {}

    void calculateGPA() {
        float totalScore = 0;
        float totalCredit = 0;
        for (int i = 0; i < courseCount; ++i) {
            totalCredit += courses[i].credit;
            totalScore += courses[i].marks * courses[i].credit;
        }
        gpa = (totalCredit > 0) ? (totalScore / totalCredit) / 10 * 4 : 0;
    }
};

class Enrollment {
private:
    Student students[MAX_STUDENTS];
    int studentCount;

    void saveToFile() {
        ofstream fout("student.txt");
        for (int i = 0; i < studentCount; ++i) {
            fout << students[i].id << " " << students[i].name << " " << students[i].gender << " " << students[i].gpa;
            for (int j = 0; j < students[i].courseCount; ++j) {
                fout << " " << students[i].courses[j].courseName << " " << students[i].courses[j].marks << " " << students[i].courses[j].credit;
            }
            fout << endl;
        }
        fout.close();
    }

public:
    Enrollment() : studentCount(0) {}

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
                cout << "Enter new name: ";
                getline(cin, students[i].name);
                cout << "Enter new gender: ";
                getline(cin, students[i].gender);

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
                saveToFile();

                cout << "Student updated successfully." << endl;
                system("pause");
                return;
            }
        }

        cout << "Student ID not found." << endl;
        system("pause");
    }

    void searchStudent() {
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
    Enrollment system;
    int choice;

    while (true) {
        //system("cls");
        cout << "Student Management System" << endl;
        cout << "1. Add New Student" << endl;
        cout << "2. Update Existing Student" << endl;
        cout << "3. Search for a Student" << endl;
        cout << "4. Remove a Student" << endl;
        cout << "5. List All Students" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        //system("cls");
        switch (choice) {
        case 1:
            system.addNewStudent();
            break;
        case 2:
            system.updateStudent();
            break;
        case 3:
            system.searchStudent();
            break;
        case 4:
            system.removeStudent();
            break;
        case 5:
            system.listAllStudents();
            break;
        case 6:
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
            //system("pause");
            break;
        }
    }

    return 0;
}
