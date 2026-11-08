<div align="center">

# Online Exam / Quiz Management System

### A C++ console-based examination and quiz management project.

Developed using **Object-Oriented Programming**, **file handling**, and **C++**. Manage subject-wise MCQ questions, conduct student examinations, automatically evaluate answers, and maintain examination results.

![Language](https://img.shields.io/badge/language-C%2B%2B-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![Platform](https://img.shields.io/badge/platform-Windows-0078D4?style=for-the-badge&logo=windows&logoColor=white)
![Interface](https://img.shields.io/badge/interface-Console-555555?style=for-the-badge)
![Storage](https://img.shields.io/badge/storage-File%20Handling-4A7C59?style=for-the-badge)
![License](https://img.shields.io/badge/license-MIT-green?style=for-the-badge)

</div>

---

## Overview

The **Online Exam / Quiz Management System** is a menu-driven C++ project developed to demonstrate the practical use of Object-Oriented Programming and file handling.

The application provides two main interfaces:

- **Faculty:** Manage the question bank and examination results.
- **Student:** Select a subject, attempt an MCQ examination, and view results.

Questions are organised subject-wise and stored locally. During an examination, the system checks each answer, calculates the student's score, and saves the result for later access.

> **Note:** Despite the academic project title, this version is a local, Windows console application. It does not use a server, internet connection, or online database.

---

## Features

| # | Feature | Description |
|:-:|---------|-------------|
| 1 | **Faculty Menu** | Provides access to question-bank and result-management operations. |
| 2 | **Subject Management** | Select an existing subject or add a new subject while creating questions. |
| 3 | **Question Bank** | Add, display, update, and delete MCQ questions. |
| 4 | **Multiple-Choice Questions** | Each question contains four options and one correct option. |
| 5 | **Student Menu** | Collects student ID/roll number and name before accessing the student menu. |
| 6 | **Subject Selection** | Students can choose from subjects available in the question bank. |
| 7 | **Automatic Evaluation** | Checks submitted answers and calculates marks automatically. |
| 8 | **Question Order Variation** | Uses the student's roll number to determine the question sequence. |
| 9 | **Result Management** | Save, display, search, update, and delete examination results. |
| 10 | **Topper Display** | Finds and displays result records with the highest marks obtained. |
| 11 | **Input Validation** | Handles several invalid inputs using validation and exception handling. |
| 12 | **Local File Storage** | Stores question and result records in local `.dat` files. |

### Examination rules

- Each question carries **1 mark**.
- There is **no negative marking**.
- Students select answers using options **1 to 4**.
- The program displays the time taken after the examination.
- Results are calculated and saved after an examination is completed.

---

## Quick Start

### Requirements

- Windows 10 or Windows 11
- GCC / MinGW-w64 compiler
- A terminal such as PowerShell, Command Prompt, or the VS Code terminal

No external libraries are required.

### Clone the repository

```bash
git clone https://github.com/iabhnv19/Quiz_Management_System.git
```

---
## FlowChart

<img width="4722" height="6311" alt="diagram" src="https://github.com/user-attachments/assets/12ec3dbb-3141-41a0-be32-1e845688dff2" />

---

## Usage

After launching the program, the main menu provides two options:

```text
Context Menu
1. Faculty Login
2. Student Login

Enter your choice:
```

### Faculty

The faculty menu provides the following operations:

```text
Faculty Menu
1. Display Question Bank
2. Add Questions
3. Delete Question
4. Replace Question
5. Result Menu
6. Exit
```

Faculty can:

- View all stored questions.
- Add questions under an existing or new subject.
- Delete a question using its question ID.
- Update question text, options, and the correct option.
- Open the result menu to manage examination records.

### Student

The student enters their ID/roll number and name before accessing:

```text
Student Menu
1. Start Exam
2. View Results
3. Exit
```

Students can:

- Select an available subject.
- Read the examination rules.
- Attempt the subject's MCQ questions.
- View saved examination results.

### Result management

The faculty result menu supports:

- Add a result manually.
- Display all results.
- Search results using student ID.
- Display topper result(s).
- Delete a result using its result ID.
- Update marks and recalculate the grade.

The student result menu supports displaying all results, searching by student ID, and viewing topper result(s).

---

## How the Examination Works

The examination process follows these steps:

1. The student enters their ID/roll number and name.
2. The student selects a subject from the available question bank.
3. The program loads the questions belonging to that subject.
4. The student's roll number is used to derive a question sequence.
5. The student answers each question by selecting an option from 1 to 4.
6. The program checks the selected options against the stored correct answers.
7. The score and total marks are calculated.
8. The result is saved in `results.dat`.
9. The program displays the time taken for the examination.

### Result calculation

The percentage is calculated using:

<div align="center">

**Percentage = (Marks Obtained / Total Marks) × 100**

</div>

The grade is assigned as follows:

| Percentage | Grade |
|:----------:|:-----:|
| 80% and above | A |
| 60% to below 80% | B |
| 40% to below 60% | C |
| Below 40% | F |

---

## OOP Concepts Used

This project demonstrates the following Object-Oriented Programming concepts:

| Concept | Implementation |
|---------|----------------|
| **Classes and Objects** | Classes such as `studentinfo`, `faculty`, `question`, `exam`, `examresult`, and `menu` organise the program. |
| **Encapsulation** | Data members are grouped with their related member functions using classes and access specifiers. |
| **Inheritance** | `exam` inherits from `question`, while `menu` uses multiple inheritance from `question` and `examresult`. |
| **Abstraction** | Operations such as `takeexam()`, `calculate()`, `save()`, and question-management functions hide their internal steps behind member functions. |
| **Constructors / Object Use** | Class objects are created and used to perform different program operations. |
| **Exception Handling** | `try`, `catch`, and `throw` handle invalid input and file-related errors. |

### Other C++ concepts

- Functions and member functions
- Arrays and character strings
- Loops and conditional statements
- `switch` statements
- Pointers and object memory
- File streams using `fstream`
- Binary file read/write operations
- Searching and updating records
- Time measurement using `<ctime>`

---

## File Handling

The application stores its records locally in files created in the program's working directory.

| File | Purpose |
|------|---------|
| `Questions.dat` | Stores the question bank, including subjects, questions, options, and correct answers. |
| `results.dat` | Stores examination result records. |
| `temp.dat` | Temporary file used during record deletion. |

These files are generated when the application performs the relevant operations. They are not required to compile the project.

**Important:** The program writes class-object data directly to files. This is a basic educational demonstration, not a portable database format. The generated records can depend on compiler, architecture, class layout, and file mode. Do not use these files as a long-term or cross-platform data format.

---

## Limitations

- The application is a local console program, not a networked online examination platform.
- Faculty ID and name are collected, but there is no actual credential verification.
- Student details are entered for a session; there is no secure student-account system.
- Data is stored in local files rather than a database.
- Raw object storage is not suitable for portable or long-term records.
- The console commands `cls` and `pause` make the current implementation Windows-specific.
- The application is intended for academic learning and demonstration, not production use.

---

## Troubleshooting

<details>
<summary><b><code>g++</code> is not recognized</b></summary>

G++ is either not installed or its `bin` directory is not available in your PATH.

- Install GCC / MinGW-w64.
- Add the compiler's `bin` directory to your PATH.
- Open a new terminal and check:

```powershell
g++ --version
```

</details>

<details>
<summary><b>Compilation fails</b></summary>

- Make sure you are in the repository's root directory.
- Check that `src/project.cpp` exists.
- Verify that GCC / MinGW-w64 is installed correctly.
- Compile using the command shown in [Compilation](#-compilation).

</details>

<details>
<summary><b>The program cannot find or open a data file</b></summary>

The application creates its data files at runtime. Run the executable from a directory where it has permission to create and modify files.

</details>

<details>
<summary><b>The program does not work correctly in Linux or macOS</b></summary>

This version uses Windows-specific console commands such as `system("cls")` and `system("pause")`. Those calls need platform-specific replacements before using the application on other operating systems.

</details>

---

## FAQ

**Does this project require an internet connection?**

No. The current application works locally and stores records in files on the computer.

**Does it use a database?**

No. It uses local `.dat` files through C++ file handling.

**Can faculty add new subjects?**

Yes. A new subject can be entered while adding a question.

**How are marks calculated?**

Every correct answer adds one mark. There is no negative marking.

**Can students view their results?**

Yes. The student result menu provides options to display all results, search by student ID, and view topper result(s).

**Is this a fully online examination system?**

No. The project title describes the examination-system concept, but this implementation is a local Windows console application.

---

## Future Improvements

- Add secure faculty and student authentication.
- Move record storage to a database such as SQLite.
- Replace raw object storage with a structured, portable format.
- Add configurable exam duration and question limits.
- Improve input validation and error handling.
- Make console handling cross-platform.
- Add a graphical user interface.
- Add automated tests and sample screenshots.

---

## Contributors

This project was collaboratively developed by:

<div align="center">

<table>
  <tr>
    <td align="center">
      <a href="https://github.com/iabhnv19">
        <img src="https://github.com/iabhnv19.png" width="80" height="80" alt="Abhinav's GitHub profile picture" />
        <br />
        <strong>Abhinav</strong>
        <br />
        @iabhnv19
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/div62">
        <img src="https://github.com/div62.png" width="80" height="80" alt="Divyansha's GitHub profile picture" />
        <br />
        <strong>Divyansha Sharma</strong>
        <br />
        @div62
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/eshmeetk">
        <img src="https://github.com/eshmeetk.png" width="80" height="80" alt="Eshmeet's GitHub profile picture" />
        <br />
        <strong>Eshmeet Kaur</strong>
        <br />
        @eshmeetk
      </a>
    </td>
  </tr>
</table>

</div>

## License & Author

Released under the [MIT License](LICENSE).

<div align="center">

**Developed by the Online Exam / Quiz Management System team**

*Built as a C++ Object-Oriented Programming academic project.*

</div>
