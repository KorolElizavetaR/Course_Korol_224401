#pragma once
#define USERS "Users.txt"

#include "AllDependencies.h"
#include "Users.h"
#include "FileException.h"

class LogIntoTheSystem
{
	vector <User*> users;
	vector<User*>::iterator AuthorizedUser;
	int size;

	void Fillauthorizationfile()
	{
		ifstream file;
		file.open(USERS);
		if (!file.is_open() || file.peek() == EOF)
			throw FileException(USERS);

		string login;
		string password;
		string role;
		//Проверка на существование логина
		//Проверка на корректность записи в строке
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
	}

public:

	LogIntoTheSystem();

	bool LogInAsUser();

	vector<User*>::iterator FindByLogin(string login);

	vector<User*>::iterator users_end();
};



