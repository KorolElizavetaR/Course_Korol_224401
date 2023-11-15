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
            cout << "Логин (не меньше семи символов)" << ":";
            cin >> login;
            int size = login.size();
            if (size < 6)
            {
                cout << "Логин слишком короткий.Введите другой." << endl;
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
                cout << "В логине не могут быть только цифры." << endl;
                repeat = 1;
                continue;
            }
            if (log.FindByLogin(login))
            {
                cout << "Логин уже занят. Придумайте новый." << endl;
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
            cout << "Пароль(не меньше 6 символов):";
            cin >> password;
            if (password.size() < 6)
            {
                cout << "Пароль слишком короткий.Введите другой." << endl;;
                continue;
            }
            this->password = password;
        }
    }

    void AdminMenu()
    {

    }
};

