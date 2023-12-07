#include "LogIntoTheSystem.h"

User::User(string login, string password)
{
	this->login = login;
	this->password = password;
	this->role = false;
}

User::User()
{
	this->login = "";
	this->password = "";
	this->role = false;
}

string User::GetLogin()
{
	return this->login;
}

string User::GetPassword()
{
	return this->password;
}

string User::GetStringRole()
{
	return "������������";
}

void User::SetLogin(System& log)
{
    string login;
    bool repeat = 0;
    do
    {
        repeat = 0;
        cout << "����� (�� ������ ���� ��������)" << ":";
        cin.ignore(cin.rdbuf()->in_avail());
        cin >> noskipws >> login;
        int size = login.size();
        if (size < 6)
        {
            cout << "����� ������� ��������.������� ������." << endl;
            repeat = 1;
            continue;
        }
        bool Only_Digits = 1;
        for (int i = 0; i < size; i++)
        {
            if ((login[i] >= 'a' && login[i] <= 'z') || (login[i] >= 'A' && login[i] <= 'Z'))
            {
                Only_Digits = 0;
                break;
            }
        }
        if (Only_Digits)
        {
            cout << "� ������ �� ����� ���� ������ �����." << endl;
            repeat = 1;
            continue;
        }
        try
        {
            log.FindByLogin(login);
            cout << "����� ��� �����. ���������� �����." << endl;
            repeat = 1;
            continue;
        }
        catch (exception& ex)
        {
            // :)
        }
        if (!repeat)
        {
            this->login = login;
            return;
        }
    } while (repeat);
}

void User::SetPassword()
{
    string password;
    while (true)
    {
        cout << "������(�� ������ 6 ��������):";
        cin.ignore(cin.rdbuf()->in_avail());
        cin >> noskipws >> password;
        if (password.size() < 6)
        {
            cout << "������ ������� ��������.������� ������." << endl;;
            continue;
        }
        this->password = password;
        return;
    }
}

bool User::GetRole()
{
    return this->role;
}

void User::SetLoginWITHOUTRESTRICTION(string login)
{
    this->login = login;
}

void User::SetPasswordWITHOUTRESTRICTION(string password)
{
    this->password = password;
}