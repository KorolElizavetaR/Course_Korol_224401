#pragma once
class User
{
protected:
	string login;
	string password;
	bool role;
public:
	User(string login, string password):User()
	{
		this->login = login;
		this->password = password;
	}
	User()
	{
		this->login = "";
		this->password = "";
		this->role = false;
	}
	string GetLogin()
	{
		return this->login;
	}
	string GetPassword()
	{
		return this->password;
	}
};



