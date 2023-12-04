#include "Admin.h"

Admin::Admin(string name, string password) :User(name, password)
{
	this->role = true;
}

void Admin::Menu_accounts()
{
    cout << "\tРедактирование учетных записей" << endl;
    cout << "1.Просмотр учетных записей" << endl;
    cout << "2.Добавление учетной записи" << endl;
    cout << "3.Редактирование учетной записи" << endl;
    cout << "4.Удаление учетной записи" << endl;
}

string Admin::GetStringRole()
{
    return "администратор";
}