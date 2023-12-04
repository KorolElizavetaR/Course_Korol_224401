#pragma once
#include "User.h"

using namespace std;

class Admin : public User
{
public:
    Admin(string name, string password) :User(name, password) {}

    void Menu_accounts();

    string GetStringRole() override;
};

