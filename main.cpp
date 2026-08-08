#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

const int MAX_STUDENTS = 100;
const string FILE_NAME = "students.txt";

struct Student{
    int roll;
    string name;
    int age;
    string course;
};

Student students[MAX_STUDENTS];
int totalStudents = 0;

void addStudent();
void viewStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
void sortStudents();
void saveToFile();
void loadFromFile();
bool rollExists(int roll);

bool rollExists(int roll){
    for (int i = 0; i < totalStudents; i++){
        if (students[i].roll == roll){
            return true;
        }
    }
    return false;
}

void saveToFile()
{
    ofstream file(FILE_NAME);

    if (!file)
    {
        cout << "\nError: Could not save student data!\n";
        return;
    }

    for (int i = 0; i < totalStudents; i++)
    {
        file << students[i].roll << "|"
             << students[i].name << "|"
             << students[i].age << "|"
             << students[i].course << "\n";
    }

    file.close();
}

void loadFromFile()
{
    ifstream file(FILE_NAME);

    if (!file)
    {
        return;
    }

    totalStudents = 0;

    while (totalStudents < MAX_STUDENTS)
    {
        string rollString;
        string name;
        string ageString;
        string course;

        if (!getline(file, rollString, '|'))
            break;

        if (!getline(file, name, '|'))
            break;

        if (!getline(file, ageString, '|'))
            break;

        if (!getline(file, course))
            break;

        int roll;
        int age;

        try
        {
            roll = stoi(rollString);
            age = stoi(ageString);
        }
        catch (...)
        {
            continue;
        }

        if (rollExists(roll))
        {
            continue;
        }

        students[totalStudents].roll = roll;
        students[totalStudents].name = name;
        students[totalStudents].age = age;
        students[totalStudents].course = course;

        totalStudents++;
    }

    file.close();
}

void addStudent()
{
    if (totalStudents >= MAX_STUDENTS)
    {
        cout << "\nDatabase Full!\n";
        return;
    }

    int roll;

    cout << "\n========== ADD STUDENT ==========\n";
    cout << "Enter Roll Number: ";
    cin >> roll;

    if (roll <= 0)
    {
        cout << "\nError: Roll number must be positive!\n";
        return;
    }

    if (rollExists(roll))
    {
        cout << "\nError: Roll number already exists!\n";
        return;
    }

    students[totalStudents].roll = roll;

    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, students[totalStudents].name);

    if (students[totalStudents].name.empty())
    {
        cout << "\nError: Name cannot be empty!\n";
        return;
    }

    cout << "Enter Age: ";
    cin >> students[totalStudents].age;

    if (students[totalStudents].age <= 0 ||
        students[totalStudents].age > 100)
    {
        cout << "\nError: Invalid age!\n";
        return;
    }

    cin.ignore();

    cout << "Enter Course: ";
    getline(cin, students[totalStudents].course);

    if (students[totalStudents].course.empty())
    {
        cout << "\nError: Course cannot be empty!\n";
        return;
    }

    totalStudents++;

    saveToFile();

    cout << "\nStudent Added Successfully!\n";
}

void viewStudents()
{
    if (totalStudents == 0)
    {
        cout << "\nNo Students Found!\n";
        return;
    }

    cout << "\n========== STUDENT LIST ==========\n";

    for (int i = 0; i < totalStudents; i++)
    {
        cout << "\nStudent " << i + 1 << "\n";
        cout << "----------------------------------\n";
        cout << "Roll Number : " << students[i].roll << "\n";
        cout << "Name        : " << students[i].name << "\n";
        cout << "Age         : " << students[i].age << "\n";
        cout << "Course      : " << students[i].course << "\n";
    }
}

void searchStudent()
{
    if (totalStudents == 0)
    {
        cout << "\nNo Students Available!\n";
        return;
    }

    int roll;

    cout << "\n========== SEARCH STUDENT ==========\n";
    cout << "Enter Roll Number to Search: ";
    cin >> roll;

    for (int i = 0; i < totalStudents; i++)
    {
        if (students[i].roll == roll)
        {
            cout << "\nStudent Found!\n";
            cout << "----------------------------------\n";
            cout << "Roll Number : " << students[i].roll << "\n";
            cout << "Name        : " << students[i].name << "\n";
            cout << "Age         : " << students[i].age << "\n";
            cout << "Course      : " << students[i].course << "\n";

            return;
        }
    }

    cout << "\nStudent Not Found!\n";
}

void updateStudent()
{
    if (totalStudents == 0)
    {
        cout << "\nNo Students Available!\n";
        return;
    }

    int roll;

    cout << "\n========== UPDATE STUDENT ==========\n";
    cout << "Enter Roll Number to Update: ";
    cin >> roll;

    for (int i = 0; i < totalStudents; i++)
    {
        if (students[i].roll == roll)
        {
            cout << "\nCurrent Student Details\n";
            cout << "----------------------------------\n";
            cout << "Roll Number : " << students[i].roll << "\n";
            cout << "Name        : " << students[i].name << "\n";
            cout << "Age         : " << students[i].age << "\n";
            cout << "Course      : " << students[i].course << "\n";

            cin.ignore();

            string newName;
            int newAge;
            string newCourse;

            cout << "\nEnter New Name: ";
            getline(cin, newName);

            if (newName.empty())
            {
                cout << "\nError: Name cannot be empty!\n";
                return;
            }

            cout << "Enter New Age: ";
            cin >> newAge;

            if (newAge <= 0 || newAge > 100)
            {
                cout << "\nError: Invalid age!\n";
                return;
            }

            cin.ignore();

            cout << "Enter New Course: ";
            getline(cin, newCourse);

            if (newCourse.empty())
            {
                cout << "\nError: Course cannot be empty!\n";
                return;
            }

            students[i].name = newName;
            students[i].age = newAge;
            students[i].course = newCourse;

            saveToFile();

            cout << "\nStudent Updated Successfully!\n";

            return;
        }
    }

    cout << "\nStudent Not Found!\n";
}

void deleteStudent()
{
    if (totalStudents == 0)
    {
        cout << "\nNo Students Available!\n";
        return;
    }

    int roll;

    cout << "\n========== DELETE STUDENT ==========\n";
    cout << "Enter Roll Number to Delete: ";
    cin >> roll;

    for (int i = 0; i < totalStudents; i++)
    {
        if (students[i].roll == roll)
        {
            cout << "\nStudent Found:\n";
            cout << "Name   : " << students[i].name << "\n";
            cout << "Course : " << students[i].course << "\n";

            char confirm;

            cout << "\nAre you sure you want to delete this student? (Y/N): ";
            cin >> confirm;

            if (confirm != 'Y' && confirm != 'y')
            {
                cout << "\nDeletion Cancelled.\n";
                return;
            }

            for (int j = i; j < totalStudents - 1; j++)
            {
                students[j] = students[j + 1];
            }

            totalStudents--;

            saveToFile();

            cout << "\nStudent Deleted Successfully!\n";

            return;
        }
    }

    cout << "\nStudent Not Found!\n";
}

void sortStudents()
{
    if (totalStudents == 0)
    {
        cout << "\nNo Students Available!\n";
        return;
    }

    int choice;

    cout << "\n========== SORT STUDENTS ==========\n";
    cout << "1. Sort by Roll Number\n";
    cout << "2. Sort by Name\n";
    cout << "3. Sort by Age\n";
    cout << "4. Sort by Course\n";
    cout << "5. Back\n";
    cout << "----------------------------------\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        sort(students, students + totalStudents,
             [](const Student& a, const Student& b)
             {
                 return a.roll < b.roll;
             });

        cout << "\nStudents Sorted by Roll Number!\n";
        break;

    case 2:
        sort(students, students + totalStudents,
             [](const Student& a, const Student& b)
             {
                 return a.name < b.name;
             });

        cout << "\nStudents Sorted by Name!\n";
        break;

    case 3:
        sort(students, students + totalStudents,
             [](const Student& a, const Student& b)
             {
                 return a.age < b.age;
             });

        cout << "\nStudents Sorted by Age!\n";
        break;

    case 4:
        sort(students, students + totalStudents,
             [](const Student& a, const Student& b)
             {
                 return a.course < b.course;
             });

        cout << "\nStudents Sorted by Course!\n";
        break;

    case 5:
        return;

    default:
        cout << "\nInvalid Choice!\n";
        return;
    }

    saveToFile();
}

int main()
{
    int choice;

    loadFromFile();

    cout << "\n==========================================\n";
    cout << "       COLLEGE MANAGEMENT SYSTEM\n";
    cout << "==========================================\n";

    if (totalStudents > 0)
    {
        cout << "Loaded " << totalStudents
             << " student(s) from database.\n";
    }

    do
    {
        cout << "\n==========================================\n";
        cout << "       COLLEGE MANAGEMENT SYSTEM\n";
        cout << "==========================================\n";

        cout << "1. Add Student\n";
        cout << "2. View Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Sort Students\n";
        cout << "7. Exit\n";

        cout << "------------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addStudent();
            break;

        case 2:
            viewStudents();
            break;

        case 3:
            searchStudent();
            break;

        case 4:
            updateStudent();
            break;

        case 5:
            deleteStudent();
            break;

        case 6:
            sortStudents();
            break;

        case 7:
            saveToFile();
            cout << "\nData Saved Successfully!\n";
            cout << "Thank You for Using College Management System!\n";
            break;

        default:
            cout << "\nInvalid Choice! Please try again.\n";
        }

    } while (choice != 7);

    return 0;
}


