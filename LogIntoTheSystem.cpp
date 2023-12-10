#include "LogIntoTheSystem.h"

template<typename VALUE>
void System::CatchWrongValue(VALUE value)
{
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		throw exception("Неккоректный ввод.");
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
	//Проверка на существование логина
	//Проверка на корректность записи в строке
	while (!file.eof())
	{
		file >> login >> password >> role;
		if (role == "0")
			users.push_back(new User(login, password));
		else if (role == "1")
			users.push_back(new Admin(login, password));
	}

	file.close();
}

System::System()
{
	try
	{
		Fillauthorizationfile();
		FillStudentsFromFile();
	}
	catch (FileException& ex)
	{
		cout << ex.what() << ex.GetFileName();
		//EmergencyAdminFile(); создать админа
	}
	if (LogInAsUser())
	{
		cout << "Вы вошли под логином " << (*AuthorizedUser)->GetLogin() << " под ролью " << (*AuthorizedUser)->GetStringRole() << endl;
	}
	else
	{
		throw exception("Произошли проблемы при подключении к аккаунту...");
	}
}

bool System::LogInAsUser()
{
	string login;
	string password;
	unsigned char p;
	int attempts = 6;
	while (--attempts != 0)
	{
		cout << "Введите логин: ";
		cin >> login;
		cout << "Введите пароль: ";
		while (true)
		{
			p = _getch();
			if (p == 13) break;
			if (p == '\b' && !password.empty())
			{
				password.erase(password.size() - 1);
				cout << "\b \b";
			}
			if (isalnum((unsigned char)p))
			{
				cout << '*';
				password += p;
			}
		}
		cout << "\n";
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

vector<User*>::iterator System::FindByLogin(string login)
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
	string ID;
	while (true)
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
		cout << "Ввод: ";
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
				cout << "1. Добавить администратора" << endl;
				cout << "2. Добавить пользователя" << endl;
				cout << "3. Вернуться в главное меню." << endl;
				cout << "Ввод: ";
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
			case 5:
				PrintAllStudents();
				break;
			case 6:
				AddStudent();
				break;
			case 7:
				cout << "Введите ID студента" << endl;
				cin.ignore(cin.rdbuf()->in_avail());
				cin >> noskipws >> choice;

				cout << "1. Изменить ФИО" << endl;
				cout << "2. Изменить средний балл" << endl;
				cout << "3. Изменить льготу." << endl;
				cout << "Ввод: ";
				cin.ignore(cin.rdbuf()->in_avail());
				cin >> noskipws >> choice;
				EditStudent(choice);
				break;
			case 12:
				return;
			default:
				CatchWrongValue(choice);
				cout << "Такой опции нет." << endl;
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
		cout << "Ввиду неясности ответа переводим вас в главное меню";
		return;
	}
	user->SetLogin(*this);
	user->SetPassword();
	cout << "Сохранить аккаунт?\n1.Да\n2.Нет" << endl;
	cin.ignore(cin.rdbuf()->in_avail());
	cin >> noskipws >> option;
	switch (option)
	{
	case '1':
		users.push_back(user);
		cout << "Пользователь " << user->GetLogin() << " под ролью " << user->GetStringRole() << " был добавлен." << endl;
		return;
	case '2':
		delete user;
		return;
	default:
		CatchWrongValue(option);
		delete user;
		cout << "Ввиду неясности ответа изменения не сохранились. Перенаправление в главное меню.";
		return;
	}
}

void System::EditAccount()
{
	string login;
	string password;
	int choice;
	vector<User*>::iterator Current_User;
	cout << "Введите логин аккаунта, информацию о котором нужно изменить:";
	cin.ignore(cin.rdbuf()->in_avail());
	cin >> noskipws >> login;
	try
	{
		Current_User = FindByLogin(login);
		cout << "Какую информацию требуется изменить?" << endl;
		cout << "1.Логин\n2.Пароль\n3.Вернуться в главное меню.";
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
			cout << "Возврат в главное меню";
			return;
		default:
			CatchWrongValue(choice);
			return;
		}
	}
	catch (exception& ex)
	{
		cout << "Ввиду неясности ответа переводим вас в главное меню";
	}
	cout << "Сохранить изменения?\n1.Да\n2.Нет" << endl;
	int option;
	cin.ignore(cin.rdbuf()->in_avail());
	cin >> noskipws >> option;
	switch (option)
	{
	case 1:
		if (choice == 1)
		{
			cout << "Логин пользователя " << login << " сменен на " << (*Current_User)->GetLogin();
		}
		else
		{
			cout << "Пароль пользователя " << login << " сменен с " << password << " на " << (*Current_User)->GetPassword();
		}
		return;
	case 2:
		(*Current_User)->SetLoginWITHOUTRESTRICTION(login);
		(*Current_User)->SetPasswordWITHOUTRESTRICTION(password);
		return;
	default:
		CatchWrongValue(option);
		cout << "Ввиду неясности ответа изменения не сохранились. Перенаправление в главное меню.";
		return;
	}
}

void System::PrintAllAccounts()
{
	cout << setw(40) << left << "ЛОГИН" << setw(40) << "ПАРОЛЬ" << setw(40) << "РОЛЬ" << endl;
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
	cout << "Введите логин аккаунта, информацию о котором нужно удалить:";
	cin.ignore(cin.rdbuf()->in_avail());
	cin >> noskipws >> login;
	if (login == (*AuthorizedUser)->GetLogin())
	{
		cout << "Вы не можете удалить свой аккаунт. Выход в главное меню.";
		return;
	}
	try
	{
		Current_User = FindByLogin(login);
		cout << "Удалить аккаунт " << login << "?\n1.Да\n2.Нет" << endl;
		int option;
		cin.ignore(cin.rdbuf()->in_avail());
		cin >> noskipws >> option;
		switch (option)
		{
		case 1:
			users.erase(Current_User);
			AuthorizedUser = FindByLogin(Currentuser_login);
			cout << "Пользователь " << login << " удален.";
			return;
		case 2:
			cout << "Возвращаемся в главное меню. ";
			return;
		default:
			CatchWrongValue(option);
			cout << "Ввиду неясности ответа изменения не сохранились. Перенаправление в главное меню.";
			return;
		}
	}
	catch (exception& ex)
	{
		cout << ex.what() << ". Возврат в главное меню.";
	}
}

void System::PrintAllStudents()
{
	for (auto student : students)
	{
		cout << "Имя студента:" << student.GetStudentFullName() << "\n\tID:" << student.GetID()
			<< "\n\tТекущая стипендия:" << student.GetAccessToScholarship().GetScholarship()
			<< "\n\tСредний балл:" << student.GetAccessToScholarship().GetAverageGrade()
			<< "\n\tЛьгота:" << student.GetAccessToScholarship().GetBenefit() << endl;
	}
}

void System::AddStudent()
{
	Student st;
	st.SetFIO();
	st.GenerateID();
	cout << "ID студента:" << st.GetID() << endl;
	cout << "Остальная информация добавляется в разделе редактирования студента.";
	students.push_back(st);
}