#include "LogIntoTheSystem.h"

template<typename VALUE>
void System::CatchWrongValue(VALUE value)
{
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		throw exception("������������ ����.");
	}
}

void System::Fillauthorizationfile()
{
	ifstream file;
	file.open(USERS);
	if (!file.is_open() || file.peek() == EOF)
		throw FileException(USERS);

	string login;
	string password;
	string role;
	//�������� �� ������������� ������
	//�������� �� ������������ ������ � ������
	while (!file.eof())
	{
		file >> login >> password >> role;
		if (role == "0")
			users.push_back(new User(login, password));
		else if (role == "1")
			users.push_back(new Admin(login, password));
		size++;
	}

	file.close();
}

System::System()
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
		cout << "�� ����� ��� ������� " << (*AuthorizedUser)->GetLogin() << " ��� ����� " << (*AuthorizedUser)->GetStringRole() << endl;
	}
	else
	{
		throw exception("��������� �������� ��� ����������� � ��������...");
	}
}

bool System::LogInAsUser()
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

vector<User*>::iterator System::FindByLogin(string login)
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

void System::Menu()
{
	if ((*AuthorizedUser)->GetRole())
	{
		AdminMenu();
	}
	else
	{
		UserMenu();
	}
}

vector<User*>::iterator System::users_end()
{
	return users.end();
}

void System::AdminMenu()
{
	int choice;
	while (true)
	{
		cout << "\t������ � �������� ��������" << endl;
		cout << "1.�������� ������� �������" << endl;
		cout << "2.���������� ������� ������" << endl;
		cout << "3.�������������� ������� ������" << endl;
		cout << "4.�������� ������� ������" << endl << endl;
		cout << "\t������ � ������� � ������������ ����������" << endl;
		cout << "5.�������� ������ ���������" << endl;
		cout << "6.���������� ���������� � ��������." << endl;
		cout << "7.�������������� ���������� � �������� � ��� ���������." << endl;
		cout << "8.�������� �������� �� ���� ������" << endl;
		cout << "9.����� ���������� �� ����������." << endl;
		cout << "10.����� ���������� � �������� �� ������������� ������." << endl;
		cout << "11.���������� ������ ��������� �� ����������." << endl;
		cout << "12.������ �� ���������/��������� ���������" << endl << endl;
		cout << "\t������" << endl;
		cout << "12.����� �� ���������" << endl;
		cout << "����: ";
		cin.ignore(cin.rdbuf()->in_avail());
		cin >> noskipws >> choice;
		try
		{
			switch (choice)
			{
			case 1:
				PrintAllAccounts();
				break;
			case 2:
				cout << "1. �������� ��������������" << endl;
				cout << "2. �������� ������������" << endl;
				cout << "3. ��������� � ������� ����." << endl;
				cout << "����: ";
				cin.ignore(cin.rdbuf()->in_avail());
				cin >> noskipws >> choice;
				AddAccount(choice);
				break;
			case 3:
				EditAccount();
				break;
			case 4:
				DeleteAccount();
				break;
			case 12:
				return;
			default:
				CatchWrongValue(choice);
				cout << "����� ����� ���." << endl;
			}
		}
		catch (exception& ex)
		{
			cout << ex.what() << endl;
		}
		system("pause");
		system("cls");
	}
}  

void System::AddAccount(int choice)
{
	char option;
	string login;
	string password;
	User* user;
	switch (choice)
	{
	case 1:
		user = new Admin();
		break;
	case 2:
		user = new User();
		break;
	case 3:
		return;
	default:
		CatchWrongValue(choice);
		cout << "����� ��������� ������ ��������� ��� � ������� ����";
		return;
	}
	user->SetLogin(*this);
	user->SetPassword();
	cout << "��������� �������?\n1.��\n2.���" << endl;
	cin.ignore(cin.rdbuf()->in_avail());
	cin >> noskipws >> option;
	switch (option)
	{
	case '1':
		users.push_back(user);
		++size;
		cout << "������������ " << user->GetLogin() << " ��� ����� " << user->GetStringRole() << " ��� ��������." << endl;
		return;
	case '2':
		delete user;
		return;
	default:
		CatchWrongValue(option);
		delete user;
		cout << "����� ��������� ������ ��������� �� �����������. ��������������� � ������� ����.";
		return;
	}
}

void System::EditAccount()
{
	string login;
	string password;
	int choice;
	vector<User*>::iterator Current_User;
	cout << "������� ����� ��������, ���������� � ������� ����� ��������:";
	cin.ignore(cin.rdbuf()->in_avail());
	cin >> noskipws >> login;
	try
	{
		Current_User = FindByLogin(login);
		cout << "����� ���������� ��������� ��������?" << endl;
		cout << "1.�����\n2.������\n3.��������� � ������� ����.";
		cin.ignore(cin.rdbuf()->in_avail());
		cin >> noskipws >> choice;
		switch (choice)
		{
		case 1:
			(*Current_User)->SetLogin(*this);
			break;
		case 2:
			password = (*Current_User)->GetPassword();
			(*Current_User)->SetPassword();
			break;
		case 3:
			cout << "������� � ������� ����";
			return;
		default:
			CatchWrongValue(choice);
			return;
		}
	}
	catch (exception& ex)
	{
		cout << "����� ��������� ������ ��������� ��� � ������� ����";
	}
	cout << "��������� ���������?\n1.��\n2.���" << endl;
	int option;
	cin.ignore(cin.rdbuf()->in_avail());
	cin >> noskipws >> option;
	switch (option)
	{
	case 1:
		if (choice == 1)
		{
			cout << "����� ������������ " << login << " ������ �� " << (*Current_User)->GetLogin();
		}
		else
		{
			cout << "������ ������������ " << login << " ������ � " << password << " �� " << (*Current_User)->GetPassword();
		}
		return;
	case 2:
		(*Current_User)->SetLoginWITHOUTRESTRICTION(login);
		(*Current_User)->SetPasswordWITHOUTRESTRICTION(password);
		return;
	default:
		CatchWrongValue(option);
		cout << "����� ��������� ������ ��������� �� �����������. ��������������� � ������� ����.";
		return;
	}
}

void System::PrintAllAccounts()
{
	cout << setw(40) << left << "�����" << setw(40) << "������" << setw(40) << "����" << endl;
	for (auto* user : users)
	{
		cout << *user << endl;
	}
}

void System::DeleteAccount()
{
	string Currentuser_login = (*AuthorizedUser)->GetLogin();
	string login;
	string password;
	int choice;
	vector<User*>::iterator Current_User;
	cout << "������� ����� ��������, ���������� � ������� ����� �������:";
	cin.ignore(cin.rdbuf()->in_avail());
	cin >> noskipws >> login;
	if (login == (*AuthorizedUser)->GetLogin())
	{
		cout << "�� �� ������ ������� ���� �������. ����� � ������� ����.";
		return;
	}
	try
	{
		Current_User = FindByLogin(login);
		cout << "������� ������� " << login << "?\n1.��\n2.���" << endl;
		int option;
		cin.ignore(cin.rdbuf()->in_avail());
		cin >> noskipws >> option;
		switch (option)
		{
		case 1:
			users.erase(Current_User);
			size--;
			AuthorizedUser = FindByLogin(Currentuser_login);
			cout << "������������ " << login << " ������.";
			return;
		case 2:
			cout << "������������ � ������� ����. ";
			return;
		default:
			CatchWrongValue(option);
			cout << "����� ��������� ������ ��������� �� �����������. ��������������� � ������� ����.";
			return;
		}
	}
	catch (exception& ex)
	{
		cout << ex.what() << ". ������� � ������� ����.";
	}
}