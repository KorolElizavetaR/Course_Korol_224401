#include "System.h"

USER0::USER0()
{
	this->login = "";
	this->password = "";
	this->role = false;
}

string USER0::GetLogin()
{
	return this->login;
}

string USER0::GetPassword()
{
	return this->password;
}

string USER0::GetStringRole()
{
	return "������������";
}

void USER0::SetLogin(System& log)
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

void USER0::SetPassword()
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

bool USER0::GetRole()
{
    return this->role;
}

void USER0::SetLoginWITHOUTRESTRICTION(string login)
{
    this->login = login;
}

void USER0::SetPasswordWITHOUTRESTRICTION(string password)
{
    this->password = password;
}