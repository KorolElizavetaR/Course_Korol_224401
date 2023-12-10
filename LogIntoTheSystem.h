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


	void Fillauthorizationfile();

	void FillStudentsFromFile()
	{
		string FullName;
		string Name, Surname, LastName;
		string GroupID;
		double AverageGrade;
		int Benefit;

		ifstream file;
		file.open(STUDENTS);
		if (!file.is_open() || file.peek() == EOF)
			throw FileException(STUDENTS);

		while (!file.eof())
		{
			file >> Surname >> Name >> LastName >> GroupID >> AverageGrade >> Benefit;
			FullName = Surname + " " + Name + " " + LastName;
			students.push_back(Student(FullName, GroupID, AverageGrade, Benefit));
		}

		file.close();
	}

	template<typename VALUE>
	void CatchWrongValue(VALUE value);

public:

	void AddStudent();

	void PrintAllStudents();

	System();

	bool LogInAsUser();

	vector<User*>::iterator FindByLogin(string login);

	vector<User*>::iterator users_end();

	void AdminMenu();

	void UserMenu()
	{
		
	}

	void Menu();

	void PrintAllAccounts();

	void AddAccount(int choice);

	void EditAccount();

	void DeleteAccount();

	void EditStudent( int choice)
	{
		switch (choice)
		{
		case 1:
			user = new Admin();
			break;
		case 2:
			user = new User();
			break;
		case 3:
			return;
		default:
			CatchWrongValue(choice);
			cout << "Ввиду неясности ответа переводим вас в главное меню";
			return;
		}
		user->SetLogin(*this);
		user->SetPassword();
		cout << "Сохранить аккаунт?\n1.Да\n2.Нет" << endl;
		cin.ignore(cin.rdbuf()->in_avail());
		cin >> noskipws >> option;
		switch (option)
		{
		case '1':
			users.push_back(user);
			cout << "Пользователь " << user->GetLogin() << " под ролью " << user->GetStringRole() << " был добавлен." << endl;
			return;
		case '2':
			delete user;
			return;
		default:
			CatchWrongValue(option);
			delete user;
			cout << "Ввиду неясности ответа изменения не сохранились. Перенаправление в главное меню.";
			return;
		}
	}
};