#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Person {
    protected:
    string name;
    string dateOfBirth;
    public:
    string getName() {
        return name;
    }
    void input();
    void output();
};

class Subject {
    protected:
    string subjectTitle;
    float attendance;
    float midtermExam;
    float finalExam;
    public:
    
    float getAttendance() {
        return attendance;
    }
    float getMidtermExam() {
        return midtermExam;
    }
    float sumScore() {
        return attendance + midtermExam + finalExam;
    }
    void input();
    void output();
};

class Student : public Person, public Subject {
    string id;
    float overallScore;
    public:
    
    string getID() {
        return id;
    }
    float getOS() {
        return sumScore() / 3;
    } 
    void input();
    void output();
};

//********************************************************************
void Person::input() {
    cout << "Enter your name: ";
    getline(cin, name);
    cout << "Enter your date of birth: ";
    getline(cin, dateOfBirth);
}
void Person::output() {
    cout << left << setw(20) << name << setw(15) << dateOfBirth;
}

void Subject::input() {
    cout << "Enter the title of the subject: ";
    getline(cin, subjectTitle);
    cout << "Enter attendance: ";
    cin >> attendance;
    cout << "Enter mid-term exam: ";
    cin >> midtermExam;
    cout << "Enter final exam: ";
    cin >> finalExam;
    cin.ignore();
}
void Subject::output() {
    cout << left << setw(20) << subjectTitle << setw(15) << attendance 
    << setw(15) << midtermExam << setw(15) << finalExam;
}

void Student::input() {
    cout << "ID Student: ";
    getline(cin, id);
    Person::input();
    Subject::input();
}
void Student::output() {
    cout << left << setw(10) << id;
    Person::output();
    Subject::output();
    cout << endl;
}

//********************************************************************
void sortStudents(Student *students, int n) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(students[i].getOS() < students[j].getOS()) {
                swap(students[i], students[j]);
            }
        }
    }
}

void banStudents(Student *students, int n) {
    bool banned = false;
    for(int i = 0; i < n; i++) {
        if(students[i].getAttendance() < 5 || students[i].getMidtermExam() == 0) {
            students[i].output();
            banned = true;
        }
    }
    if(!banned) {
        cout << "No student will be banned from taking the exam.";
    }
}

void searchStudents(Student *students, int n, string key) {
    for(int i = 0; i < n; i++) {
        if(students[i].getID() == key || students[i].getName() == key) {
            students[i].output();
        }
    }
}

void header() {
    cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(15) << "Date of Birth" << setw(20) << "Subject Title" 
    << setw(15) << "Attendance" << setw(15) << "Mid-term Exam" << setw(15) << "Final Exam" << endl;
}



int main() {
    int n;
    cout << "Enter student number: ";
    cin >> n;
    cin.ignore();
    Student *student = new Student[n];

    for(int i = 0; i < n; i++) {
        student[i].input();
        cout << endl;
    }
    sortStudents(student, n);
    cout << "List student sorted." << endl;
    header();
    for(int i = 0; i < n; i++) {
        student[i].output();
    }

    cout << "\nList student ban test." << endl;
    header();
    banStudents(student, n);
    
    
    
    string key;
    cout << "\nEnter id or name student for search: " << endl;
    getline(cin, key);
    cout << "Search result: " << endl;
    header();
    searchStudents(student, n, key);

    cout << "\nThe student has the highest overall score: " << endl;
    header();
    student[0].output();

    delete[] student;
    return 0;
}