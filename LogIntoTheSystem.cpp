#include "LogIntoTheSystem.h"

LogIntoTheSystem::LogIntoTheSystem()
{
	this->size = 0;
	try
	{
		Fillauthorizationfile();
	}
	catch (FileException& ex)
	{
		cout << ex.what() << ex.GetFileName();
		//EmergencyAdminFile(); ������� ������
	}
	if (LogInAsUser())
	{
		cout << "�� ����� ��� ������� " << (*AuthorizedUser)->GetLogin() << "��� �����" << (*AuthorizedUser)->GetStringRole();
	}
	else
	{
		throw exception("��������� �������� ��� ����������� � ��������...");
	}
}

bool LogIntoTheSystem::LogInAsUser()
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
			vector<User*>::iterator Iuser;
			Iuser = FindByLogin(login);
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
		catch (exception& ex)
		{
			cout << ex.what();
		}
		cout << "�������� �������: " << attempts << endl;
	}
	return false;
}

vector<User*>::iterator LogIntoTheSystem::FindByLogin(string login)
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

vector<User*>::iterator LogIntoTheSystem::users_end()
{
	return users.end();
}