#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <regex>
using namespace std;

class Student {
public:
    string id;
    string name;
    string gender;
    string email;
    string phoneNo;
    string faculty;

    Student() {}

    Student(string id, string name, string gender, string email, string phoneNo, string faculty) {
        this->id = id;
        this->name = name;
        this->gender = gender;
        this->email = email;
        this->phoneNo = phoneNo;
        this->faculty = faculty;
    }
};

class Score {
public:
    string id;
    string subject;
    string credit;
    string score;
    double gpa;

    Score() {}

    Score(string id, string subject, string credit, string score) {
        this->id = id;
        this->subject = subject;
        this->credit = credit;
        this->score = score;
    }
};

class StudentManagementSystem {
private:
    list<Student> students;
    list<Score> scores;

public:
    void predisplay() {
        cout << "Welcome to the Student Management System" << endl;
    }

    void readCSVFile() {
        ifstream file("student.txt");
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string id, name, gender, email, phoneNo, faculty;
            getline(iss, id, ',');
            getline(iss, name, ',');
            getline(iss, gender, ',');
            getline(iss, email, ',');
            getline(iss, phoneNo, ',');
            getline(iss, faculty, ',');
            Student student(id, name, gender, email, phoneNo, faculty);
            students.push_back(student);
        }
        file.close();		
    }

    void readCSVFile2() {
        ifstream file("score.txt");
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string id, subject, credit, score, gpa;
            getline(iss, id, ',');
            getline(iss, subject, ',');
            getline(iss, credit, ',');
            getline(iss, score, ',');
            getline(iss, gpa, ',');
            Score sc(id, subject, credit, score);
            sc.gpa = stod(gpa);
            scores.push_back(sc);
        }
        file.close();
    }

    void saveStudentToFile() {
        ofstream file("student.txt");
        for (const auto &student : students) {
            file << student.id << ","
                 << student.name << ","
                 << student.gender << ","
                 << student.email << ","
                 << student.phoneNo << ","
                 << student.faculty << "\n";
        }
        file.close();
    }

    void saveScoreToFile() {
        ofstream file("score.txt");
        for (const auto &score : scores) {
            file << score.id << ","
                 << score.subject << ","
                 << score.credit << ","
                 << score.score << ","
                 << fixed << setprecision(2) << score.gpa << "\n";
        }
        file.close();
    }

    void addNewStudent() {
        string id, name, gender, email, phoneNo, faculty;
        cout << "Enter ID: ";
        cin >> id;
        cin.ignore(); // Clear newline character from input buffer
        cout << "Enter name: ";
        getline(cin, name);
        cout << "Enter gender: ";
        getline(cin, gender);
        cout << "Enter email: ";
        getline(cin, email);
        cout << "Enter phone number: ";
        getline(cin, phoneNo);
        cout << "Enter faculty: ";
        getline(cin, faculty);
        Student student(id, name, gender, email, phoneNo, faculty);
        students.push_back(student);
        cout << "Student " << name << " added successfully." << endl;
    }

    void updateStudent() {
        string id;
        cout << "Enter ID of the student to update: ";
        cin >> id;
        cin.ignore(); // Clear newline character from input buffer
        for (auto &student : students) {
            if (student.id == id) {
                cout << "Enter new name: ";
                getline(cin, student.name);
                cout << "Enter new gender: ";
                getline(cin, student.gender);
                cout << "Enter new email: ";
                getline(cin, student.email);
                cout << "Enter new phone number: ";
                getline(cin, student.phoneNo);
                cout << "Enter new faculty: ";
                getline(cin, student.faculty);
                cout << "Student with ID " << id << " updated successfully." << endl;
                return;
            }
        }
        cout << "Student with ID " << id << " not found." << endl;
    }

    void searchStudent() {
        string id;
        cout << "Enter student ID to search: ";
        cin >> id;
        for (const auto &student : students) {
            if (student.id == id) {
                cout << "ID: " << student.id << ", Name: " << student.name
                     << ", Gender: " << student.gender << ", Email: " << student.email
                     << ", Phone No: " << student.phoneNo << ", Faculty: " << student.faculty << endl;
                return;
            }
        }
        cout << "Student with ID " << id << " not found." << endl;
    }

    void removeStudent() {
        string id;
        cout << "Enter ID of the student to remove: ";
        cin >> id;
        for (auto it = students.begin(); it != students.end(); ++it) {
            if (it->id == id) {
                students.erase(it);
                cout << "Student with ID " << id << " removed successfully." << endl;
                return;
            }
        }
        cout << "Student with ID " << id << " not found." << endl;
    }

    void listAllStudents() {
        if (students.empty()) {
            cout << "No students to display." << endl;
            return;
        }
        for (const auto &student : students) {
            cout << "ID: " << student.id << ", Name: " << student.name
                 << ", Gender: " << student.gender << ", Email: " << student.email
                 << ", Phone No: " << student.phoneNo << ", Faculty: " << student.faculty << endl;
        }
    }

    void sortStudentsByGPA() {
        if (students.empty()) {
            cout << "No students to sort." << endl;
            return;
        }
        students.sort([this](const Student &a, const Student &b) {
            double gpaA = this->getStudentGPA(a.id);
            double gpaB = this->getStudentGPA(b.id);
            return gpaA > gpaB;
        });
        cout << "Students sorted by GPA." << endl;
    }

    double getStudentGPA(const string &id) {
        double totalScore = 0.0;
        double totalCredit = 0.0;
        for (const auto &score : scores) {
            if (score.id == id) {
                totalCredit += stod(score.credit);
                totalScore += stod(score.score) * stod(score.credit);
            }
        }
        return totalCredit > 0 ? ((totalScore / totalCredit) / 10) * 4 : 0.0;
    }

    void addScore() {
        string id;
        cout << "Enter student ID to add score: ";
        cin >> id;
        cin.ignore(); // Clear newline character from input buffer

        bool found = false;
        for (const auto &student : students) {
            if (student.id == id) {
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Student with ID " << id << " not found." << endl;
            return;
        }

        int numSubjects;
        cout << "Enter number of subjects (max 4): ";
        cin >> numSubjects;
        cin.ignore(); // Clear newline character from input buffer
        if (numSubjects > 4) {
            cout << "Number of subjects cannot exceed 4." << endl;
            return;
        }

        double totalScore = 0.0;
        double totalCredit = 0.0;

        for (int i = 0; i < numSubjects; ++i) {
            string subject, credit, score;
            cout << "Enter subject name: ";
            getline(cin, subject);
            cout << "Enter credit: ";
            getline(cin, credit);
            cout << "Enter score: ";
            getline(cin, score);

            totalCredit += stod(credit);
            totalScore += stod(score) * stod(credit);

            scores.emplace_back(id, subject, credit, score);
        }

        double gpa = ((totalScore / totalCredit) / 10) * 4;
        for (auto &score : scores) {
            if (score.id == id) {
                score.gpa = gpa;
            }
        }

        cout << "GPA: " << fixed << setprecision(2) << gpa << endl;
        saveScoreToFile();
    }

    void listAllScores() {
        if (scores.empty()) {
            cout << "No scores to display." << endl;
            return;
        }
        for (const auto &score : scores) {
            cout << "ID: " << score.id << ", Subject: " << score.subject
                 << ", Credit: " << score.credit << ", Score: " << score.score
                 << ", GPA: " << fixed << setprecision(2) << score.gpa << endl;
        }
    }
};

int main() {
    StudentManagementSystem sms;
    sms.predisplay();
    sms.readCSVFile();
    sms.readCSVFile2();

    int choice;
    do {
        cout << "\nMenu:\n"
             << "1. Add New Student\n"
             << "2. Update Existing Student\n"
             << "3. Search for a Student\n"
             << "4. Remove a Student\n"
             << "5. List All Students\n"
             << "6. Sort Students by GPA\n"
             << "7. Add Score\n"
             << "8. List All Scores\n"
             << "9. Save & Exit\n"
             << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear newline character from input buffer
        switch (choice) {
            case 1:
                sms.addNewStudent();
                break;
            case 2:
                sms.updateStudent();
                break;
            case 3:
                sms.searchStudent();
                break;
            case 4:
                sms.removeStudent();
                break;
            case 5:
                sms.listAllStudents();
                break;
            case 6:
                sms.sortStudentsByGPA();
                break;
            case 7:
                sms.addScore();
                break;
            case 8:
                sms.listAllScores();
                break;
            case 9:
                sms.saveStudentToFile();
                cout << "Data saved. Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 9);

    return 0;
}
