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
			//�������� �� ������������� ������
			//�������� �� ������������ ������ � ������
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
		cout << "������ ��� �������� �����. ������� ������ �� ��������������." << endl;
		// ���������� � ����� ������;
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
			cout << "�� ����� ��� ������� " << (*AuthorizedUser)->GetLogin() << "��� �����" << (*AuthorizedUser)->GetStringRole();
		}
	}

	bool LogInAsUser()
	{
		string login;
		string password;
		int attempts = 6;
		while (--attempts != 0)
		{
			cout << "������� �����: ";
			cin >> login;
			cout << "������� ������: ";
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
					cout << "�������� ������ ��� �����.";
				}
			}
			catch(exception &ex)
			{
				cout << ex.what();
			}
			cout << "�������� �������: " << attempts << endl;
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
		throw exception("������������ �� ������. ");
	}

	vector<User*>::iterator users_end()
	{
		return users.end();
	}
};

