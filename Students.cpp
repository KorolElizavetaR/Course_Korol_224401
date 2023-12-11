#include "System.h"

Student::Student()
{
	scholarship = new Scholarship();
	Full_Name = "";
	GenerateID();
}

Student::Student(string Full_Name, string GroupID, double averagegrade, int benefit)
{
	scholarship = new Scholarship();
	this->Full_Name = Full_Name;
	this->GroupID = GroupID;
	scholarship->SetAverageGrade(averagegrade);
	scholarship->SetBenefit(benefit);
}

Student::Student(string Full_Name)
{
	scholarship = new Scholarship();
	this->Full_Name = Full_Name;
	GenerateID();
}

void Student::GenerateID()
{
	string c = "";
	int current_length = 0;
	while (current_length++ < ID_LENGTH)
	{
		c += to_string(rand() % 10);
	}
	this->GroupID = c;
}

string Student::GetStudentFullName()
{
	return this->Full_Name;
}

string Student::GetID()
{
	return this->GroupID;
}

void Student::SetFIO()
{
	int count = 0;
	string FIO;
	while (true)
	{
		cout << "ФИО: ";
		count = 0;
		cin.ignore(cin.rdbuf()->in_avail());
		getline(cin, FIO);
		bool NumberInFio = 0;
		for (int i = 0; i < FIO.size(); i++)
		{
			if (FIO[i] == ' ')
			{
				count++;
				continue;
			}
			if (!((FIO[i] >= 'А' && FIO[i] <= 'Я') || (FIO[i] >= 'а' && FIO[i] <= 'я')))
			{
				cout << "В ФИО не могут содержаться цифры, латинские буквы или символы ." << endl << endl;
				NumberInFio = 1;
				break;
			}
		}
		if (NumberInFio == 1)
			continue;
		if (count == 2)
		{
			this->Full_Name = FIO;
			return;
		}
		cout << "Информация введена неверно." << endl << endl;
	}
}

Scholarship& Student::GetAccessToScholarship()
{
	return *scholarship;
}