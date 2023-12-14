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
	//�������� �� ������������� ������
	//�������� �� ������������ ������ � ������
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
	unsigned char p;
	int attempts = 6;
	while (--attempts != 0)
	{
		password = "";
		cout << "������� �����: ";
		cin >> login;
		cout << "������� ������: ";
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

vector<shared_ptr<User>>::iterator System::FindByLogin(string login)
{
	for (vector<shared_ptr<User>>::iterator Iuser = users.begin(); Iuser != users.end(); Iuser++)
	{
		if ((*Iuser)->GetLogin() == login)
		{
			return Iuser;
		}
	}
	throw exception("������������ �� ������. ");
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
	throw exception("������� �� ������.");
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
			case 5:
				PrintAllStudents();
				break;
			case 6:
				AddStudent();
				break;
			case 7:
				cout << "������� ID ��������:";
				cin.ignore(cin.rdbuf()->in_avail());
				cin >> ID;
				EditStudent(FindByStudentID(ID));
				break;
			case 8:
				cout << "������� ID ��������: ";
				cin.ignore(cin.rdbuf()->in_avail());
				cin >> ID;
				DeleteStudent(FindByStudentID(ID));
				break;
			case 9:
				BenefitsInformation();
				break;
			case 10:
				cout << "������� ID ��������: ";
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
		cout << "������������ " << user->GetLogin() << " ��� ����� " << user->GetStringRole() << " ��� ��������." << endl;
		return;
	case '2':
		return;
	default:
		WrongValue::CatchWrongValue(option);
		cout << "����� ��������� ������ ��������� �� �����������. ��������������� � ������� ����.";
		return;
	}
}

void System::EditAccount()
{
	string login;
	string password;
	int choice;
	vector<shared_ptr<User>>::iterator Current_User;
	cout << "������� ����� ��������, ���������� � ������� ����� ��������:";
	cin.ignore(cin.rdbuf()->in_avail());
	cin >> noskipws >> login;
	try
	{
		Current_User = FindByLogin(login);
		cout << "����� ���������� ��������� ��������?" << endl;
		cout << "1.�����\n2.������\n3.��������� � ������� ����.\n\t����: ";
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
			WrongValue::CatchWrongValue(choice);
			return;
		}
	}
	catch (exception& ex)
	{
		cout << "����� �� ������." << endl;
		return;
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
			cout << "����� ������������ " << login << " ������ �� " << (*Current_User)->GetLogin() << endl;
		}
		else
		{
			cout << "������ ������������ " << login << " ������ � " << password << " �� " << (*Current_User)->GetPassword() << endl;
		}
		return;
	case 2:
		(*Current_User)->SetLoginWITHOUTRESTRICTION(login);
		(*Current_User)->SetPasswordWITHOUTRESTRICTION(password);
		return;
	default:
		WrongValue::CatchWrongValue(option);
		cout << "����� ��������� ������ ��������� �� �����������. ��������������� � ������� ����." << endl;
		return;
	}
}

void System::PrintAllAccounts()
{
	cout << setw(40) << left << "�����" << setw(40) << "������" << setw(40) << "����" << endl;
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
			AuthorizedUser = FindByLogin(Currentuser_login);
			cout << "������������ " << login << " ������.";
			return;
		case 2:
			cout << "������������ � ������� ����. ";
			return;
		default:
			WrongValue::CatchWrongValue(option);
			cout << "����� ��������� ������ ��������� �� �����������. ��������������� � ������� ����.";
			return;
		}
	}
	catch (exception& ex)
	{
		cout << ex.what() << ". ������� � ������� ����.";
	}
}

void System::PrintStudent(vector<Student*>::iterator student)
{
	cout << "��� ��������:" << (*student)->GetStudentFullName() << "\n\tID:" << (*student)->GetID()
		<< "\n\t������� ���������:" << (*student)->GetAccessToScholarship().GetScholarship()
		<< "\n\t������� ����:" << (*student)->GetAccessToScholarship().GetAverageGrade()
		<< "\n\t������:" << (*student)->GetAccessToScholarship().GetBenefit() << endl;
}

void System::PrintAllStudents()
{
	for (auto Istudent = students.begin(); Istudent != students.end(); Istudent++)
	{
		PrintStudent(Istudent);
		/*cout << "��� ��������:" << student->GetStudentFullName() << "\n\tID:" << student->GetID()
			<< "\n\t������� ���������:" << student->GetAccessToScholarship().GetScholarship()
			<< "\n\t������� ����:" << student->GetAccessToScholarship().GetAverageGrade()
			<< "\n\t������:" << student->GetAccessToScholarship().GetBenefit() << endl;*/
	}
}

void System::AddStudent()
{
	Student *st = new Student();
	st->SetFIO();
	cout << "ID ��������:" << st->GetID() << endl;
	cout << "��������� ���������� ����������� � ������� �������������� ��������.";
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
	cout << "�� �������, ��� ������ ������� �������� " << (*Istudent)->GetStudentFullName() << "?\n1.��\n2.���" << endl;
	int option;
	cin.ignore(cin.rdbuf()->in_avail());
	cin >> noskipws >> option;
	switch (option)
	{
	case 1:
		students.erase(Istudent); 
		cout << "������� " << FIO << " ������.";
		return;
	case 2:
		cout << "������������ � ������� ����. ";
		return;
	default:
		WrongValue::CatchWrongValue(option);
		cout << "����� ��������� ������ ��������� �� �����������. ��������������� � ������� ����.";
		return;
	}
}

void System::EditStudent(vector <Student*>::iterator Istudent)
{
	int choice;
	double averagegrade;
	int benefit;
	cout << "\n1. �������� ���" << endl;
	cout << "2. �������� ������� ����" << endl;
	cout << "3. �������� ������." << endl;
	cout << "4. � ������� ����." << endl;
	cout << "����: ";
	cin.ignore(cin.rdbuf()->in_avail());
	cin >> noskipws >> choice;
	switch (choice)
	{
	case 1:
		(*Istudent)->SetFIO();
		cout << "��� �������� " << (*Istudent)->GetID() << " �������� �� " << (*Istudent)->GetStudentFullName() << endl;
		return;
	case 2:
		while (true)
		{
			try
			{
				cout << "������� ����:";
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
		cout << "������� ���� �������� " << (*Istudent)->GetStudentFullName() << " ������� �� " << (*Istudent)->GetAccessToScholarship().GetAverageGrade() << endl;
		return;
	case 3:
		while (true)
		{
			try
			{
				cout << "������� ��� ������:";
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
			cout << "\n������� " << (*Istudent)->GetStudentFullName() << " ��� ����� ������." << endl;
		}
		else
		{
			cout << "\n��������� ������ �������� " << (*Istudent)->GetStudentFullName() << " ���� ��������/���������:" << (*Istudent)->GetAccessToScholarship().GetBenefit() << endl;
		}
		break;
	default:
		WrongValue::CatchWrongValue(choice);
		cout << "����� ��������� ������ ��������� ��� � ������� ����" << endl;
		return;
	}
}

void System::BenefitsInformation()
{
	cout << "������� ��������������� ����������� ������������ �������������� ������������ ����������� �� 31.10.2022 � 410 �� �������� ��������������� ����������� � ������������� ������ �������� ������ ������������." << endl;
	cout << "���������� ��������� ����������� ����, ���� ��� ���� ��������� � ����� �� ���������:" << endl;
	cout << "1) ����, ������� ����� � �������� �� ������������ ���;" << endl;
	cout << "2) �������������� ������� ������� ������, ��������, ���������� �������������� ������, ���������������, ���������� �� ������� (�����������) �����, � ����� ��������� � ������������ �������� ������;\n" << endl;
	cout << "3) ���������, ����� ���, ������������ ������� ��������� � ���������� �������������� ��������;" << endl;
	cout << "4) �����-����� � �����, ���������� ��� ��������� ���������;" << endl;
	cout << "5) ������� ��������� ����, ���������� ������� ����������� � ���������;" << endl;
	cout << "6) ������� ��������� ����, ���������� ������� ����������� � ������-����������������� ������������;" << endl;
	cout << "7) ���, ������� ������ � ������������ �� �������� 18-23 ������ ���������� �������� �� 6 ������ 2009 ���� �� ���������� ������ �������, ������������ �� ���������� �� ������������� ���, ������ ������������ ������;" << endl;
	cout << "8) ���, ����������� � ������� ������������ ���������;" << endl;
}

void System::SortingMenu()
{
	int choice;
	cout << "1. ���������� �� ���" << endl;
	cout << "2. ���������� �� �������� �����" << endl;
	cout << "3. �����." << endl;
	cout << "����: ";
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
		cout << "����� ��������� ������ ��������� ��� � ������� ����";
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
		cout << "1.�������� ������" << endl;
		cout << "2.�������� ������ ���������" << endl;
		cout << "3.����� ���������� �� ����������." << endl;
		cout << "4.����� ���������� � �������� �� ������������� ������." << endl;
		cout << "5.����� �� ���������" << endl;
		cout << "����: ";
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
				cout << "������� ID ��������" << endl;
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
		file << students[i]->GetStudentFullName() << ": " << students[i]->GetAccessToScholarship().GetScholarship() << " �." << endl;
	}
	file << students[size-1]->GetStudentFullName() << ": " << students[size-1]->GetAccessToScholarship().GetScholarship() << " �.";

	file.close();
}