#pragma once
#define USERS "Users.txt"
#include <vector>
#include <string>
#include <fstream>
#include "User.h"

using namespace std;

class LogIntoTheSystem
{
	vector <User*> users;
	int size;

	bool Fillauthorizationfile()
	{
		ifstream file;
		file.open(USERS);
		if (!file.is_open() || file.peek() == EOF)
			return true;

		string login;
		string password;
		string role;
			
		while (!file.eof())
		{
			file >> login >> password >> role;
			if (role == "0")
				users.push_back(new User(login, password));
			else if (role == "1")
				users.push_back(new Admin(login, password));
			size++;
		} 

		file.close();
		return false;
	}

	void EmergencyAdminFile()
	{
		cout << "ќшибка при открытии файла. ¬ведите данные об администраторе." << endl;
		ofstream file;
		file.open(USERS);
		Admin user;

		user.SetLogin(*this);
		user.SetPassword();

		file << user.GetLogin() << " " << user.GetPassword() << " " << "1";
		users.push_back(&user);
		this->size++;
		file.close();
	}
		
public:

	LogIntoTheSystem()
	{
		this->size = 0;
		if (Fillauthorizationfile())
			EmergencyAdminFile();
	}

	int FindByLogin(string login)
	{
		for (int i = 0; i<size;i++)
		{
			if (users[i]->GetLogin() == login)
				return i;
		}
	}
};

