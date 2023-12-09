#pragma once
#define USERS "Users.txt"
#define STUDENTS "Students.txt"

#include "AllDependencies.h"
#include "Users.h"
#include "FileException.h"
#include "Students.h"

class System
{
	vector <User*> users;
	vector<User*>::iterator AuthorizedUser;

	vector <Student> students;

	int size;

	void Fillauthorizationfile();

	void FillStudentsFromFile()
	{
		string Name, Surname, LastName;
		string GroupID;
		double AverageGrade;
		int 
	}

	template<typename VALUE>
	void CatchWrongValue(VALUE value);

public:

	System();

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