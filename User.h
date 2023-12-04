#pragma once
#include <iostream>
#include "LogIntoTheSystem.h"

using namespace std;

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



