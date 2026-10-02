#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

class ExamResult
{
private:
    int resultID;
    int studentID;
    char studentName[50];
    char examDate[15];
    int totalMarks;
    int marksObtained;
    float percentage;
    char grade[3];

public:

    void calculate()
    {
        if (totalMarks <= 0 || marksObtained < 0 || marksObtained > totalMarks)
        {
            cout << "Invalid marks entered!" << endl;

            percentage = 0;
            strcpy(grade, "F");

            return;
        }

        percentage = (marksObtained * 100.0) / totalMarks;

        if (percentage >= 80)
            strcpy(grade, "A");
        else if (percentage >= 60)
            strcpy(grade, "B");
        else if (percentage >= 40)
            strcpy(grade, "C");
        else
            strcpy(grade, "F");
    }

    void input()
    {
        cout << "Enter Result ID : ";
        cin >> resultID;

        cout << "Enter Student ID : ";
        cin >> studentID;
        cin.ignore();

        cout << "Enter Student Name : ";
        cin.getline(studentName, 50);

        cout << "Enter Exam Date : ";
        cin.getline(examDate, 15);

        cout << "Enter Total Marks : ";
        cin >> totalMarks;

        cout << "Enter Marks Obtained : ";
        cin >> marksObtained;

        calculate();
    }

    void output()
    {
        cout << "\nResult ID : " << resultID;
        cout << "\nStudent ID : " << studentID;
        cout << "\nStudent Name : " << studentName;
        cout << "\nExam Date : " << examDate;
        cout << "\nTotal Marks : " << totalMarks;
        cout << "\nMarks Obtained : " << marksObtained;
        cout << "\nPercentage : " << percentage;
        cout << "\nGrade : " << grade << endl;
    }

    void save()
    {
        fstream fr;

        fr.open("results.dat", ios::out | ios::app);

        fr.write((char*)this, sizeof(*this));

        fr.close();

        cout << "\nResult saved successfully!" << endl;
    }

    void displayall()
    {
        fstream fr;

        fr.open("results.dat", ios::in);

        if (!fr)
        {
            cout << "No results found." << endl;
            return;
        }

        while (fr.read((char*)this, sizeof(*this)))
        {
            output();
            cout << endl;
        }

        fr.close();
    }
    void showstudent(int id)
{
    fstream fr;
    bool found = false;

    fr.open("results.dat", ios::in);

    if (!fr)
    {
        cout << "No results found." << endl;
        return;
    }

    while (fr.read((char*)this, sizeof(*this)))
    {
        if (studentID == id)
        {
            output();
            found = true;
        }
    }

    if (!found)
    {
        cout << "No result found for this student." << endl;
    }

    fr.close();
}
void toppers()
{
    fstream fr;
    int max = 0;
    bool found = false;

    fr.open("results.dat", ios::in);

    if (!fr)
    {
        cout << "No results found." << endl;
        return;
    }

    
    while (fr.read((char*)this, sizeof(*this)))
    {
        if (marksObtained > max)
        {
            max = marksObtained;
        }
    }

    
    fr.clear();
    fr.seekg(0);

    cout << "\nTopper Result(s):\n";

    
    while (fr.read((char*)this, sizeof(*this)))
    {
        if (marksObtained == max)
        {
            output();
            found = true;
        }
    }

    if (!found)
    {
        cout << "No results found." << endl;
    }

    fr.close();
}
void deleteResult()
{
    int id;
    bool found = false;

    cout << "Enter Result ID to Delete : ";
    cin >> id;

    fstream fr, temp;

    fr.open("results.dat", ios::in);

    if (!fr)
    {
        cout << "No results found." << endl;
        return;
    }

    temp.open("temp.dat", ios::out);

    if (!temp)
    {
        cout << "Temporary file could not be created." << endl;
        fr.close();
        return;
    }

    while (fr.read((char*)this, sizeof(*this)))
    {
        if (resultID == id)
        {
            found = true;
        }
        else
        {
            temp.write((char*)this, sizeof(*this));
        }
    }

    fr.close();
    temp.close();

    if (found)
    {
        remove("results.dat");
        rename("temp.dat", "results.dat");

        cout << "Result deleted successfully!" << endl;
    }
    else
    {
        remove("temp.dat");
        cout << "Result not found." << endl;
    }
}
void updateMarks()
{
    int id;
    int pos;
    int newMarks;
    bool found = false;

    cout << "Enter Result ID to update : ";
    cin >> id;

    fstream fr;

    fr.open("results.dat", ios::in | ios::out);

    if (!fr)
    {
        cout << "No results found." << endl;
        return;
    }

    while (true)
    {
        pos = fr.tellg();

        if (!fr.read((char*)this, sizeof(*this)))
            break;

        if (resultID == id)
        {
            cout << "Current Marks : " << marksObtained << endl;
            cout << "Total Marks : " << totalMarks << endl;

            cout << "Enter New Marks : ";
            cin >> newMarks;

            if (newMarks < 0 || newMarks > totalMarks)
            {
                cout << "Invalid marks entered!" << endl;
                fr.close();
                return;
            }

            marksObtained = newMarks;

            calculate();

            fr.seekp(pos);
            fr.write((char*)this, sizeof(*this));

            found = true;
            break;
        }
    }

    fr.close();

    if (found)
        cout << "Marks updated successfully!" << endl;
    else
        cout << "Result ID not found." << endl;
}
};

int main()
{
    ExamResult r;
    int choice;

    do
    {
        cout << "\n\nRESULT MENU\n";
        cout << "1. Add Result\n";
        cout << "2. Display All Results\n";
        cout << "3. Search Result by Student ID\n";
        cout << "4. Display Topper\n";
        cout << "5. Delete Result\n";
        cout << "6. Update Marks\n";
        cout << "7. Exit\n";
        cout << "Enter your choice : ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                r.input();
                r.output();
                r.save();
                break;

            case 2:
                r.displayall();
                break;

            case 3:
            {
                int id;

                cout << "Enter Student ID : ";
                cin >> id;

                r.showstudent(id);
                break;
            }

            case 4:
                r.toppers();
                break;

            case 5:
                r.deleteResult();
                break;

            case 6:
                r.updateMarks();
                break;

            case 7:
                cout << "Exiting..." << endl;
                break;

            default:
                cout << "Invalid choice!" << endl;
        }

    } while(choice != 7);

    return 0;
}