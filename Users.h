#pragma once
#include "AllDependencies.h"

using namespace std;
class LogIntoTheSystem;

class User
{
protected:
	string login;
	string password;
	bool role;
    friend ostream& operator<<(ostream& os, const User& user);
public:
    User(string login, string password);
    User();

    string GetLogin();
    string GetPassword();
    virtual string GetStringRole();
    void SetLogin(LogIntoTheSystem& log);
    void SetPassword();

    void MenuOptions()
    {
        cout << "\tРабота с данными о студенческих стипендиях" << endl;
        cout << "1.Общая информация по стипендиям." << endl;
        cout << "2.Поиск информации о студенте по студенческому номеру." << endl;
        cout << "3.Оставить заявку на получение/повышение стипендии." << endl << endl;
        cout << "\tПрочее" << endl;
        cout << "12.Выход из программы" << endl;
    }

    virtual void Menu(LogIntoTheSystem& log)
    {
        MenuOptions();
    }
};

class Admin : public User
{
public:

    Admin(string name, string password);

    void Menu_accounts();

    string GetStringRole() override;

    void MenuOptions()
    {
        cout << "\tРабота с учетными записями" << endl;
        cout << "1.Просмотр учетных записей" << endl;
        cout << "2.Добавление учетной записи" << endl;
        cout << "3.Редактирование учетной записи" << endl;
        cout << "4.Удаление учетной записи" << endl << endl;
        cout << "\tРабота с данными о студенческих стипендиях" << endl;
        cout << "5.Просмотр списка студентов" << endl;
        cout << "6.Добавление информации о студенте." << endl;
        cout << "7.Редактирование информации о студенте и его стипендии." << endl;
        cout << "8.Удаление студента из базы данных" << endl;
        cout << "9.Общая информация по стипендиям." << endl;
        cout << "10.Поиск информации о студенте по студенческому номеру." << endl;
        cout << "11.Сортировка списка студентов по параметрам." << endl;
        cout << "12.Заявки на получение/повышение стипендии" << endl << endl;
        cout << "\tПрочее" << endl;
        cout << "12.Выход из программы" << endl;
    }

    void Menu(LogIntoTheSystem& log) override
    {
        int choice;
        while (true)
        {
            MenuOptions();
            cout << "Ввод: ";
            cin >> choice;
            switch (choice)
            {
            case 12:
                return;
            }
        }
    }
};

inline ostream& operator<<(ostream& os, const User& user)
{
    os << setw(40) << left << user.login << setw(40) << user.password << setw(40) << user.role << endl;
    // os << user.login << user.password << endl;
    return os;
}