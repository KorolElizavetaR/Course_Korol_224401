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

	void Fillauthorizationfile();
	template<typename VALUE>
	void CatchWrongValue(VALUE value);

public:

	LogIntoTheSystem();

	bool LogInAsUser();

	vector<User*>::iterator FindByLogin(string login);

	vector<User*>::iterator users_end();

	void AdminMenu();

	void UserMenu()
	{
		cout << "\t�������������� ������� �������" << endl;
		cout << "1.�������� ������� �������" << endl;
		cout << "2.���������� ������� ������" << endl;
		cout << "3.�������������� ������� ������" << endl;
		cout << "4.�������� ������� ������" << endl;
	}

	void Menu();

	void PrintAllAccounts();

	void AddAccount(int choice);

	void EditAccount();

	void DeleteAccount();
};



//istream& operator>>(istream& is, User& item)
//{
//	is >> item.x >> item.y;
//	return is;
//}