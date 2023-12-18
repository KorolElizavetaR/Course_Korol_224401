#include "System.h"

User::User()
{
	this->role = false;
}

User::User(string login, string password) :User()
{
	this->password = password;
	this->login = login;
}

string User::GetStringRole()
{
	return "пользователь";
}