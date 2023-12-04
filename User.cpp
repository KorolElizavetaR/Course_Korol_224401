#include "User.h"

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
	return "пользователь";
}

void User::SetLogin(LogIntoTheSystem& log)
{
    string login;
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
        if (log.FindByLogin(login) != log.users_end())
        {
            cout << "Логин уже занят. Придумайте новый." << endl;
            continue;
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