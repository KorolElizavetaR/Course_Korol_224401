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
public:
    User(string login, string password);
    User();

    string GetLogin();
    string GetPassword();
    virtual string GetStringRole();
    void SetLogin(LogIntoTheSystem& log);
    void SetPassword();
};

class Admin : public User
{
public:

    Admin(string name, string password);

    void Menu_accounts();

    string GetStringRole() override;
};

