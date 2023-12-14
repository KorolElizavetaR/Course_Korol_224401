#include "System.h"
#define CAEASAR_CIPHER 3

string System::PasswordDecipher(string password, int CIPHERCODE)
{
	int size = password.size();
	for (int i = 0; i < size; i++)
	{
		password[i] += CIPHERCODE;
	}
	return password;
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
		password = PasswordDecipher(password, CAEASAR_CIPHER);
		if (role == "0")
			users.push_back(shared_ptr<User> (new User(login, password)));
		else if (role == "1")
			users.push_back(shared_ptr<User>(new Admin(login, password)));
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
		AddAccount(1);
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
		password = "";
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
			vector<shared_ptr<User>>::iterator Iuser;
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

vector<shared_ptr<User>>::iterator System::FindByLogin(string login)
{
	for (vector<shared_ptr<User>>::iterator Iuser = users.begin(); Iuser != users.end(); Iuser++)
	{
		if ((*Iuser)->GetLogin() == login)
		{
			return Iuser;
		}
	}
	throw exception("Пользователь не найден. ");
}

vector <Student*>::iterator System::FindByStudentID(string ID)
{
	for (vector<Student*>::iterator Istudent = students.begin(); Istudent != students.end(); Istudent++)
	{
		if ((*Istudent)->GetID() == ID)
		{
			return Istudent;
		}
	}
	throw exception("Студент не найден.");
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

vector<shared_ptr<User>>::iterator System::users_end()
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
				cout << "Введите ID студента:";
				cin.ignore(cin.rdbuf()->in_avail());
				cin >> ID;
				EditStudent(FindByStudentID(ID));
				break;
			case 8:
				cout << "Введите ID студента: ";
				cin.ignore(cin.rdbuf()->in_avail());
				cin >> ID;
				DeleteStudent(FindByStudentID(ID));
				break;
			case 9:
				BenefitsInformation();
				break;
			case 10:
				cout << "Введите ID студента: ";
				cin.ignore(cin.rdbuf()->in_avail());
				cin >> noskipws >> ID;
				PrintStudent(FindByStudentID(ID));
				break;
			case 11:
				SortingMenu();
				break;
			case 12:
				ReWriteStudentsfile();
				ReWriteauthorizationfile();
				ScholarshipReportFILE();
				return;
			default:
				WrongValue::CatchWrongValue(choice);
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
	shared_ptr<User> user;
	switch (choice)
	{
	case 1:
		user = shared_ptr<User> (new Admin());
		break;
	case 2:
		user = shared_ptr<User> (new User());
		break;
	case 3:
		return;
	default:
		WrongValue::CatchWrongValue(choice);
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
		return;
	default:
		WrongValue::CatchWrongValue(option);
		cout << "Ввиду неясности ответа изменения не сохранились. Перенаправление в главное меню.";
		return;
	}
}

void System::EditAccount()
{
	string login;
	string password;
	int choice;
	vector<shared_ptr<User>>::iterator Current_User;
	cout << "Введите логин аккаунта, информацию о котором нужно изменить:";
	cin.ignore(cin.rdbuf()->in_avail());
	cin >> noskipws >> login;
	try
	{
		Current_User = FindByLogin(login);
		cout << "Какую информацию требуется изменить?" << endl;
		cout << "1.Логин\n2.Пароль\n3.Вернуться в главное меню.\n\tВвод: ";
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
			WrongValue::CatchWrongValue(choice);
			return;
		}
	}
	catch (exception& ex)
	{
		cout << "Логин не найден." << endl;
		return;
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
			cout << "Логин пользователя " << login << " сменен на " << (*Current_User)->GetLogin() << endl;
		}
		else
		{
			cout << "Пароль пользователя " << login << " сменен с " << password << " на " << (*Current_User)->GetPassword() << endl;
		}
		return;
	case 2:
		(*Current_User)->SetLoginWITHOUTRESTRICTION(login);
		(*Current_User)->SetPasswordWITHOUTRESTRICTION(password);
		return;
	default:
		WrongValue::CatchWrongValue(option);
		cout << "Ввиду неясности ответа изменения не сохранились. Перенаправление в главное меню." << endl;
		return;
	}
}

void System::PrintAllAccounts()
{
	cout << setw(40) << left << "ЛОГИН" << setw(40) << "ПАРОЛЬ" << setw(40) << "РОЛЬ" << endl;
	for (shared_ptr<User> user : users)
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
	vector<shared_ptr<User>>::iterator Current_User;
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
			WrongValue::CatchWrongValue(option);
			cout << "Ввиду неясности ответа изменения не сохранились. Перенаправление в главное меню.";
			return;
		}
	}
	catch (exception& ex)
	{
		cout << ex.what() << ". Возврат в главное меню.";
	}
}

void System::PrintStudent(vector<Student*>::iterator student)
{
	cout << "Имя студента:" << (*student)->GetStudentFullName() << "\n\tID:" << (*student)->GetID()
		<< "\n\tТекущая стипендия:" << (*student)->GetAccessToScholarship().GetScholarship()
		<< "\n\tСредний балл:" << (*student)->GetAccessToScholarship().GetAverageGrade()
		<< "\n\tЛьгота:" << (*student)->GetAccessToScholarship().GetBenefit() << endl;
}

void System::PrintAllStudents()
{
	for (auto Istudent = students.begin(); Istudent != students.end(); Istudent++)
	{
		PrintStudent(Istudent);
		/*cout << "Имя студента:" << student->GetStudentFullName() << "\n\tID:" << student->GetID()
			<< "\n\tТекущая стипендия:" << student->GetAccessToScholarship().GetScholarship()
			<< "\n\tСредний балл:" << student->GetAccessToScholarship().GetAverageGrade()
			<< "\n\tЛьгота:" << student->GetAccessToScholarship().GetBenefit() << endl;*/
	}
}

void System::AddStudent()
{
	Student *st = new Student();
	st->SetFIO();
	cout << "ID студента:" << st->GetID() << endl;
	cout << "Остальная информация добавляется в разделе редактирования студента.";
	students.push_back(st);
}

void System::FillStudentsFromFile()
{
	string FullName;
	string Name, Surname, LastName;
	string GroupID;
	double AverageGrade;
	int Benefit;

	ifstream file;
	file.open(STUDENTS);
	if (!file.is_open() || file.peek() == EOF)
		throw FileException(STUDENTS);

	while (!file.eof())
	{
		file >> Surname >> Name >> LastName >> GroupID >> AverageGrade >> Benefit;
		FullName = Surname + " " + Name + " " + LastName;
		students.push_back(new Student(FullName, GroupID, AverageGrade, Benefit));
	}

	file.close();
}

void System::DeleteStudent(vector <Student*>::iterator Istudent)
{
	string FIO = (*Istudent)->GetStudentFullName();
	cout << "Вы уверены, что хотите удалить студента " << (*Istudent)->GetStudentFullName() << "?\n1.Да\n2.Нет" << endl;
	int option;
	cin.ignore(cin.rdbuf()->in_avail());
	cin >> noskipws >> option;
	switch (option)
	{
	case 1:
		students.erase(Istudent); 
		cout << "Студент " << FIO << " удален.";
		return;
	case 2:
		cout << "Возвращаемся в главное меню. ";
		return;
	default:
		WrongValue::CatchWrongValue(option);
		cout << "Ввиду неясности ответа изменения не сохранились. Перенаправление в главное меню.";
		return;
	}
}

void System::EditStudent(vector <Student*>::iterator Istudent)
{
	int choice;
	double averagegrade;
	int benefit;
	cout << "\n1. Изменить ФИО" << endl;
	cout << "2. Изменить средний балл" << endl;
	cout << "3. Изменить льготу." << endl;
	cout << "4. В главное меню." << endl;
	cout << "Ввод: ";
	cin.ignore(cin.rdbuf()->in_avail());
	cin >> noskipws >> choice;
	switch (choice)
	{
	case 1:
		(*Istudent)->SetFIO();
		cout << "ФИО студента " << (*Istudent)->GetID() << " изменены на " << (*Istudent)->GetStudentFullName() << endl;
		return;
	case 2:
		while (true)
		{
			try
			{
				cout << "Средний балл:";
				cin.ignore(cin.rdbuf()->in_avail());
				cin >> noskipws >> averagegrade;
				(*Istudent)->GetAccessToScholarship().SetAverageGrade(averagegrade);
				break;
			}
			catch (exception& ex)
			{
				cout << ex.what() << endl;
				continue;
			}
		}
		cout << "Средний балл студента " << (*Istudent)->GetStudentFullName() << " изменен на " << (*Istudent)->GetAccessToScholarship().GetAverageGrade() << endl;
		return;
	case 3:
		while (true)
		{
			try
			{
				cout << "Введите код льготы:";
				cin.ignore(cin.rdbuf()->in_avail());
				cin >> noskipws >> benefit;
				(*Istudent)->GetAccessToScholarship().SetBenefit(benefit);
				break;
			}
			catch (exception& ex)
			{
				cout << ex.what() << endl;
				continue;
			}
		}
		if (benefit == 0)
		{
			cout << "\nСтудент " << (*Istudent)->GetStudentFullName() << " был лишен льготы." << endl;
		}
		else
		{
			cout << "\nСледующая льгота студента " << (*Istudent)->GetStudentFullName() << " была изменена/добавлена:" << (*Istudent)->GetAccessToScholarship().GetBenefit() << endl;
		}
		break;
	default:
		WrongValue::CatchWrongValue(choice);
		cout << "Ввиду неясности ответа переводим вас в главное меню" << endl;
		return;
	}
}

void System::BenefitsInformation()
{
	cout << "Вопросы стипендиального обеспечения регулируются Постановлением Министерства образования от 31.10.2022 № 410 «О вопросах стипендиального обеспечения и осуществления других денежных выплат обучающимся»." << endl;
	cout << "Социальная стипендия назначается лицу, если это лицо относится к одной из категорий:" << endl;
	cout << "1) лица, имеющих детей в возрасте до восемнадцати лет;" << endl;
	cout << "2) военнослужащие срочной военной службы, граждане, проходящие альтернативную службу, военнообязанные, призванные на военные (специальные) сборы, а также суворовцы и воспитанники воинских частей;\n" << endl;
	cout << "3) инвалидов, кроме лиц, инвалидность которых наступила в результате противоправных действий;" << endl;
	cout << "4) детей-сирот и детей, оставшихся без попечения родителей;" << endl;
	cout << "5) именная стипендия лицу, достигшему высоких результатов в олимпиаде;" << endl;
	cout << "6) Именная стипендия лицу, достигшему высоких результатов в научно-исследовательской деятельности;" << endl;
	cout << "7) лиц, имеющих льготы в соответствии со статьями 18-23 Закона Республики Беларусь от 6 января 2009 года «О социальной защите граждан, пострадавших от катастрофы на Чернобыльской АЭС, других радиационных аварий»;" << endl;
	cout << "8) лиц, находящихся в тяжелом материальном положении;" << endl;
}

void System::SortingMenu()
{
	int choice;
	cout << "1. Сортировка по ФИО" << endl;
	cout << "2. Сортировка по среднему баллу" << endl;
	cout << "3. Выход." << endl;
	cout << "Ввод: ";
		cin.ignore(cin.rdbuf()->in_avail());
	cin >> noskipws >> choice;
	switch (choice)
	{
	case 1:
		SortByFIO();
		break;
	case 2:
		SortByAverageGrade();
		break;
	case 3:
		return;
	default:
		WrongValue::CatchWrongValue(choice);
		cout << "Ввиду неясности ответа переводим вас в главное меню";
		return;
	}
	PrintAllStudents();
}

void System::SortByAverageGrade()
{
	int size = students.size();
	int min;
	for (int i = 0; i < size; i++)
	{
		min = i;
		for (int j = i + 1; j < size; j++)
			if (students[j]->GetAccessToScholarship().GetAverageGrade() < students[min]->GetAccessToScholarship().GetAverageGrade())
				min = j;
		swap(students[i], students[min]);
	}
}

void System::SortByFIO()
{
	int size = students.size();
	int min;
	for (int i = 0; i < size; i++)
	{
		min = i;
		for (int j = i + 1; j < size; j++)
			if (students[j]->GetStudentFullName() < students[min]->GetStudentFullName())
				min = j;
		swap(students[i], students[min]);
	}
}

void System::ReWriteauthorizationfile()
{
	string password;
	ofstream file;
	file.open(USERS);
	if (!file.is_open())
		throw FileException(USERS);

	int size = users.size();

	for (int i = 0; i < size - 1; i++)
	{
		password = PasswordDecipher(users[i]->GetPassword(), (CAEASAR_CIPHER * (-1)));
		file << users[i]->GetLogin() << " " << password << " " << users[i]->GetRole() << endl;
	}
	password = PasswordDecipher(users[size - 1]->GetPassword(), (CAEASAR_CIPHER * (-1)));
	file << users[size - 1]->GetLogin() << " " << password << " " << users[size - 1]->GetRole();

	file.close();
}

void System::ReWriteStudentsfile()
{
	ofstream file;
	file.open(STUDENTS);
	if (!file.is_open())
		throw FileException(STUDENTS);

	int size = students.size();

	for (int i = 0; i < size - 1; i++)
	{
		file << students[i]->GetStudentFullName() << " " << students[i]->GetID() << " " << students[i]->GetAccessToScholarship().GetAverageGrade() <<
			" " << students[i]->GetAccessToScholarship().GetBenefitCode() << endl;
	}
	file << students[size - 1]->GetStudentFullName() << " " << students[size - 1]->GetID() << " " << students[size - 1]->GetAccessToScholarship().GetAverageGrade() << 
		  " " << students[size - 1]->GetAccessToScholarship().GetBenefitCode();

	file.close();
}

void System::UserMenu()
{
	int choice;
	string ID;
	while (true)
	{
		cout << "1.Изменить пароль" << endl;
		cout << "2.Просмотр списка студентов" << endl;
		cout << "3.Общая информация по стипендиям." << endl;
		cout << "4.Поиск информации о студенте по студенческому номеру." << endl;
		cout << "5.Выход из программы" << endl;
		cout << "Ввод: ";
		cin.ignore(cin.rdbuf()->in_avail());
		cin >> noskipws >> choice;
		try
		{
			switch (choice)
			{
			case 1:
				(*AuthorizedUser)->SetPassword();
				break;
			case 2:
				PrintAllStudents();
				break;
			case 3:
				BenefitsInformation();
				break;
			case 4:
				cout << "Введите ID студента" << endl;
				cin.ignore(cin.rdbuf()->in_avail());
				cin >> noskipws >> ID;
				PrintStudent(FindByStudentID(ID));
				break;
			case 5:
				ReWriteStudentsfile();
				ReWriteauthorizationfile();
				return;
			default:
				WrongValue::CatchWrongValue(choice);
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

void System::ScholarshipReportFILE()
{
	string password;

	ofstream file;
	file.open(REPORT);
	if (!file.is_open())
		throw FileException(REPORT);

	int size = users.size();

	for (int i = 0; i < size - 1; i++)
	{
		file << students[i]->GetStudentFullName() << ": " << students[i]->GetAccessToScholarship().GetScholarship() << " р." << endl;
	}
	file << students[size-1]->GetStudentFullName() << ": " << students[size-1]->GetAccessToScholarship().GetScholarship() << " р.";

	file.close();
}