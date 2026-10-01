#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

class studentinfo{
private:
int rollnumber;
char name[20];

public:
void input(){
    cout<<"Enter The Question ID : "<<endl;
    cin>>rollnumber;
    cout<<"Enter the Question :"<<endl;
    cin.getline(name,20);
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
void subjectlist(){
    /*fstream fq;
    system("cls");
    cout << "Subjects :\n";
    fq.open("Questions.dat", ios::in);
    while (fq.read((char*)this, sizeof(subject)))
    {
        cout << subject << endl;
    }
    cout<<"Enter a New Subject : ";
    cin.getline(subject,20);*/
    system("cls");
    cout<<"SUbject List will be displayed here\n"<<endl;
    system("pause");
}

void input(){
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
    while (fq.read((char*)this, sizeof(question)))
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
    while (fq.read((char*)this, sizeof(question)))
    {
        if (questionid == id)
        {
            cout << "\nQuestion Found!\n" << endl;
            output();
            cout << "Question deleted successfully!" << endl;
        }
        else
        {
        temp.write((char*)this, sizeof(question));
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
            while (fq.read((char*)this, sizeof(question)))
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
            while (fq.read((char*)this, sizeof(question))){
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

class Menu:public question{
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
                system("pause");
                break;
        }

    } while(choice != 5);
}

void studentlogin(){
    studentinfo s;
    s.input();
}

void displayfaculty(){
    system("cls");
    cout<<"Faculty Menu\n";
    cout<<"1. Display Question Bank \n";
    cout<<"2. Add Questions\n";
    cout<<"3. Delete Question\n";
    cout<<"4. Replace Question\n";
    cout<<"5. Exit\n";
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
    Menu m;
    m.mainmenu();
    return 0;
}