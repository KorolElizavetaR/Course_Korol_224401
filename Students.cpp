#include "LogIntoTheSystem.h"

Student::Student(string Full_Name, string GroupID, double averagegrade, int benefit)
{
	this->Full_Name = Full_Name;
	this->GroupID = GroupID;
	(this->scholarship).SetAverageGrade(averagegrade);
	(this->scholarship).SetBenefit(benefit);
}

Student::Student(string Full_Name)
{
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

