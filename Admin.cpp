#include "Admin.h"

Admin::Admin(string name, string password) :User(name, password)
{
	this->role = true;
}

void Admin::Menu_accounts()
{
    cout << "\t�������������� ������� �������" << endl;
    cout << "1.�������� ������� �������" << endl;
    cout << "2.���������� ������� ������" << endl;
    cout << "3.�������������� ������� ������" << endl;
    cout << "4.�������� ������� ������" << endl;
}

string Admin::GetStringRole()
{
    return "�������������";
}