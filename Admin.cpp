#include "System.h"

Admin::Admin()
{
	this->role = true;
}

Admin::Admin(string login, string password):Admin()
{
	this->password = password;
	this->login = login;
}

string Admin::GetStringRole()
{
    return "администратор";
}