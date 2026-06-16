#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

const int MAX_STUDENTS = 100;
const int MAX_COURSES = 50;
const int MAX_ENROLLMENTS = 200;
const int MAX_ATTENDANCE = 1500;
const int MAX_FEES = 100;

struct Student {
    string roll_no;
    string name;
    string department;
    int semester;
    double cgpa;
    string status;
};

struct Course {
    string course_code;
    string course_name;
    int credit_hours;
    string instructor;
    int capacity;
    int enrolled;
    string prerequisite;
};

struct Enrollment {
    string enrollment_id;
    string roll_no;
    string course_code;
    int semester;
    string enrollment_date;
    string status;
};

struct Attendance {
    string log_id;
    string roll_no;
    string course_code;
    string session_date;
    char status;
};

struct Fee {
    string fee_id;
    string roll_no;
    int semester;
    double total_fee;
    double amount_paid;
    string due_date;
    string payment_date;
    string payment_method;
    string status;
};

void parseCommaLine(string line, string arr[], int maxFields) {
    int fieldCount = 0;
    string currentField = "";
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == ',' || line[i] == '\r' || line[i] == '\n') {
            if (fieldCount < maxFields) {
                arr[fieldCount++] = currentField;
            }
            currentField = "";
        } else {
            currentField += line[i];
        }
    }
    if (fieldCount < maxFields) {
        arr[fieldCount] = currentField;
    }
}

int safeStoi(string s) {
    if (s.empty()) return 0;
    string cleanStr = "";
    for(int i=0; i<s.length(); i++) {
        if(isdigit(s[i]) || s[i] == '-') cleanStr += s[i];
    }
    if (cleanStr.empty() || cleanStr == "-") return 0;

    stringstream ss(cleanStr);
    int val = 0;
    ss >> val;
    return val;
}

double safeStod(string s) {
    if (s.empty()) return 0.0;
    string cleanStr = "";
    for(int i=0; i<s.length(); i++) {
        if(isdigit(s[i]) || s[i] == '.' || s[i] == '-') cleanStr += s[i];
    }
    if (cleanStr.empty() || cleanStr == "-") return 0.0;

    stringstream ss(cleanStr);
    double val = 0.0;
    ss >> val;
    return val;
}

int loadStudents(Student students[]) {
    ifstream file("../students.txt");
    if (!file.is_open()) return 0;

    string line;
    getline(file, line);

    int count = 0;
    while (getline(file, line) && count < MAX_STUDENTS) {
        if (line.empty() || line == "\r" || line == "\n") continue;
        string fields[6];
        parseCommaLine(line, fields, 6);

        if(fields[0].empty()) continue;

        students[count].roll_no = fields[0];
        students[count].name = fields[1];
        students[count].department = fields[2];
        students[count].semester = safeStoi(fields[3]);
        students[count].cgpa = safeStod(fields[4]);
        students[count].status = fields[5];
        count++;
    }
    file.close();
    return count;
}

int loadCourses(Course courses[]) {
    ifstream file("../courses.txt");
    if (!file.is_open()) return 0;

    string line;
    getline(file, line);

    int count = 0;
    while (getline(file, line) && count < MAX_COURSES) {
        if (line.empty() || line == "\r" || line == "\n") continue;
        string fields[7];
        parseCommaLine(line, fields, 7);

        if(fields[0].empty()) continue;

        courses[count].course_code = fields[0];
        courses[count].course_name = fields[1];
        courses[count].credit_hours = safeStoi(fields[2]);
        courses[count].instructor = fields[3];
        courses[count].capacity = safeStoi(fields[4]);
        courses[count].enrolled = safeStoi(fields[5]);
        courses[count].prerequisite = fields[6];
        count++;
    }
    file.close();
    return count;
}

int loadEnrollments(Enrollment enrollments[]) {
    ifstream file("../enrollments.txt");
    if (!file.is_open()) return 0;

    string line;
    getline(file, line);

    int count = 0;
    while (getline(file, line) && count < MAX_ENROLLMENTS) {
        if (line.empty() || line == "\r" || line == "\n") continue;
        string fields[6];
        parseCommaLine(line, fields, 6);

        if(fields[0].empty()) continue;

        enrollments[count].enrollment_id = fields[0];
        enrollments[count].roll_no = fields[1];
        enrollments[count].course_code = fields[2];
        enrollments[count].semester = safeStoi(fields[3]);
        enrollments[count].enrollment_date = fields[4];
        enrollments[count].status = fields[5];
        count++;
    }
    file.close();
    return count;
}

int loadAttendance(Attendance attendanceLogs[]) {
    ifstream file("../attendance_log.txt");
    if (!file.is_open()) return 0;

    string line;
    getline(file, line);

    int count = 0;
    while (getline(file, line) && count < MAX_ATTENDANCE) {
        if (line.empty() || line == "\r" || line == "\n") continue;
        string fields[5];
        parseCommaLine(line, fields, 5);

        if(fields[0].empty()) continue;

        attendanceLogs[count].log_id = fields[0];
        attendanceLogs[count].roll_no = fields[1];
        attendanceLogs[count].course_code = fields[2];
        attendanceLogs[count].session_date = fields[3];
        if (!fields[4].empty()) {
            attendanceLogs[count].status = fields[4][0];
        }
        count++;
    }
    file.close();
    return count;
}

int loadFees(Fee fees[]) {
    ifstream file("../fees.txt");
    if (!file.is_open()) return 0;

    string line;
    getline(file, line);

    int count = 0;
    while (getline(file, line) && count < MAX_FEES) {
        if (line.empty() || line == "\r" || line == "\n") continue;
        string fields[9];
        parseCommaLine(line, fields, 9);

        if(fields[0].empty()) continue;

        fees[count].fee_id = fields[0];
        fees[count].roll_no = fields[1];
        fees[count].semester = safeStoi(fields[2]);
        fees[count].total_fee = safeStod(fields[3]);
        fees[count].amount_paid = safeStod(fields[4]);
        fees[count].due_date = fields[5];
        fees[count].payment_date = fields[6];
        fees[count].payment_method = fields[7];
        fees[count].status = fields[8];
        count++;
    }
    file.close();
    return count;
}

void showStudents(Student students[], int count) {
    cout << "\n--- Student List ---" << endl;
    for(int i = 0; i < count; i++) {
        cout << "Roll: " << students[i].roll_no
             << " | Name: " << students[i].name
             << " | Dept: " << students[i].department
             << " | CGPA: " << students[i].cgpa << endl;
    }
}

void showCourses(Course courses[], int count) {
    cout << "\n--- Course List ---" << endl;
    for(int i = 0; i < count; i++) {
        cout << "Code: " << courses[i].course_code
             << " | Name: " << courses[i].course_name
             << " | Instructor: " << courses[i].instructor
             << " | Enrolled: " << courses[i].enrolled << "/" << courses[i].capacity << endl;
    }
}

void showProbationStudents(Student students[], int count) {
    cout << "\n--- Academic Probation List (CGPA < 2.0) ---" << endl;
    int foundCount = 0;
    for (int i = 0; i < count; i++) {
        if (students[i].cgpa < 2.0) {
            cout << "Roll No: " << students[i].roll_no
                 << " | Name: " << students[i].name
                 << " | Dept: " << students[i].department
                 << " | CGPA: " << students[i].cgpa << endl;
            foundCount++;
        }
    }
    if (foundCount == 0) {
        cout << "No students are currently on academic probation." << endl;
    }
}

void showTopPerformers(Student students[], int count) {
    cout << "\n--- Top Academic Performers ---" << endl;
    if (count == 0) return;

    Student top1 = students[0];
    Student top2 = students[0];
    Student top3 = students[0];

    top2.cgpa = -1.0;
    top3.cgpa = -1.0;

    for (int i = 1; i < count; i++) {
        if (students[i].cgpa > top1.cgpa) {
            top3 = top2;
            top2 = top1;
            top1 = students[i];
        } else if (students[i].cgpa > top2.cgpa) {
            top3 = top2;
            top2 = students[i];
        } else if (students[i].cgpa > top3.cgpa) {
            top3 = students[i];
        }
    }

    cout << "1st Rank: " << top1.name << " (" << top1.roll_no << ") - CGPA: " << top1.cgpa << " [" << top1.department << "]" << endl;
    if (top2.cgpa != -1.0) {
        cout << "2nd Rank: " << top2.name << " (" << top2.roll_no << ") - CGPA: " << top2.cgpa << " [" << top2.department << "]" << endl;
    }
    if (top3.cgpa != -1.0) {
        cout << "3rd Rank: " << top3.name << " (" << top3.roll_no << ") - CGPA: " << top3.cgpa << " [" << top3.department << "]" << endl;
    }
}

void showPopularCourses(Course courses[], int count) {
    cout << "\n--- Most Popular Courses (Highest Enrollment) ---" << endl;
    if (count == 0) return;

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (courses[j].enrolled < courses[j+1].enrolled) {
                Course temp = courses[j];
                courses[j] = courses[j+1];
                courses[j+1] = temp;
            }
        }
    }

    int limit = (count < 3) ? count : 3;
    for (int i = 0; i < limit; i++) {
        cout << i + 1 << ". " << courses[i].course_name << " (" << courses[i].course_code << ") - Enrolled: " << courses[i].enrolled << " Students" << endl;
    }
}

void checkLowAttendance(Student students[], int sCount, Attendance attendanceLogs[], int aCount) {
    cout << "\n--- Attendance Alert (Below 75%) ---" << endl;
    int alertCount = 0;
    for (int i = 0; i < sCount; i++) {
        int totalSessions = 0;
        int presentSessions = 0;

        for (int j = 0; j < aCount; j++) {
            if (attendanceLogs[j].roll_no == students[i].roll_no) {
                totalSessions++;
                if (attendanceLogs[j].status == 'P' || attendanceLogs[j].status == 'p') {
                    presentSessions++;
                }
            }
        }

        if (totalSessions > 0) {
            double percentage = ((double)presentSessions / totalSessions) * 100.0;
            if (percentage < 75.0) {
                cout << "Roll No: " << students[i].roll_no
                     << " | Name: " << students[i].name
                     << " | Attendance: " << percentage << "%" << endl;
                alertCount++;
            }
        }
    }
  if (alertCount == 0) {
        cout << "All students have satisfactory attendance records." << endl;
    }
}

void showFeeDefaulters(Student students[], int sCount, Fee fees[], int fCount) {
    cout << "\n--- Financial Fee Defaulters List ---" << endl;
    int defaulterCount = 0;
    for (int i = 0; i < fCount; i++) {
        double pending = fees[i].total_fee - fees[i].amount_paid;
        if (pending > 0) {
            string studentName = "Unknown Student";
            for (int j = 0; j < sCount; j++) {
                if (students[j].roll_no == fees[i].roll_no) {
                    studentName = students[j].name;
                    break;
                }
            }
            cout << "Roll No: " << fees[i].roll_no
                 << " | Name: " << studentName
                 << " | Owed: " << pending
                 << " PKR | Status: " << fees[i].status << endl;
            defaulterCount++;
        }
    }
    if (defaulterCount == 0) {
        cout << "All accounts clear. No fee defaulters found!" << endl;
    }
}

void showFinancialSummary(Fee fees[], int count) {
    cout << "\n--- University Financial Summary ---" << endl;
    double totalCollected = 0.0;
    double totalPending = 0.0;
    for (int i = 0; i < count; i++) {
        totalCollected += fees[i].amount_paid;
        totalPending += (fees[i].total_fee - fees[i].amount_paid);
    }
    cout << "Total Revenue Collected: " << totalCollected << " PKR" << endl;
    cout << "Total Revenue Pending:   " << totalPending << " PKR" << endl;
    cout << "Expected Gross Income:   " << (totalCollected + totalPending) << " PKR" << endl;
}

int main() {
    Student students[MAX_STUDENTS];
    Course courses[MAX_COURSES];
    Enrollment enrollments[MAX_ENROLLMENTS];
    Attendance attendanceLogs[MAX_ATTENDANCE];
    Fee fees[MAX_FEES];

    int studentCount = loadStudents(students);
    int courseCount = loadCourses(courses);
    int enrollmentCount = loadEnrollments(enrollments);
    int attendanceCount = loadAttendance(attendanceLogs);
    int feeCount = loadFees(fees);

    int choice = 0;
    while(choice != 10) {
        cout << "      CAMPUS ANALYTICS ENGINE MENU        " << endl;
        cout << "1. View All Students" << endl;
        cout << "2. View All Courses" << endl;
        cout << "3. View Academic Probation List" << endl;
        cout << "4. View Top Academic Performers" << endl;
        cout << "5. View Most Popular Courses" << endl;
        cout << "6. View Low Attendance Alerts" << endl;
        cout << "7. View Fee Defaulters List" << endl;
        cout << "8. View Financial Revenue Summary" << endl;
        cout << "9. View System Status Summary" << endl;
        cout << "10. Exit Application" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            showStudents(students, studentCount);
        }
        else if (choice == 2) {
            showCourses(courses, courseCount);
        }
        else if (choice == 3) {
            showProbationStudents(students, studentCount);
        }
        else if (choice == 4) {
            showTopPerformers(students, studentCount);
        }
        else if (choice == 5) {
            showPopularCourses(courses, courseCount);
        }
        else if (choice == 6) {
            checkLowAttendance(students, studentCount, attendanceLogs, attendanceCount);
        }
        else if (choice == 7) {
            showFeeDefaulters(students, studentCount, fees, feeCount);
        }
        else if (choice == 8) {
            showFinancialSummary(fees, feeCount);
        }
        else if (choice == 9) {
            cout << "\n--- System Status Summary ---" << endl;
            cout << "Total Students Loaded:    " << studentCount << endl;
            cout << "Total Courses Loaded:     " << courseCount << endl;
            cout << "Total Enrollments Loaded: " << enrollmentCount << endl;
            cout << "Total Attendance Records: " << attendanceCount << endl;
            cout << "Total Fee Sheets Loaded:  " << feeCount << endl;
        }
        else if (choice == 10) {
            cout << "\nExiting application. Goodbye!" << endl;
        }
        else {
            cout << "\nInvalid choice! Please try again." << endl;
        }
    }

    return 0;
}
