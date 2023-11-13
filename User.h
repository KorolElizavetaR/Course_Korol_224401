#pragma once
class User
{
protected:
	string login;
	string password;
public:
	User(string login, string password)
	{
		this->login = login;
		this->password = password;
	}
	User()
	{
		this->login = "";
		this->password = "";
	}
};

