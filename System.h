#pragma once
#define USERS "Users.txt"
#define STUDENTS "Students.txt"
#define BENEFITS "Benefits.txt"

#include "AllDependencies.h"
#include "Users.h"
#include "FileException.h"
#include "Students.h"

class System
{
	vector <User*> users;
	vector<User*>::iterator AuthorizedUser;

	vector <Student*> students;


	string PasswordDecipher(string password , int CIPHERCODE);

	void Fillauthorizationfile();

	void FillStudentsFromFile();

	template<typename VALUE>
	void CatchWrongValue(VALUE value);

public:
	vector <Student*>::iterator FindByStudentID(string ID);

	void AddStudent();

	void PrintAllStudents();

	System();

	bool LogInAsUser();

	vector<User*>::iterator FindByLogin(string login);

	void DeleteStudent(vector <Student*>::iterator Istudent);

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

	void PrintStudent(vector<Student*>::iterator student);

	void EditStudent(vector <Student*>::iterator Istudent);

	void BenefitsInformation();
	void SortingMenu();
	void SortByAverageGrade();
	void SortByFIO();
	void ReWriteauthorizationfile();
	void ReWriteStudentsfile();
};