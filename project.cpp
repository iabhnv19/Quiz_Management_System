#include <iostream>
#include <fstream>
using namespace std;

class studentinfo{
private:
int rollnumber;
char name[20];

public:
void input(){
    system("cls");
    cout<<"Enter Student ID/Roll Number : ";
    cin>>rollnumber;
    cin.ignore();
    cout<<"Enter the Name : ";
    cin.getline(name,20);
}

void output(){
    cout<<"Student ID/Roll Number : "<<rollnumber<<"\n"<<"Name : "<<name<<endl;
}
};

class faculty{
private:
int facultyid;
char name[20];

public:
void input(){
    system("cls");
    cout<<"Enter The Faculty ID : ";
    cin>>facultyid;
    cin.ignore();
    cout<<"Enter the Name :";
    cin.getline(name,20);
}
};

class question{
private:
int questionid;
char subject[20];
char question[100];
char optionA[50];
char optionB[50];
char optionC[50];
char optionD[50];
int correctoption;

public:
void subjectlist()
{
    fstream fq;
    char subjects[50][20];
    int subjectCount = 0;
    int choice;
    fq.open("Questions.dat", ios::in);
    if (fq)
    {
        while (fq.read((char*)this, sizeof(*this)))
        {
            if (subject[0] == '\0')
            {
                continue;
            }
            bool alrexists = false;
            for (int i = 0; i < subjectCount; i++)
            {
                if (strcmp(subjects[i], subject) == 0)
                {
                    alrexists = true;
                    break;
                }
            }
            if (!alrexists && subjectCount < 50)
            {
                strcpy(subjects[subjectCount], subject);
                subjectCount++;
            }
        }
        fq.close();
    }

    do{
        system("cls");
        cout << "SUBJECT LIST\n";
        for (int i = 0; i < subjectCount; i++)
        {
            cout << i + 1 << ". " << subjects[i] << endl;
        }
        cout << subjectCount + 1 << ". Add New Subject\n";
        cout << "0. Exit\n";
        cout << "\nEnter your choice : ";
        cin >> choice;
        if (choice >= 1 && choice <= subjectCount)
        {
            strcpy(subject, subjects[choice - 1]);
            cout << "\nSelected Subject: " << subject << endl;
            system("pause");

            break;
        }
        else if (choice == subjectCount + 1)
        {
            cin.ignore();
            cout << "\nEnter New Subject : ";
            cin.getline(subject, 20);
            if (strlen(subject) == 0)
            {
                cout << "\nSubject cannot be empty!\n";
                system("pause");
                continue;
            }
            cout << "\nNew Subject Added: " << subject << endl;
            system("pause");
            break;
        }
    } while (true);
}

void input(){
    cout << "Subject : " << subject << endl;
    cout<<"Enter The Question ID : "<<" ";
    cin>>questionid;
    cin.ignore();
    cout<<"Enter the Question : "<<" ";
    cin.getline(question,100);
    cout<<"\nEnter the Options\n";
    cout<<"Option A : ";
    cin.getline(optionA,50);
    cout<<"Option B : ";
    cin.getline(optionB,50);
    cout<<"Option C : ";
    cin.getline(optionC,50);
    cout<<"Option D : ";
    cin.getline(optionD,50);
    cout<<"\nEnter the Correct Option (1 to 4): ";
    cin>>correctoption;
}

void output(){
    cout << "Subject : " << subject << endl;
    cout<<"QuestionID :"<<questionid<<"\n"<<"Question :"<<"\n"<<question<<endl;
    cout<<"Options :\n";
    cout<<"A. "<<optionA<<endl;
    cout<<"B. "<<optionB<<endl;
    cout<<"C. "<<optionC<<endl;
    cout<<"D. "<<optionD<<endl;
    cout<<"Correct Option : "<<correctoption<<endl;
}

void questionsadd(){
    fstream fq;
    int choice;
    do {
        system("cls");
        input();
        fq.open("Questions.dat", ios::out | ios::app);
        fq.write((char*)this, sizeof(*this));
        fq.close();
        cout << "\nYou Added the Following Question:\n";
        output();   
        cout << "\nDo you want to add a new question?\n";
        cout << "1. Yes\n";
        cout << "2. No\n";
        cout << "Enter your choice: ";
        cin >> choice;
    } while(choice == 1);
}

void displayallquestions(){
    fstream fq;
    system("cls");
    cout << "Displaying Question Bank\n";
    fq.open("Questions.dat", ios::in);
    while (fq.read((char*)this, sizeof(*this)))
    {
        output();
        cout<<endl;
    }
    fq.close();
}

void delrecord(){
    int id;
    system("cls");
    cout<<"Enter Question ID to Delete :\n";
    cin>>id;
    fstream fq, temp;
    fq.open("Questions.dat", ios::in );
    temp.open("temp.dat", ios::out);
    while (fq.read((char*)this, sizeof(*this)))
    {
        if (questionid == id)
        {
            cout << "\nQuestion Found!\n" << endl;
            output();
            cout << "Question deleted successfully!" << endl;
        }
        else
        {
        temp.write((char*)this, sizeof(*this));
     }
    }
        fq.close();
        temp.close();
        remove("Questions.dat");
        rename("temp.dat", "Questions.dat");    
}

void find(){
    fstream fq;
    int id;
    int choice;
    char findquestion[100];
    system("cls");
    cout<<"Find by Id Or Question :\n";
    cout<<"1. Find by ID\n";
    cout<<"2. Find by Question\n";
    cout<<"\nEnter your choice : ";
    cin>>choice;
    switch(choice){
        case 1:
            cout<<"\nEnter Question ID to Find :\n";
            cin>>id;
            fq.open("Questions.dat", ios::in);
            while (fq.read((char*)this, sizeof(*this)))
            {
                if (questionid == id)
                {
                    cout << "\nQuestion Found!\n" << endl;
                    output();
                }
            }
            fq.close();
            break;
        case 2:
            cin.ignore();
            cout<<"\nEnter Question to Find :\n";
            cin.getline(findquestion, 100);
            fq.open("Questions.dat", ios::in);
            while (fq.read((char*)this, sizeof(*this))){
                bool found = false;
                for (int i = 0; question[i] != '\0'; i++){
                    int j = 0;
                    while (findquestion[j] != '\0' && question[i + j] == findquestion[j])
                    {
                        j++;
                    }
                    if (findquestion[j] == '\0')
                    {
                        found = true;
                        break;
                    }
                }

                if (found)
                {
                    cout << "\nQuestion Found!\n" << endl;
                    output();
                }
            }
            fq.close();
            break;
    }
}

void replacedata(){
    system("cls");
    find();
}
};

class exam:public question{

public:
void selectsub(){
    subjectlist();
} 

void rules(){
    system("cls");
    cout<<"Rules of Exam :\n";
    cout<<"1. Each Question carries 1 mark.\n";
    cout<<"2. No Negative Marking.\n";
    system("pause");
}

};

class examresult{
private:
    int studentid;
    char studentname[50];
    char examdate[15];
    int totalmarks;
    int marksobtained;
    float percentage;
    char grade[3];
    
public:
void calculate(){
    percentage = (marksobtained * 100.0) / totalmarks;
    if (percentage >= 80)
        strcpy(grade, "A");
    else if (percentage >= 60)
        strcpy(grade, "B");
    else if (percentage >= 40)
        strcpy(grade, "C");
    else
        strcpy(grade, "F");
}

void input(){
    system("cls");
    cout << "Enter Student ID : ";
    cin >> studentid;
    cin.ignore();
    cout << "Enter Student Name : ";
    cin.getline(studentname, 50);
    cout << "Enter Exam Date : ";
    cin.getline(examdate, 15);
    cout << "Enter Total Marks : ";
    cin >> totalmarks;
    cout << "Enter Marks Obtained : ";
    cin >> marksobtained;
    calculate();
}

int resultid = studentid + marksobtained;

void output(){
    system("cls");
    cout << "\nResult ID : " << resultid;
    cout << "\nStudent ID : " << studentid;
    cout << "\nStudent Name : " << studentname;
    cout << "\nExam Date : " << examdate;
    cout << "\nTotal Marks : " << totalmarks;
    cout << "\nMarks Obtained : " <<marksobtained;
    cout << "\nPercentage : " << percentage;
    cout << "\nGrade : " << grade << endl;
}

void save(){
    fstream fr;
    fr.open("results.dat", ios::out | ios::app);
    fr.write((char*)this, sizeof(*this));
    fr.close();
    cout << "\nResult saved successfully!" << endl;
}

void displayall(){
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

void showstudent(int id){
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
        if (studentid == id)
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

void toppers(){
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
        if (marksobtained > max)
        {
            max = marksobtained;
        }
    }
    fr.clear();
    fr.seekg(0);
    cout << "\nTopper Result(s):\n";
    while (fr.read((char*)this, sizeof(*this)))
    {
        if (marksobtained == max)
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

void deleteresult(){
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
        if (resultid == id)
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

void updatemarks(){
    int id;
    int pos;
    int newmarks;
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
        if (resultid == id)
        {
            cout << "Current Marks : " << marksobtained << endl;
            cout << "Total Marks : " << totalmarks << endl;
            cout << "Enter New Marks : ";
            cin >> newmarks;
            if (newmarks < 0 || newmarks > totalmarks)
            {
                cout << "Invalid marks entered!" << endl;
                fr.close();
                return;
            }
            marksobtained = newmarks;
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

void resultmenufaculty(){
    int choice;
    do
    {
        system("cls");
        cout << "RESULT MENU\n";
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
                input();
                output();
                save();
                system("pause");
                break;

            case 2:
                displayall();
                system("pause");
                break;

            case 3:
            {
                int id;
                cout << "Enter Student ID : ";
                cin >> id;
                showstudent(id);
                system("pause");
                break;
            }
            case 4:
                toppers();
                system("pause");
                break;
            case 5:
                deleteresult();
                system("pause");
                break;
            case 6:
                updatemarks();
                system("pause");
                break;
            case 7:
                cout << "Exiting..." << endl;
                system("pause");
                break;
        }

    } while(choice != 7);

}

void resultmenustudent(){
    int choice;
    do
    {
        system("cls");
        cout << "RESULT MENU\n";
        cout << "1. Display All Results\n";
        cout << "2. Search Result by Student ID\n";
        cout << "3. Display Topper\n";
        cout << "4. Exit\n";
        cout << "Enter your choice : ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                displayall();
                system("pause");
                break;
            case 2:
            {
                int id;
                cout << "Enter Student ID : ";
                cin >> id;
                showstudent(id);
                system("pause");
                break;
            }
            case 3:
                toppers();
                system("pause");
                break;
            case 4:
                cout << "Exiting..." << endl;
                system("pause");
                break;
        }

    } while(choice != 4);

}
};

class menu:public question,public examresult{
private:
int choice;

void facultylogin(){
    faculty f;
    int choice;
    f.input();
    subjectlist();
    do {
        system("cls");
        displayfaculty();
        cin >> choice;
        switch(choice){
            case 1:
                displayallquestions();
                system("pause");
                break;
            case 2:
                questionsadd();
                system("pause");
                break;
            case 3:
                delrecord();
                system("pause");
                break;
            case 4:
                replacedata();
                system("pause");
                break;
            case 5:
                resultmenufaculty();
                system("pause");
                break;
            case 6:
                cout << "Exiting..." << endl;
                system("pause");
                break;
        }
    } while(choice != 6);
}

void studentlogin(){
    int choice;
    studentinfo s;
    exam e;
    s.input();
    system("pause");
    do{
        system("cls");
        s.output();
        cout<<"\nStudent Menu\n";
        cout<<"1. Start Exam\n";
        cout<<"2. View Results\n";
        cout<<"3. Exit\n";
        cout<<"Enter your choice : ";
        cin>>choice;
        switch (choice){
            case 1:
                e.selectsub();
                e.rules();
                system("pause");
                break;
            case 2:
                resultmenustudent();
                system("pause");
                break;
            case 3:
                cout << "Exiting..." << endl;
                system("pause");
                break;
        }
    }while(choice != 3);
}

void displayfaculty(){
    system("cls");
    cout<<"Faculty Menu\n";
    cout<<"1. Display Question Bank \n";
    cout<<"2. Add Questions\n";
    cout<<"3. Delete Question\n";
    cout<<"4. Replace Question\n";
    cout<<"5. Result Menu\n";
    cout<<"6. Exit\n";
    cout<<"Enter your choice : ";
}

void display(){
    cout<<"Context Menu\n";
    cout<<"1. Faculty Login\n";
    cout<<"2. Student Login\n";
    cout<<"Enter your choice : ";
    cin>>choice;
}

public:
void mainmenu(){
    do{
        system("cls");
        display();
        switch(choice){
            case 1:
                facultylogin();
                break;
            case 2:
                studentlogin();
                break;
        }
    }while(choice != 2);
}
};

int main(){
    menu m;
    m.mainmenu();
    return 0;
}