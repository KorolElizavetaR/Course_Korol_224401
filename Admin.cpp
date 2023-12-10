#include "System.h"

Admin::Admin():User()
{
	this->role = true;
}
Admin::Admin(string name, string password):User(name, password)
{
	this->role = true;
}

string Admin::GetStringRole()
{
    return "администратор";
}