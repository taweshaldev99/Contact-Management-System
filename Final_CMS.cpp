#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

using namespace std;

class Details {
private:
    char FName[50];
    char LName[50];
    char Address[50];
    char email[50];
    long long phone_No;

public:
    void getdata() {
        cout << "\t\t*** Enter First Name: ";
        fflush(stdin);
        cin.get(FName, 50);

        cout << "\t\t*** Enter Last Name: ";
        cin.get(LName, 50);
        fflush(stdin);

        cout << "\t\t*** Enter Address: ";
        cin.get(Address, 50);
        fflush(stdin);

        cout << "\t\t*** Enter Email: ";
        cin.get(email, 50);
        fflush(stdin);

        cout << "\t\t*** Enter Phone Number: ";
        cin >> phone_No;
        fflush(stdin);
    }

    void showcontact() {
        cout << "\t\t*** Name     : " << FName << " " << LName << endl;
        cout << "\t\t*** Address  : " << Address << endl;
        cout << "\t\t*** Email    : " << email << endl;
        cout << "\t\t*** Phone_No : " << phone_No;
    }

    void writeonfile() {
        ofstream F1;
        F1.open("CMS.dat", ios::binary | ios::app);
        if (!F1.is_open()) {
            cout << "\t\tError opening file!" << endl;
            return;
        }

        F1.write(reinterpret_cast<char*>(this), sizeof(*this));
        cout << "\t\t*** Contact Successfully Created!!!\n";
        F1.close();
    }

    void readfromfile() {
        ifstream F2("CMS.dat", ios::binary);
        if (!F2.is_open()) {
            cout << "\t\tError opening file!" << endl;
            return;
        }

        cout << "\t\t===========================" << endl;
        cout << "\t\t LIST OF CONTACTS!!!!" << endl;
        cout << "\t\t===========================" << endl;

        while (F2.read(reinterpret_cast<char*>(this), sizeof(*this))) {
            showcontact();
            cout << "\n========================================\n";
        }

        F2.close();
    }

    void searchfromfile() {
        long long phone;
        cout << "\t\t*** Enter Phone Number You Want To Search: ";
        cin >> phone;

        ifstream F3("CMS.dat", ios::binary);
        if (!F3.is_open()) {
            cout << "\t\tError opening file!" << endl;
            return;
        }

        bool found = false;
        while (F3.read(reinterpret_cast<char*>(this), sizeof(*this))) {
            if (phone_No == phone) {
                showcontact();
                found = true;
                break;
            }
        }

        if (!found)
            cout << "\t\t*** Number Not Found!!!" << endl;

        F3.close();
    }

    void deletefromfile() {
        long long phone;
        cout << "\t\tEnter Phone Number To delete Contact: ";
        cin >> phone;

        ifstream F4("CMS.dat", ios::binary);
        ofstream F5("temp.dat", ios::binary);

        if (!F4.is_open() || !F5.is_open()) {
            cout << "\t\tError opening file!" << endl;
            return;
        }

        bool deleted = false;
        while (F4.read(reinterpret_cast<char*>(this), sizeof(*this))) {
            if (phone_No != phone) {
                F5.write(reinterpret_cast<char*>(this), sizeof(*this));
            } else {
                deleted = true;
            }
        }

        F4.close();
        F5.close();

        remove("CMS.dat");
        rename("temp.dat", "CMS.dat");

        if (deleted)
            cout << "\t\tContact Deleted" << endl;
        else
            cout << "\t\tContact Not Found" << endl;
    }
};

class LoginManager {
public:
    bool authenticate() {
        string username, password;
        cout << "\n\n\t\t\t\t\t\t Username : ";
        cin >> username;
        cout << "\n\n\t\t\t\t\t\t Password : ";
        cin >> password;

        ifstream login_file("Login_Data.dat");
        if (!login_file.is_open()) {
            cout << "\t\tError opening file!" << endl;
            return false;
        }

        string file_user, file_pass;
        while (login_file >> file_user >> file_pass) {
            if (file_user == username && file_pass == password) {
                cout << "\n\n\t\t\t\t\t\t Login successful.\n";
                login_file.close();
                return true;
            }
        }
        cout << "\n\n\t\t\t\t\t\t Invalid username or password.\n";
        login_file.close();
        return false;
    }

    void signup() {
        ofstream signup_data;
        string username, password;
        cout << "\n\n\t\t\t\t\t\t Enter new Username : ";
        cin >> username;
        cout << "\n\n\t\t\t\t\t\t Enter new Password : ";
        cin >> password;

        signup_data.open("Login_Data.dat", ios::out | ios::app);
        if (!signup_data.is_open()) {
            cout << "\n\n\t\t\t\t\t\t Error: Unable to create an account." << endl;
            return;
        }
        signup_data << username << ' ' << password << endl;
        cout << "\n\n\t\t\t\t\t\t Signup successfully." << endl;
        signup_data.close();
    }
};

int loginMenu() {
    int choice;
    cout << "\n\n\t\t\t\t\t\t 1. Login";
    cout << "\n\n\t\t\t\t\t\t 2. Signup";
    cout << "\n\n\t\t\t\t\t\t 3. Exit";
    cout << "\n\n\t\t\t\t\t\t Enter your choice : ";
    cin >> choice;
    return choice;
}

int main() {
    int loginChoice;
    LoginManager loginManager;
    while (true) {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t************************************************\n";
        cout << "\t\t\t\t\t\t\t=================================================\n";
        cout << "\t\t\t\t\t\t\t||                                                  ||\n";
        cout << "\t\t\t\t\t\t\t||         ---------------------------------        ||\n";
        cout << "\t\t\t\t\t\t\t||        **Contact Management System**             ||\n";
        cout << "\t\t\t\t\t\t\t||         ---------------------------------        ||\n";
        cout << "\t\t\t\t\t\t\t||                                                  ||\n";
        cout << "\t\t\t\t\t\t\t||                                                  ||\n";
        cout << "\t\t\t\t\t\t\t||                                                  ||\n";
        cout << "\t\t\t\t\t\t\t==================================================\n";
        cout << "\t\t\t\t\t\t\t******************************************************\n\n\n";
        cout << " \n\n\n\t\t\t\t\t\t\t Press any key to continue:";
        getch();
        system("cls");

        loginChoice = loginMenu();
        switch (loginChoice) {
            case 1:
                if (!loginManager.authenticate()) {
                    cout << "\n\n\t\t\t\t\t\t Authentication failed. Try again.\n";
                    getch();
                } else {
                    {
                        system("cls");
                        Details contact;
                        int choice;

                        while (true) {
                            cout << "\t\t*** CONTACT MANAGEMENT SYSTEM!!! ***\n";
                            cout << "\t\t=====================================\n";
                            cout << "\t\t\t***MAIN MENU***\n";
                            cout << "\t\t\t[1] Add a new contact\n";
                            cout << "\t\t\t[2] List all contacts\n";
                            cout << "\t\t\t[3] Search for contact\n";
                            cout << "\t\t\t[4] Delete any contact\n";
                            cout << "\t\t\t[0] Exit\n";
                            cout << "\t\t=====================================\n";
                            cout << "\t\t\tEnter your choice between [0-4]: ";
                            cin >> choice;

                            switch (choice) {
                                case 1:
                                    system("cls");
                                    contact.getdata();
                                    contact.writeonfile();
                                    break;

                                case 2:
                                    system("cls");
                                    contact.readfromfile();
                                    break;

                                case 3:
                                    system("cls");
                                    contact.searchfromfile();
                                    break;

                                case 4:
                                    system("cls");
                                    contact.deletefromfile();
                                    break;

                                case 0:
                                    system("cls");
                                    cout << "\t\t\t ******* Thank you For Using CMS *******\n\n";
                                    exit(0);
                                    break;

                                default:
                                    cout << "\nInvalid choice! Please enter a valid option.\n";
                                    break;
                            }
                        }
                    }
                }
                break;

            case 2:
                loginManager.signup();
                break;

            case 3:
                exit(0);
                break;

            default:
                cout << "\n\n\t\t\t\t\t\t Invalid choice. Please try again.\n";
                getch();
                break;
        }
    }

    return 0;
}

