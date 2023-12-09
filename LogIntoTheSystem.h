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
		cout << "\tРедактирование учетных записей" << endl;
		cout << "1.Просмотр учетных записей" << endl;
		cout << "2.Добавление учетной записи" << endl;
		cout << "3.Редактирование учетной записи" << endl;
		cout << "4.Удаление учетной записи" << endl;
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