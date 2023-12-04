#pragma once
#include "AllDependencies.h"

using namespace std;
class LogIntoTheSystem;

class User
{
protected:
	string login;
	string password;
	bool role;
    friend ostream& operator<<(ostream& os, const User& user);
public:
    User(string login, string password);
    User();

    string GetLogin();
    string GetPassword();
    virtual string GetStringRole();
    void SetLogin(LogIntoTheSystem& log);
    void SetPassword();

    void MenuOptions()
    {
        cout << "\t������ � ������� � ������������ ����������" << endl;
        cout << "1.����� ���������� �� ����������." << endl;
        cout << "2.����� ���������� � �������� �� ������������� ������." << endl;
        cout << "3.�������� ������ �� ���������/��������� ���������." << endl << endl;
        cout << "\t������" << endl;
        cout << "12.����� �� ���������" << endl;
    }

    virtual void Menu(LogIntoTheSystem& log)
    {
        MenuOptions();
    }
};

class Admin : public User
{
public:

    Admin(string name, string password);

    void Menu_accounts();

    string GetStringRole() override;

    void MenuOptions()
    {
        cout << "\t������ � �������� ��������" << endl;
        cout << "1.�������� ������� �������" << endl;
        cout << "2.���������� ������� ������" << endl;
        cout << "3.�������������� ������� ������" << endl;
        cout << "4.�������� ������� ������" << endl << endl;
        cout << "\t������ � ������� � ������������ ����������" << endl;
        cout << "5.�������� ������ ���������" << endl;
        cout << "6.���������� ���������� � ��������." << endl;
        cout << "7.�������������� ���������� � �������� � ��� ���������." << endl;
        cout << "8.�������� �������� �� ���� ������" << endl;
        cout << "9.����� ���������� �� ����������." << endl;
        cout << "10.����� ���������� � �������� �� ������������� ������." << endl;
        cout << "11.���������� ������ ��������� �� ����������." << endl;
        cout << "12.������ �� ���������/��������� ���������" << endl << endl;
        cout << "\t������" << endl;
        cout << "12.����� �� ���������" << endl;
    }

    void Menu(LogIntoTheSystem& log) override
    {
        int choice;
        while (true)
        {
            MenuOptions();
            cout << "����: ";
            cin >> choice;
            switch (choice)
            {
            case 12:
                return;
            }
        }
    }
};

inline ostream& operator<<(ostream& os, const User& user)
{
    os << setw(40) << left << user.login << setw(40) << user.password << setw(40) << user.role << endl;
    // os << user.login << user.password << endl;
    return os;
}