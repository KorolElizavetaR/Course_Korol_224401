#pragma once
#define USERS "Users.txt"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "User.h"
#include "FileException.h"

using namespace std;

class LogIntoTheSystem
{ 
	vector <User*> users;
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

	void EmergencyAdminFile()
	{
		cout << "ќшибка при открытии файла. ¬ведите данные об администраторе." << endl;
		// ѕерекинуть в класс админа;
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
		try
		{
			Fillauthorizationfile();
		}
		catch(FileException &ex)
		{
			cout << ex.what() << ex.GetFileName();
			EmergencyAdminFile();
		}


	}
	void LogIn()
	{
		string login;
		string password;
		int attempts = 6;
		while (--attempts != 0)
		{
			cout << "¬ведите логин: ";
			cin >> login;

		}
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

