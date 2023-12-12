#pragma once
#include "AllDependencies.h"
#include "System.h"

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
};

class Admin : public User
{
public:
    Admin();
    Admin(string name, string password);

    string GetStringRole() override;
};

inline ostream& operator<<(ostream& os, const User& user)
{
    os << setw(40) << left << user.login << setw(40) << user.password << setw(40) << user.role;
    return os;
}