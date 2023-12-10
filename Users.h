#pragma once
#include "AllDependencies.h"
#include "LogIntoTheSystem.h"

using namespace std;
class System;

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
    void SetLogin(System& log);
    void SetPassword();
    bool GetRole();

    void SetLoginWITHOUTRESTRICTION(string login);

    void SetPasswordWITHOUTRESTRICTION(string password);

    void MenuOptions()
    {
        cout << "\t������ � ������� � ������������ ����������" << endl;
        cout << "1.����� ���������� �� ����������." << endl;
        cout << "2.����� ���������� � �������� �� ������������� ������." << endl;
        cout << "3.�������� ������ �� ���������/��������� ���������." << endl << endl;
        cout << "\t������" << endl; 
        cout << "12.����� �� ���������" << endl;
    }

    virtual void Menu(System* log)
    {
        MenuOptions();
    }
};

class Admin : public User
{
public:
    Admin();
    Admin(string name, string password);

    void Menu_accounts();

    string GetStringRole() override;
};

inline ostream& operator<<(ostream& os, const User& user)
{
    os << setw(40) << left << user.login << setw(40) << user.password << setw(40) << user.role;
    return os;
}