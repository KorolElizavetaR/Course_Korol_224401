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

	LogIntoTheSystem()
	{	
		this->size = 0;
		if (Fillauthorizationfile())
			EmergencyAdminFile();
	}

	bool Fillauthorizationfile()
	{
		ifstream file;
		file.open(USERS);
		if (!file.is_open() || file.peek() == EOF)
			return true;

		string login;
		string password;
		bool role;
			
		while (!file.eof())
		{
			file >> login >> password >> role;
			if (role == false)
				users.push_back(new User(login, password));
			else if (role == true)
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
		string login;
		string password;
		bool role;
		user.SetLogin(*this);
		file << login << " " << password << " " << "1";
		users.push_back(new Admin(login, password));
		size++;
		file.close();
	}
		
public:

	LogIntoTheSystem()
	{
		Fillauthorizationfile();
	}

	int FindByLogin(string login)
	{
		for (auto i : users)
		{
			if ((*i).GetLogin() == login)
				return true;
		}
	}
};

