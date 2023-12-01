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

	void EmergencyAdminFile()
	{
		cout << "Ошибка при открытии файла. Введите данные об администраторе." << endl;
		// Перекинуть в класс админа;
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
		if (LogInAsUser())
		{
			cout << "Вы вошли под логином " << (*AuthorizedUser)->GetLogin() << "под ролью" << (*AuthorizedUser)->GetStringRole();
		}
	}

	bool LogInAsUser()
	{
		string login;
		string password;
		int attempts = 6;
		while (--attempts != 0)
		{
			cout << "Введите логин: ";
			cin >> login;
			cout << "Введите пароль: ";
			cin >> password;
			try
			{
				vector<User*>::iterator Iuser = FindByLogin(login);
				if ((*Iuser)->GetPassword() == password)
				{
					AuthorizedUser = Iuser;
					return true;
				}
				else
				{
					cout << "Неверные данные при входе.";
				}
			}
			catch(exception &ex)
			{
				cout << ex.what();
			}
			cout << "Осталось попыток: " << attempts << endl;
		}
		return false;
	}

	vector<User*>::iterator FindByLogin(string login)
	{
		for (vector<User*>::iterator Iuser = users.begin(); Iuser != users.end(); Iuser++)
		{
			if ((*Iuser)->GetLogin() == login)
			{
				return Iuser;
			}
		}
		throw exception("Пользователь не найден. ");
	}

	vector<User*>::iterator users_end()
	{
		return users.end();
	}
};

