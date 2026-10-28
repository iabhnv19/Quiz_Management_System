#include <iostream>
#include <fstream>
#include <exception>
#include <string.h>
#include <ctime>
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
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        throw "Roll number must be a valid integer!";
    }
    cin.ignore(10000, '\n');
    if (rollnumber <= 0)
        throw "Roll number must be greater than zero!";
    cout<<"Enter the Name : ";
    cin.getline(name,20);
}

int getid(){ return rollnumber; }
char* getname(){ return name; }
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
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        throw "Faculty ID must be a valid integer!";
    }
    else if (facultyid <= 0)
        throw "Faculty ID must be greater than zero!";
    cin.ignore();
    cout<<"Enter the Name :";
    cin.getline(name,20);
}
};
class question{
protected:
int questionid;
char subject[20];
char ques[100];
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
        while (fq.read((char*)this, sizeof(*this))){
            if (subject[0] == '\0'){
                continue;
            }
            bool alrexists = false;
            for (int i = 0; i < subjectCount; i++){
                if (strcmp(subjects[i], subject) == 0){
                    alrexists = true;
                    break;
                }
            }
            if (!alrexists && subjectCount < 50){
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
        if (cin.fail()){
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "\nPlease enter a valid number!\n";
            }
        cin.ignore(10000, '\n');
        if (choice >= 1 && choice <= subjectCount){
            strcpy(subject, subjects[choice - 1]);
            cout << "\nSelected Subject: " << subject << endl;
            system("pause");
            break;
        }
        else if (choice == subjectCount + 1){
            cin.ignore();
            cout << "\nEnter New Subject : ";
            cin.getline(subject, 20);
            if (strlen(subject) == 0){
                cout << "\nSubject cannot be empty!\n";
                system("pause");
                continue;
            }
            cout << "\nNew Subject Added: " << subject << endl;
            system("pause");
            break;
        }
        else{
            cout << "\nInvalid choice!\n";
        }
            
    } while (true);
}

void input()
{
    cout << "Subject : " << subject << endl;
    questionid = autoqueiD();
    cout << "Question ID : " << questionid << endl;
    cout << "Enter the Question : ";
    cin.ignore();
    cin.getline(ques, 100);
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        throw "Question is too long!";
    }
    cout << "\nEnter the Options\n";
    cout << "Option A : ";
    cin.getline(optionA, 50);
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        throw "Option A is too long!";
    }
    cout << "Option B : ";
    cin.getline(optionB, 50);
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        throw "Option B is too long!";
    }
    cout << "Option C : ";
    cin.getline(optionC, 50);
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        throw "Option C is too long!";
    }   
    cout << "Option D : ";
    cin.getline(optionD, 50);
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        throw "Option D is too long!";
    }
    cout << "\nEnter the Correct Option (1 to 4): ";
    cin >> correctoption;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        throw "Correct option must be a number!";
    }
    cin.ignore(10000, '\n');
    if (correctoption < 1 || correctoption > 4)
        throw "Correct option must be between 1 and 4!";
}

int autoqueiD()
{
    fstream fq;
    question q;
    int lastID = 0;
    fq.open("Questions.dat", ios::in);
    if (fq)
    {
        while (fq.read((char*)&q, sizeof(q))){
            if (strcmp(q.subject, subject) == 0){
                if (q.questionid > lastID)
                {
                    lastID = q.questionid;
                }
            }
        }
        fq.close();
    }
    return lastID + 1;
}


void output(){
    cout << "Subject : " << subject << endl;
    cout<<"QuestionID :"<<questionid<<"\n"<<"Question :"<<"\n"<<ques<<endl;
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
        try {
            input();
            fq.open("Questions.dat", ios::out | ios::app | ios::binary);
            if (!fq)
                throw "Could not open file for writing!";
            fq.write((char*)this, sizeof(*this));
            if (!fq)
                throw "Failed to write the question";
            fq.close();
            cout << "\nYou Added the Following Question:\n";
            output();
        }
        catch (const char* msg) {
            if (fq.is_open())
                fq.close();
            cout << "\nError : " << msg << endl;
            cout << "The question was not saved.\n";
        }
        cout << "\nDo you want to add a new question?\n";
        cout << "1. Yes\n";
        cout << "2. No\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            choice = 2;
        }
        cin.ignore(10000, '\n');
    } while(choice == 1);
}

void displayallquestions(){
    fstream fq;
    system("cls");
    cout << "Displaying Question Bank\n";
    fq.open("Questions.dat", ios::in);
    if (!fq)
        throw "Question bank is empty";
    while (fq.read((char*)this, sizeof(*this)))
    {
        output();
        cout<<endl;
    }
    fq.close();
}

void delrecord(){
    int id;
    bool found = false;
    system("cls");
    cout<<"Enter Question ID to Delete :\n";
    cin>>id;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        throw "Question ID must be a number!";
    }
    cin.ignore(10000, '\n');
    fstream fq, temp;
    fq.open("Questions.dat", ios::in | ios::binary);
    if (!fq)
        throw "Could not open the file";
    temp.open("temp.dat", ios::out | ios::binary);
    if (!temp){
        fq.close();
        throw "Could not create the temporary file!";
    }
    while (fq.read((char*)this, sizeof(*this))){
        if (questionid == id){
            found = true;
            cout << "\nQuestion Found!\n" << endl;
            output();
        }
        else{
            temp.write((char*)this, sizeof(*this));
        }
    }
    fq.close();
    temp.close();
    if (!found){
        throw "Question ID not found";
    }
    cout << "Question deleted successfully!" << endl;
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
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        throw "Please enter a valid number!";
    }
    cin.ignore(10000, '\n');
    switch(choice){
        case 1:
            cout<<"\nEnter Question ID to Find :\n";
            cin>>id;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                throw "Question ID must be a number!";
            }
            fq.open("Questions.dat", ios::in);
            if (!fq)
                throw "Could not open the file";
            while (fq.read((char*)this, sizeof(*this))){
                if (questionid == id){
                    cout << "\nQuestion Found!\n" << endl;
                    output();
                }
                else{
                    cout << "\nNo Question Found" << endl;
                }
            }
            fq.close();
            break;
        case 2:
            cin.ignore();
            cout<<"\nEnter Question to Find :\n";
            cin.getline(findquestion, 100);
            fq.open("Questions.dat", ios::in);
            if (!fq)
                throw "Could not open the file";
            while (fq.read((char*)this, sizeof(*this))){
                bool found = false;
                for (int i = 0; ques[i] != '\0'; i++){
                    int j = 0;
                    while (findquestion[j] != '\0' && ques[i + j] == findquestion[j]){
                        j++;
                    }
                    if (findquestion[j] == '\0'){
                        found = true;
                        break;
                    }
                }
                if (found){
                    cout << "\nQuestion Found!\n" << endl;
                    output();
                }
                else{
                    cout << "\nNo Question Found" << endl;
                }
            }
            fq.close();
            break;
        default:
            throw "Invalid choice!";
    }
}

void replacedata(){
    system("cls");
    int id;
    int pos;
    bool found = false;
    cout << "Enter Question ID to update : ";
    cin >> id;
    fstream fq;
    fq.open("Questions.dat", ios::in | ios::out | ios::binary);
    if (!fq){
        cout << "No questions found.\n";
        return;
    }
    while (true){
        pos = fq.tellg();
        if (!fq.read((char *)this, sizeof(*this)))
            break;
        if (questionid == id){
            found = true;
            cout << "\nExisting question:\n";
            output();
            cin.ignore();
            cout << "Enter updated question text : ";
            cin.getline(ques, 100);
            cout << "Enter updated Option A : ";
            cin.getline(optionA, 50);
            cout << "Enter updated Option B : ";
            cin.getline(optionB, 50);
            cout << "Enter updated Option C : ";
            cin.getline(optionC, 50);
            cout << "Enter updated Option D : ";
            cin.getline(optionD, 50);
            do{
                cout << "Enter correct option (1 to 4) : ";
                cin >> correctoption;
                if (correctoption < 1 || correctoption > 4)
                    cout << "Enter a number from 1 to 4.\n";
            } while (correctoption < 1 || correctoption > 4);
            fq.seekp(pos);
            fq.write((char *)this, sizeof(*this));
            cout << "Question updated successfully.\n";
            break;
        }
    }
    fq.close();
    if (!found)
        cout << "Question ID not found.\n";
    }
};

class exam:public question{
public:
bool selectsub(){
    fstream fq;
    char subjects[50][20];
    int count = 0;
    int choice;

    fq.open("Questions.dat", ios::in);
    if(fq){
        while(fq.read((char*)this, sizeof(question))){
            bool exists = false;
            for(int i = 0; i < count; i++){
                if(strcmp(subjects[i], subject) == 0){
                    exists = true;
                    break;
                }
            }
            if(!exists && count < 50){
                strcpy(subjects[count], subject);
                count++;
            }
        }
        fq.close();
    }

    if(count == 0){
        cout << "No subjects available yet.\n";
        return false;
    }

    do{
        system("cls");
        cout << "SELECT SUBJECT\n";
        for(int i = 0; i < count; i++){
            cout << i + 1 << ". " << subjects[i] << endl;
        }
        cout << "0. Back\n";
        cout << "\nEnter your choice : ";
        try{
            cin >> choice;
            if(cin.fail()){
                cin.clear();
                cin.ignore(10000, '\n');
                throw "Please enter a valid number!";
            }
            cin.ignore(10000, '\n');
            if(choice < 0 || choice > count)
                throw "Invalid choice!";
        }
        catch(const char* msg){
            cout << "\nError : " << msg << endl;
            system("pause");
            choice = -1;
        }
    }while(choice < 0 || choice > count);

    if(choice == 0){
        return false;
    }
    strcpy(subject, subjects[choice - 1]);
    cout << "\nSelected Subject : " << subject << endl;
    system("pause");
    return true;
}

void rules(){
    system("cls");
    cout << "Rules of Exam :\n";
    cout << "1. Each Question carries 1 mark.\n";
    cout << "2. No Negative Marking.\n";
    cout << "3. Answer with a number from 1 to 4.\n";
    system("pause");
}

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

bool takeexam(int &score, int &total, int universityRoll) {
    fstream fq;
    long positions[500];
    int count = 0;
    int ans;
    score = 0;
    total = 0;
    char chosen[20];
    strcpy(chosen, subject);
    fq.open("Questions.dat", ios::in | ios::binary);
    if (!fq) {
        throw("Could not open the file!");
    }
    while (true) {
        long pos = fq.tellg();
        if (!fq.read((char*)this, sizeof(question)))
            break;
        if (strcmp(subject, chosen) == 0) {
            if (count >= 500) {
                fq.close();
                throw("Question limit exceeded!");
            }
            positions[count++] = pos;
        }
    }
    fq.close();
    total = count;
    if (total == 0) {
        throw("No questions available!");
    }
    int number = universityRoll;
    while (number >= 10) {
        int sum = 0;
        while (number > 0) {
            sum += number % 10;
            number /= 10;
        }
        number = sum;
    }
    int seed = number;
    if (seed == 0)
        seed = 1;
    int gap = seed;
    if (total > 1) {
        gap %= total;
        if (gap == 0)
            gap = 1;
        while (gcd(gap, total) != 1) {
            gap++;
            if (gap >= total)
                gap = 1;
        }
    }
    int current = seed % total;
    fq.open("Questions.dat", ios::in | ios::binary);
    if (!fq) {
        throw("Could not open the file!");
    }
    for (int i = 0; i < total; i++) {
        fq.clear();
        fq.seekg(positions[current]);
        if (!fq.read((char*)this, sizeof(question))) {
            fq.close();
            throw("Unable to read question!");
        }
        system("cls");
        cout << "Subject : " << chosen << "\n";
        cout << ques << "\n";
        cout << "1. " << optionA << endl;
        cout << "2. " << optionB << endl;
        cout << "3. " << optionC << endl;
        cout << "4. " << optionD << endl;
        do {
            cout << "\nYour answer (1-4): ";
            try {
                cin >> ans;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    throw "Please enter a number!";
                }
                cin.ignore(10000, '\n');
                if (ans < 1 || ans > 4)
                    throw "Enter a number from 1 to 4!";
            }
            catch (const char* msg) {
                cout << "Invalid answer! " << msg << endl;
                ans = 0;
            }
        } while (ans < 1 || ans > 4);
        if (ans == correctoption)
            score++;
        current = (current + gap) % total;
    }
    fq.close();
    return true;
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
    int resultid;
    
public:
void calculate(){
    if (totalmarks <= 0)
        throw "Total marks must be greater than zero!";
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
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        throw "Student ID must be a number!";
    }
    cin.ignore(10000, '\n');
    if (studentid <= 0)
        throw "Student ID must be greater than zero!";
    cout << "Enter Student Name : ";
    cin.getline(studentname, 50);
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        throw "Student name is too long!";
    }
    if (strlen(studentname) == 0)
        throw "Student name cannot be empty!";
    cout << "Enter Exam Date : ";
    cin.getline(examdate, 15);
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        throw "Exam date is too long!";
    }
    if (strlen(examdate) == 0)
        throw "Exam date cannot be empty!";
    cout << "Enter Total Marks : ";
    cin >> totalmarks;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        throw "Total marks must be a number!";
    }
    cin.ignore(10000, '\n');
    if (totalmarks <= 0)
        throw "Total marks must be greater than zero!";
    cout << "Enter Marks Obtained : ";
    cin >> marksobtained;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        throw "Marks obtained must be a number!";
    }
    cin.ignore(10000, '\n');
    if (marksobtained < 0 || marksobtained > totalmarks)
        throw "Marks obtained must be between 0 and total marks!";
    calculate();
    autoresultid();
}

void autoresultid(){
    resultid = (studentid % 1000) * 1000000 + marksobtained * 1000 + totalmarks;
}

void output(){
    system("cls");
    cout << "Result: ";
    cout << "\n\nResult ID : " << resultid;
    cout << "\nStudent ID : " << studentid;
    cout << "\nStudent Name : " << studentname;
    cout << "\nTotal Marks : " << totalmarks;
    cout << "\nMarks Obtained : " <<marksobtained;
    cout << "\nPercentage : " << percentage;
    cout << "\nGrade : " << grade << endl;
}

void saveresult(int sid, char* nm, int total, int obtained){
    studentid = sid;
    strcpy(studentname, nm);
    totalmarks = total;
    marksobtained = obtained;
    calculate();
    autoresultid();
    output();
    save();
}

void save(){
    fstream fr;
    fr.open("results.dat", ios::out | ios::app);
    if (!fr)
        throw "Could not open file";
    fr.write((char*)this, sizeof(*this));
    if (!fr)
        throw "Failed to write to file!";
    fr.close();
    cout << "\nResult saved successfully!" << endl;
}

void displayall(){
    fstream fr;
    fr.open("results.dat", ios::in);
    if (!fr){
        cout << "No results found." << endl;
        return;
    }
    while (fr.read((char*)this, sizeof(*this))){
        output();
        cout << endl;
    }
    fr.close();
}

void showstudent(int id){
    fstream fr;
    bool found = false;
    fr.open("results.dat", ios::in);
    if (!fr){
        cout << "No results found." << endl;
        return;
    }
    while (fr.read((char*)this, sizeof(*this))){
        if (studentid == id){
            output();
            found = true;
        }
    }
    if (!found){
        cout << "No result found for this student." << endl;
    }
    fr.close();
}

void toppers(){
    fstream fr;
    int max = 0;
    bool found = false;
    fr.open("results.dat", ios::in);
    if (!fr){
        cout << "No results found." << endl;
        return;
    }
    while (fr.read((char*)this, sizeof(*this))){
        if (marksobtained > max){
            max = marksobtained;
        }
    }
    fr.clear();
    fr.seekg(0);
    cout << "\nTopper Result(s):\n";
    while (fr.read((char*)this, sizeof(*this))){
        if (marksobtained == max){
            output();
            found = true;
        }
    }
    if (!found){
        cout << "No results found." << endl;
    }
    fr.close();
}

void deleteresult(){
    int id;
    bool found = false;
    cout << "Enter Result ID to Delete : ";
    cin >> id;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        throw "Result ID must be a number!";
    }
    cin.ignore(10000, '\n');
    fstream fr, temp;
    fr.open("results.dat", ios::in);
    if (!fr){
        cout << "No results found." << endl;
        return;
    }
    temp.open("temp.dat", ios::out);
    if (!temp){
        cout << "Temporary file could not be created." << endl;
        fr.close();
        return;
    }
    while (fr.read((char*)this, sizeof(*this))){
        if (resultid == id){
            found = true;
        }
        else{
            temp.write((char*)this, sizeof(*this));
        }
    }
    fr.close();
    temp.close();
    if (found){
        remove("results.dat");
        rename("temp.dat", "results.dat");
        cout << "Result deleted successfully!" << endl;
    }
    else{
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
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        throw "Result ID must be a number!";
    }
    cin.ignore(10000, '\n');
    fstream fr;
    fr.open("results.dat", ios::in | ios::out);
    if (!fr){
        cout << "No results found." << endl;
        return;
    }
    while (true){
        pos = fr.tellg();
        if (!fr.read((char*)this, sizeof(*this)))
            break;
        if (resultid == id){
            cout << "Current Marks : " << marksobtained << endl;
            cout << "Total Marks : " << totalmarks << endl;
            cout << "Enter New Marks : ";
            cin >> newmarks;
            if (newmarks < 0 || newmarks > totalmarks){
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

        switch(choice){
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

            case 3:{
                int id;
                cout << "Enter Student ID : ";
                cin >> id;
                if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        throw "Student ID must be a number!";
                    }
                    cin.ignore(10000, '\n');
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
            default:
                throw "Invalid choice";
        }
    } while(choice != 7);
}

void resultmenustudent(){
    int choice;
    do{
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
                if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        throw "Student ID must be a number!";
                    }
                    cin.ignore(10000, '\n');
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
            default:
                    throw "Invalid choice";
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
    try {
        f.input();
    }
    catch (const char* msg) {
        cout << "\nError : " << msg << endl;
        system("pause");
        return;
    }
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
                subjectlist();
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
            default:
                throw "Invalid choice";
        }
    } while(choice != 6);
}

void studentlogin(){
    int choice;
    studentinfo s;
    exam e;
    try {
        s.input();
    }
    catch (const char* msg) {
        cout << "\nError : " << msg << endl;
        system("pause");
        return;
    }
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
            case 1:{
            if(e.selectsub()){
                e.rules();
                int score, total;
                time_t startTime = time(0);
                if(e.takeexam(score, total, s.getid())){
                    time_t finishTime = time(0);
                    double timeTaken = difftime(finishTime, startTime);
                    system("cls");
                    cout << "Exam finished!\n";
                    saveresult(s.getid(), s.getname(),score, total);
                    int minutes = (int)timeTaken / 60;
                    int seconds = (int)timeTaken % 60;
                    cout << "Time Taken    : " << minutes << " minutes and " << seconds << " seconds\n";
                }
                else{
                    cout << "\nNo questions available for this subject yet.\n";
                }
            }
                system("pause");
                break;
            }
            case 2:
                resultmenustudent();
                system("pause");
                break;
            case 3:
                cout << "Exiting..." << endl;
                system("pause");
                break;
            default:
                throw "Invalid choice";
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
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        throw "Please enter a valid number!";
    }
    cin.ignore(10000, '\n');
}

public:
void mainmenu(){
    choice = 0;
    do{
        system("cls");
        try {
            display();
            switch(choice){
                case 1:
                    facultylogin();
                    break;
                case 2:
                    studentlogin();
                    break;
                default:
                    throw "Invalid choice!";
            }
        }
        catch (const char* msg) {
            cout << "\nError : " << msg << endl;
            choice = 0;
            system("pause");
        }
    }while(choice != 2);
}
};

int main(){
    try {
        menu m;
        m.mainmenu();
    }
    catch (const char* msg) {
        cout << "Error : " << msg << endl;
        return 1;
    }
    catch (exception& ex) {
        cout << "Unexpected error : " << ex.what() << endl;
        return 1;
    }
    catch (...) {
        cout << "Something went wrong and the program had to stop." << endl;
        return 1;
    }
    return 0;
}