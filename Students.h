#pragma once
#define ID_LENGTH 6
#include "AllDependencies.h"
#include "LogIntoTheSystem.h"

class Student
{
	friend Scholarship;

	Scholarship scholarship;
	string Full_Name;
	string GroupID; //onlydigits 
public:
	Student(string Full_Name, string GroupID, double averagegrade, int benefit)
	{
		this->Full_Name = Full_Name;
		this->GroupID = GroupID;
		(this->scholarship).SetAverageGrade(averagegrade);
		(this->scholarship).SetBenefit(averagegrade);
	}

	Student(string Full_Name)
	{
		this->Full_Name = Full_Name;
		GroupID = GenerateID();
	}

	string GenerateID()
	{
		string c = "";
		int current_length = 0;
		while (current_length++ < ID_LENGTH)
		{
			c += to_string(rand() % 10);
		}
		return c;
	}
};

class Scholarship
{
	double scholarship;
	double averagegrade;
	int Benefit;

	double GetPersantageByGrade(int average_grade)
	{
		if (average_grade > 0 && average_grade < 7)
		{
			return 0;
		}
		else if (average_grade >= 7 && average_grade < 8)
		{
			return 0.15;
		}
		else if (average_grade >= 8 && average_grade < 9.5)
		{
			return 0.2;
		}
		else if (average_grade >= 9.5 && average_grade < 10)
		{
			return 0.3;
		}
		throw exception("Некорректный ввод средней оценки.");
	}
	double GetPersantageOfBenefit(int benefit)
	{
		switch (benefit)
		{
		case 0:
			//отсуствие льготы
			return 0;
		case 1:
			// 1. Студент с ребенком
			return 0.4;
		case 2:
			// 2. Военник
			return 0.3;
		case 3:
			// 3. Инвалид
			return 0.35;
		case 4:
			// 4. Сирота
			return 0.5;
		case 5:
			// 5. Олимпиадник
			return 0.25;
		case 6:
			// 6. Защищенная научно - исследовательская работа
			return 0.3;
		case 7:
			// 7. ЧАЭС жертвы
			return 0.3;
		case 8:
			// 8. Малоимущий студент
			return 0.5;
		default:
			throw exception("Такого кода льготы нет.");
		}
	}
public:
	void SetBenefit(int Benefit)
	{
		this->Benefit = Benefit;
	}
	void SetAverageGrade(double averagegrade)
	{
		this->averagegrade = averagegrade;
	}
	Scholarship()
	{
		scholarship = BASE_SCHOLARSHIP;
	}
	Scholarship(double average_grade, double benefit)
	{
		scholarship = BASE_SCHOLARSHIP * (1 + GetPersantageByGrade(average_grade) + GetPersantageOfBenefit(benefit));
	}
};