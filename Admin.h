#pragma once
#include "User.h"

class Admin : public User
{
public:
	Admin(string name, string password) :User(name, password)
	{
	}
    Admin():User()
    {
    }
	void SetLogin(LogIntoTheSystem& log)
	{
        string login;
        LogIntoTheSystem log();
        bool repeat = 0;
        do
        {
            repeat = 0;
            cout << "����� (�� ������ ���� ��������)" << ":";
            cin >> login;
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
            if (log.FindByLogin(login))
            {
                cout << "����� ��� �����. ���������� �����." << endl;
                continue;
            }
            if (!repeat)
            {
                this->password = password;
                return;
            }
        } while (repeat);
	}
    void SetPassword()
    {
        string password;
        while (true)
        {
            cout << "������(�� ������ 6 ��������):";
            cin >> password;
            if (password.size() < 6)
            {
                cout << "������ ������� ��������.������� ������." << endl;;
                continue;
            }
            this->password = password;
        }
    }

    void AdminMenu()
    {

    }
};

