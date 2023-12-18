#pragma once
#include "AllDependencies.h"
#include "System.h"

using namespace std;
class System;

class USER0
{
protected:
	string login;
	string password;
	bool role;
    friend ostream& operator<<(ostream& os, const USER0& user);
    USER0();
public:

    string GetLogin();
    string GetPassword();
    virtual string GetStringRole() = 0;
    void SetLogin(System& log);
    void SetPassword();
    bool GetRole();

    void SetLoginWITHOUTRESTRICTION(string login);

    void SetPasswordWITHOUTRESTRICTION(string password);
};

class User :public USER0
{
public:
    User();
    User(string login, string password);

    string GetStringRole() override;
};

class Admin : public USER0
{
public:
    Admin();
    Admin(string login, string password);

    string GetStringRole() override;
};

inline ostream& operator<<(ostream& os, const USER0& user)
{
    os << setw(40) << left << user.login << setw(40) << user.password << setw(40) << user.role;
    return os;
}