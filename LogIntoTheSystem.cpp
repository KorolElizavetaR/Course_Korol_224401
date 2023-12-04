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
		//EmergencyAdminFile(); создать админа
	}
	if (LogInAsUser())
	{
		cout << "Вы вошли под логином " << (*AuthorizedUser)->GetLogin() << "под ролью" << (*AuthorizedUser)->GetStringRole();
	}
	else
	{
		throw exception("Произошли проблемы при подключении к аккаунту...");
	}
}

bool LogIntoTheSystem::LogInAsUser()
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
			vector<User*>::iterator Iuser;
			Iuser = FindByLogin(login);
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
		catch (exception& ex)
		{
			cout << ex.what();
		}
		cout << "Осталось попыток: " << attempts << endl;
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
	throw exception("Пользователь не найден. ");
}

vector<User*>::iterator LogIntoTheSystem::users_end()
{
	return users.end();
}