#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Define Course structure
struct Course {
    string number;
    string name;
    vector<string> prerequisites;
};

// Global course map
map<string, Course> courseMap;

// Function to load courses from file
void LoadDataStructure(const string& filename) {
    courseMap.clear();
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        Course course;

        getline(ss, course.number, ',');
        getline(ss, course.name, ',');

        while (getline(ss, token, ',')) {
            course.prerequisites.push_back(token);
        }

        courseMap[course.number] = course;
    }

    file.close();
    cout << "Data loaded successfully.\n";
}

// Function to print course list in alphanumeric order
void PrintCourseList() {
    if (courseMap.empty()) {
        cout << "No data loaded. Please load data first.\n";
        return;
    }

    vector<string> courseNumbers;
    for (const auto& pair : courseMap) {
        courseNumbers.push_back(pair.first);
    }

    sort(courseNumbers.begin(), courseNumbers.end());

    cout << "\nHere is a sample schedule:\n" << endl;
    for (const string& courseNum : courseNumbers) {
        cout << courseNum << ", " << courseMap[courseNum].name << endl;
    }
}

// Function to print information for a specific course
void PrintCourseInfo(const string& courseNumber) {
    string upperCourse = courseNumber;
    transform(upperCourse.begin(), upperCourse.end(), upperCourse.begin(), ::toupper);

    auto it = courseMap.find(upperCourse);
    if (it == courseMap.end()) {
        cout << "Course not found.\n";
        return;
    }

    const Course& course = it->second;
    cout << course.number << ", " << course.name << endl;

    if (!course.prerequisites.empty()) {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < course.prerequisites.size(); ++i) {
            cout << course.prerequisites[i];
            if (i < course.prerequisites.size() - 1)
                cout << ", ";
        }
        cout << endl;
    }
}

// Main menu loop
int main() {
    string filename;
    int choice;

    cout << "Welcome to the course planner.\n" << endl;

    while (true) {
        cout << "\n1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit\n" << endl;
        cout << "What would you like to do? ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            cout << "Enter file name to load: ";
            getline(cin, filename);
            LoadDataStructure(filename);
            break;
        case 2:
            PrintCourseList();
            break;
        case 3: {
            cout << "What course do you want to know about? ";
            string courseNum;
            getline(cin, courseNum);
            PrintCourseInfo(courseNum);
            break;
        }
        case 9:
            cout << "\nThank you for using the course planner!\n";
            return 0;
        default:
            cout << "\n" << choice << " is not a valid option.\n";
            break;
        }
    }

    return 0;
}
