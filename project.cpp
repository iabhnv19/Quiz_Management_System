#include <iostream>
#include <fstream>
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
char question[100];

public:
void input(){
    cout<<"Enter The Question ID : "<<" ";
    cin>>questionid;
    cin.ignore();
    cout<<"Enter the Question :"<<" ";
    cin.getline(question,100);
}

void output(){
    cout<<"QuestionID :"<<questionid<<"\n"<<"Question :"<<question<<endl;
}

void questionsadd(){
    fstream fq;
    int choice;
    do {
        system("cls");
        input();
        fq.open("Questions.dat", ios::out | ios::app);
        fq.write((char*)this, sizeof(question));
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
            cout << "Question Found!" << endl;
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

void replacedata(){
    system("cls");
    cout<<"Enter Question ID to Replace :\n";
}
};

class Menu:public question{
private:
int choice;

void facultylogin(){
    faculty f;
    int choice;
    f.input();
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

/*void questionsadd(){
    question q;
    fstream fq;
    int choice;
    do {
        system("cls");
        q.input();
        fq.open("Questions.dat", ios::out | ios::app);
        fq.write((char*)&q, sizeof(q));
        fq.close();
        cout << "\nYou Added the Following Question:\n";
        q.output();
        cout << "\nDo you want to add a new question?\n";
        cout << "1. Yes\n";
        cout << "2. No\n";
        cout << "Enter your choice: ";
        cin >> choice;
    } while(choice == 1);
}

void displayallquestions(){
    faculty f;
    question q;
    fstream fq;
    fq.open("Questions.dat", ios::in);
    while (fq.read((char*)&q, sizeof(q)))
    {
        q.output();
    }
    fq.close();
}

void delrecord(){
    system("cls");
    cout<<"\nEnter Question ID to Delete :\n";
}

void replacedata(){
    system("cls");
     cout<<"\nEnter Question ID to Replace :\n";
}*/

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