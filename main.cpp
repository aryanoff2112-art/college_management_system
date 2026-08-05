#include <iostream>
#include <string>
using namespace std;

const int MAX = 100;

struct Student
{
    int roll;
    string name;
    int age;
    string course;
};

Student students[MAX];
int totalStudents = 0;

void addStudent()
{
    if (totalStudents == MAX)
    {
        cout << "\nDatabase Full!\n";
        return;
    }

    cout << "\nEnter Roll Number: ";
    cin >> students[totalStudents].roll;

    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, students[totalStudents].name);

    cout << "Enter Age: ";
    cin >> students[totalStudents].age;

    cin.ignore();

    cout << "Enter Course: ";
    getline(cin, students[totalStudents].course);

    totalStudents++;

    cout << "\nStudent Added Successfully!\n";
}

void viewStudents()
{
    if (totalStudents == 0)
    {
        cout << "\nNo Students Found!\n";
        return;
    }

    cout << "\n========= STUDENT LIST =========\n";

    for (int i = 0; i < totalStudents; i++)
    {
        cout << "\nStudent " << i + 1 << endl;
        cout << "Roll Number : " << students[i].roll << endl;
        cout << "Name        : " << students[i].name << endl;
        cout << "Age         : " << students[i].age << endl;
        cout << "Course      : " << students[i].course << endl;
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
    cout << "\nEnter Roll Number to Search: ";
    cin >> roll;

    for (int i = 0; i < totalStudents; i++)
    {
        if (students[i].roll == roll)
        {
            cout << "\nStudent Found!\n";
            cout << "Roll Number : " << students[i].roll << endl;
            cout << "Name        : " << students[i].name << endl;
            cout << "Age         : " << students[i].age << endl;
            cout << "Course      : " << students[i].course << endl;
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
    cout << "\nEnter Roll Number to Delete: ";
    cin >> roll;

    for (int i = 0; i < totalStudents; i++)
    {
        if (students[i].roll == roll)
        {
            for (int j = i; j < totalStudents - 1; j++)
            {
                students[j] = students[j + 1];
            }

            totalStudents--;

            cout << "\nStudent Deleted Successfully!\n";
            return;
        }
    }

    cout << "\nStudent Not Found!\n";
}

int main()
{
    int choice;

    do
    {
        cout << "\n====================================";
        cout << "\n     COLLEGE MANAGEMENT SYSTEM";
        cout << "\n====================================";
        cout << "\n1. Add Student";
        cout << "\n2. View Students";
        cout << "\n3. Search Student";
        cout << "\n4. Delete Student";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
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
            deleteStudent();
            break;

        case 5:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 5);

    return 0;
}
