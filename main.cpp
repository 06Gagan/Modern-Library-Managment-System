#include <iostream>
#include <iomanip> // for input-output manipulations
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <fstream>

// Gagandeep's Library Management System

class Book {
    char bno[6]; // Book number
    char bname[50]; // Book name
    char aname[20]; // Author name
public:
    void createBook() {
        std::cout << "\nNEW BOOK ENTRY...\n";
        std::cout << "\nENTER BOOK NO.: ";
        std::cin >> bno;
        std::cin.ignore();
        std::cout << "\nENTER BOOK NAME: ";
        std::cin.getline(bname, 50);
        std::cout << "\nENTER AUTHOR NAME: ";
        std::cin.getline(aname, 20);
        std::cout << "\n\n\nBook Created..";
    }

    void showBook() {
        std::cout << "\nBook Number: " << bno;
        std::cout << "\nBook Name: " << bname;
        std::cout << "\nBook Author Name: " << aname;
    }

    void modifyBook() {
        std::cout << "\nBook Number: " << bno;
        std::cout << "\nModify Book Name: ";
        std::cin.ignore();
        std::cin.getline(bname, 50);
        std::cout << "\nModify Author's Name: ";
        std::cin.getline(aname, 20);
    }

    char* retBno() {
        return bno;
    }

    void report() {
        std::cout << bno << std::setw(30) << bname << std::setw(30) << aname << std::endl;
    }
};

class Student {
    char admno[6]; // Admission number
    char name[20];
    char stbno[6]; // Student book number
    int token; // Total books of student
public:
    void createStudent() {
        std::cout << "\nNEW STUDENT ENTRY...\n";
        std::cout << "\nEnter The Admission No.: ";
        std::cin >> admno;
        std::cin.ignore();
        std::cout << "Enter The Student Name: ";
        std::cin.getline(name, 20);
        token = 0;
        stbno[0] = '\0';
        std::cout << "\n\nStudent Record Created...";
    }

    void showStudent() {
        std::cout << "\nAdmission Number: " << admno;
        std::cout << "\nStudent Name: " << name;
        std::cout << "\nNo of Book Issued: " << token;
        if (token == 1) {
            std::cout << "\nBook Number: " << stbno;
        }
    }

    void modifyStudent() {
        std::cout << "\nAdmission No.: " << admno;
        std::cout << "\nModify Student Name: ";
        std::cin.ignore();
        std::cin.getline(name, 20);
    }

    char* retAdmno() {
        return admno;
    }

    char* retStbno() {
        return stbno;
    }

    int retToken() {
        return token;
    }

    void addToken() {
        token = 1;
    }

    void resetToken() {
        token = 0;
    }

    void getStbno(char t[]) {
        strcpy(stbno, t);
    }

    void report() {
        std::cout << "\t" << admno << std::setw(20) << name << std::setw(10) << token << std::endl;
    }
};

// Global file stream objects
std::fstream fp, fp1;
Book bk;
Student st;

void writeBook() {
    char ch;
    fp.open("book.dat", std::ios::out | std::ios::app);
    do {
        bk.createBook();
        fp.write(reinterpret_cast<char*>(&bk), sizeof(Book));
        std::cout << "\n\nDo you want to add more records...(y/n?) ";
        std::cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}

void writeStudent() {
    char ch;
    fp.open("student.dat", std::ios::out | std::ios::app);
    do {
        st.createStudent();
        fp.write(reinterpret_cast<char*>(&st), sizeof(Student));
        std::cout << "\n\nDo you want to add more records...(y/n?) ";
        std::cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}

void displaySpb(char n[]) {
    std::cout << "\nBOOK DETAILS\n";
    int flag = 0;
    fp.open("book.dat", std::ios::in);
    while (fp.read(reinterpret_cast<char*>(&bk), sizeof(Book))) {
        if (strcasecmp(bk.retBno(), n) == 0) {
            bk.showBook();
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0) {
        std::cout << "\n\nBook does not exist";
    }
    std::cin.get();
}

void displaySps(char n[]) {
    std::cout << "\nSTUDENT DETAILS\n";
    int flag = 0;
    fp.open("student.dat", std::ios::in);
    while (fp.read(reinterpret_cast<char*>(&st), sizeof(Student))) {
        if (strcasecmp(st.retAdmno(), n) == 0) {
            st.showStudent();
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0) {
        std::cout << "\n\nStudent does not exist";
    }
    std::cin.get();
}

void modifyBook() {
    char n[6];
    int found = 0;
    std::cout << "\n\nMODIFY BOOK RECORD...";
    std::cout << "\n\nEnter the book no.: ";
    std::cin >> n;
    fp.open("book.dat", std::ios::in | std::ios::out);
    while (fp.read(reinterpret_cast<char*>(&bk), sizeof(Book)) && found == 0) {
        if (strcasecmp(bk.retBno(), n) == 0) {
            bk.showBook();
            std::cout << "\nEnter the new details of the book";
            bk.modifyBook();
            int pos = -1 * static_cast<int>(sizeof(bk));
            fp.seekp(pos, std::ios::cur);
            fp.write(reinterpret_cast<char*>(&bk), sizeof(Book));
            std::cout << "\n\nRecord Updated";
            found = 1;
        }
    }
    fp.close();
    if (found == 0) {
        std::cout << "\n\nRecord Not Found";
    }
    std::cin.get();
}

void modifyStudent() {
    char n[6];
    int found = 0;
    std::cout << "\n\nMODIFY STUDENT RECORD...";
    std::cout << "\n\nEnter the Admission no.: ";
    std::cin >> n;
    fp.open("student.dat", std::ios::in | std::ios::out);
    while (fp.read(reinterpret_cast<char*>(&st), sizeof(Student)) && found == 0) {
        if (strcasecmp(st.retAdmno(), n) == 0) {
            st.showStudent();
            std::cout << "\nEnter the new details of the student";
            st.modifyStudent();
            int pos = -1 * static_cast<int>(sizeof(st));
            fp.seekp(pos, std::ios::cur);
            fp.write(reinterpret_cast<char*>(&st), sizeof(Student));
            std::cout << "\n\nRecord Updated";
            found = 1;
        }
    }
    fp.close();
    if (found == 0) {
        std::cout << "\n\nRecord Not Found";
    }
    std::cin.get();
}

void deleteStudent() {
    char n[6];
    int flag = 0;
    std::cout << "\n\n\n\tDELETE STUDENT...";
    std::cout << "\n\nEnter the Admission no.: ";
    std::cin >> n;
    fp.open("student.dat", std::ios::in | std::ios::out);
    std::fstream fp2;
    fp2.open("temp.dat", std::ios::out);
    fp.seekg(0, std::ios::beg);
    while (fp.read(reinterpret_cast<char*>(&st), sizeof(Student))) {
        if (strcasecmp(st.retAdmno(), n) != 0) {
            fp2.write(reinterpret_cast<char*>(&st), sizeof(Student));
        } else {
            flag = 1;
        }
    }
    fp2.close();
    fp.close();
    remove("student.dat");
    rename("temp.dat", "student.dat");
    if (flag == 1) {
        std::cout << "\n\n\tRecord Deleted..";
    } else {
        std::cout << "\n\nRecord not Found";
    }
    std::cin.get();
}

void deleteBook() {
    char n[6];
    int flag = 0;
    std::cout << "\n\n\n\tDELETE BOOK...";
    std::cout << "\n\nEnter the Book no.: ";
    std::cin >> n;
    fp.open("book.dat", std::ios::in | std::ios::out);
    std::fstream fp2;
    fp2.open("temp.dat", std::ios::out);
    fp.seekg(0, std::ios::beg);
    while (fp.read(reinterpret_cast<char*>(&bk), sizeof(Book))) {
        if (strcasecmp(bk.retBno(), n) != 0) {
            fp2.write(reinterpret_cast<char*>(&bk), sizeof(Book));
        } else {
            flag = 1;
        }
    }
    fp2.close();
    fp.close();
    remove("book.dat");
    rename("temp.dat", "book.dat");
    if (flag == 1) {
        std::cout << "\n\n\tRecord Deleted...";
    } else {
        std::cout << "\n\nRecord not Found";
    }
    std::cin.get();
}

void displayAllStudents() {
    fp.open("student.dat", std::ios::in);
    if (!fp) {
        std::cout << "File Could Not Be Opened";
        std::cin.get();
        return;
    }
    std::cout << "\n\n\t\tStudent List\n\n";
    std::cout << "==================================================================\n";
    std::cout << "\tAdmission No." << std::setw(10) << "Name" << std::setw(20) << "Book Issued\n";
    std::cout << "==================================================================\n";
    while (fp.read(reinterpret_cast<char*>(&st), sizeof(Student))) {
        st.report();
    }
    fp.close();
    std::cin.get();
}

void displayAllBooks() {
    fp.open("book.dat", std::ios::in);
    if (!fp) {
        std::cout << "File Could Not Be Opened";
        std::cin.get();
        return;
    }
    std::cout << "\n\n\t\tBook List\n\n";
    std::cout << "==================================================================\n";
    std::cout << "\tBook No." << std::setw(20) << "Book Name" << std::setw(25) << "Book Author\n";
    std::cout << "==================================================================\n";
    while (fp.read(reinterpret_cast<char*>(&bk), sizeof(Book))) {
        bk.report();
    }
    fp.close();
    std::cin.get();
}

void bookIssue() {
    char sn[6], bn[6];
    int found = 0, flag = 0;
    std::cout << "\n\nBOOK ISSUE...";
    std::cout << "\n\n\tEnter Admission no.: ";
    std::cin >> sn;
    fp.open("student.dat", std::ios::in | std::ios::out);
    fp1.open("book.dat", std::ios::in | std::ios::out);
    while (fp.read(reinterpret_cast<char*>(&st), sizeof(Student)) && found == 0) {
        if (strcasecmp(st.retAdmno(), sn) == 0) {
            found = 1;
            if (st.retToken() == 0) {
                std::cout << "\n\n\tEnter The Book No.: ";
                std::cin >> bn;
                while (fp1.read(reinterpret_cast<char*>(&bk), sizeof(Book)) && flag == 0) {
                    if (strcasecmp(bk.retBno(), bn) == 0) {
                        flag = 1;
                        st.addToken();
                        st.getStbno(bk.retBno());
                        int pos = -1 * static_cast<int>(sizeof(st));
                        fp.seekg(pos, std::ios::cur);
                        fp.write(reinterpret_cast<char*>(&st), sizeof(Student));
                        std::cout << "\n\n\tBook Issued Successfully\n\n Please Note The Book Issue Date On The Backside Of Your Book And Return Book Within 15 Days, Otherwise Fine Of 15 Rs Per Day";
                    }
                }
                if (flag == 0) {
                    std::cout << "Book No. Does Not Exist";
                }
            } else {
                std::cout << "You Have Not Returned The Last Book";
            }
        }
    }
    if (found == 0) {
        std::cout << "Student Record Does Not Exist...";
    }
    std::cin.get();
    fp.close();
    fp1.close();
}

void bookDeposit() {
    char sn[6];
    int found = 0, flag = 0, day, fine;
    std::cout << "\n\nBOOK DEPOSIT...";
    std::cout << "\n\n\tEnter Admission no. Of Student: ";
    std::cin >> sn;
    fp.open("student.dat", std::ios::in | std::ios::out);
    fp1.open("book.dat", std::ios::in | std::ios::out);
    while (fp.read(reinterpret_cast<char*>(&st), sizeof(Student)) && found == 0) {
        if (strcasecmp(st.retAdmno(), sn) == 0) {
            found = 1;
            if (st.retToken() == 1) {
                while (fp1.read(reinterpret_cast<char*>(&bk), sizeof(Book)) && flag == 0) {
                    if (strcasecmp(bk.retBno(), st.retStbno()) == 0) {
                        flag = 1;
                        bk.showBook();
                        std::cout << "\n\n Book Deposited In No. Of Days: ";
                        std::cin >> day;
                        if (day > 15) {
                            fine = (day - 15) * 1;
                            std::cout << "\n\n Fine = " << fine;
                        }
                        st.resetToken();
                        int pos = -1 * static_cast<int>(sizeof(st));
                        fp.seekg(pos, std::ios::cur);
                        fp.write(reinterpret_cast<char*>(&st), sizeof(Student));
                        std::cout << "\n\n\tBook Deposited Successfully";
                    }
                }
                if (flag == 0) {
                    std::cout << "Book No. Does Not Exist";
                }
            } else {
                std::cout << "No Book Issued";
            }
        }
    }
    if (found == 0) {
        std::cout << "Student Record Does Not Exist...";
    }
    std::cin.get();
    fp.close();
    fp1.close();
}

void start() {
    std::cout << "\n\n\n\tLIBRARY";
    std::cout << "\n\n\tMANAGEMENT";
    std::cout << "\n\n\tSYSTEM";
    std::cout << " \n  by: Gagandeep";
    std::cin.get();
}

void adminMenu() {
    int ch2;
    std::cout << "\n\n\n\tADMINISTRATOR MENU";
    std::cout << "\n\n\n\t1.CREATE STUDENT RECORD";
    std::cout << "\n\n\n\t2.DISPLAY ALL STUDENT RECORD";
    std::cout << "\n\n\n\t3.DISPLAY SPECIFIC STUDENT RECORD";
    std::cout << "\n\n\n\t4.MODIFY STUDENT RECORD";
    std::cout << "\n\n\n\t5.DELETE STUDENT RECORD";
    std::cout << "\n\n\n\t6.CREATE BOOK";
    std::cout << "\n\n\n\t7.DISPLAY ALL BOOKS";
    std::cout << "\n\n\n\t8.DISPLAY SPECIFIC BOOK";
    std::cout << "\n\n\n\t9.MODIFY BOOK RECORD";
    std::cout << "\n\n\n\t10.DELETE BOOK RECORD";
    std::cout << "\n\n\n\t11.BACK TO MAIN MENU";
    std::cout << "\n\n\n\tPLEASE ENTER YOUR CHOICE(1-11): ";
    std::cin >> ch2;
    switch (ch2) {
        case 1: writeStudent();
            break;
        case 2: displayAllStudents();
            break;
        case 3: {
            char num[6];
            std::cout << "\n\n\t Please enter admission no.: ";
            std::cin >> num;
            displaySps(num);
            break;
        }
        case 4: modifyStudent();
            break;
        case 5: deleteStudent();
            break;
        case 6: writeBook();
            break;
        case 7: displayAllBooks();
            break;
        case 8: {
            char num[6];
            std::cout << "\n\n\tPlease enter book no.: ";
            std::cin >> num;
            displaySpb(num);
            break;
        }
        case 9: modifyBook();
            break;
        case 10: deleteBook();
            break;
        case 11:
            return;
        default:
            std::cout << "Invalid choice";
    }
    adminMenu();
}

int main() {
    char ch;
    start();
    do {
        std::cout << "\n\n\n\t MAIN MENU";
        std::cout << "\n\n\n\t1 BOOK ISSUE";
        std::cout << "\n\n\n\t2 BOOK DEPOSIT";
        std::cout << "\n\n\n\t3 ADMINISTRATOR MENU";
        std::cout << "\n\n\n\t4 EXIT";
        std::cout << "\n\n\n\t PLEASE SELECT YOUR OPTION(1-4): ";
        std::cin >> ch;
        switch (ch) {
            case '1': bookIssue();
                break;
            case '2': bookDeposit();
                break;
            case '3': adminMenu();
                break;
            case '4': exit(0);
                break;
            default:
                std::cout << "INVALID CHOICE";
        }
    } while (ch != '4');

    return 0;
}
