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
        cout << "\tРабота с данными о студенческих стипендиях" << endl;
        cout << "1.Общая информация по стипендиям." << endl;
        cout << "2.Поиск информации о студенте по студенческому номеру." << endl;
        cout << "3.Оставить заявку на получение/повышение стипендии." << endl << endl;
        cout << "\tПрочее" << endl; 
        cout << "12.Выход из программы" << endl;
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