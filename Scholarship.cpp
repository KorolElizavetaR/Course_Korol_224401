#include "System.h"

double Scholarship::GetPersantageByGrade(int average_grade)
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
	throw exception("������������ ���� ������� ������.");
}

double Scholarship::GetPersantageOfBenefit(int benefit)
{
	switch (benefit)
	{
	case 0:
		return 0;
	case 1:
		return 0.4;
	case 2:
		return 0.3;
	case 3:
		return 0.35;
	case 4:
		return 0.5;
	case 5:
		return 0.25;
	case 6:
		return 0.3;
	case 7:
		return 0.3;
	case 8:
		return 0.5;
	default:
		throw exception("������ ���� ������ ���.");
	}
}

int Scholarship::GetBenefitCode()
{
	return this->Benefit;
}

void Scholarship::SetBenefit(int Benefit)
{
	
	WrongValue::CatchWrongValue(Benefit);
	if (Benefit > 8 && averagegrade < 0)
		throw exception("������������ ���� ���� ������.");
	this->Benefit = Benefit;
	RecountScholarship();
}

void Scholarship::SetAverageGrade(double averagegrade)
{
	if (averagegrade > 10 && averagegrade <= 0)
		throw exception("������������ ���� ������� ������.");
	this->averagegrade = averagegrade;
	RecountScholarship();
}

void Scholarship::RecountScholarship()
{
	scholarship = BASE_SCHOLARSHIP * (1 + GetPersantageByGrade(averagegrade) + GetPersantageOfBenefit(Benefit));
}
Scholarship::Scholarship()
{
	scholarship = BASE_SCHOLARSHIP;
	averagegrade = 0;
	Benefit = 0;
}
Scholarship::Scholarship(double average_grade, double benefit)
{
	scholarship = BASE_SCHOLARSHIP * (1 + GetPersantageByGrade(average_grade) + GetPersantageOfBenefit(benefit));
}
double Scholarship::GetScholarship()
{
	return floor(this->scholarship*10)/10;
}
double Scholarship::GetAverageGrade()
{
	return this->averagegrade;
}
string Scholarship::GetBenefit()
{
	switch (Benefit)
	{
	case 0:
		return "������ ���";
	case 1:
		return "������� � ��������";
	case 2:
		return "�������";
	case 3:
		return "�������";
	case 4:
		return "������";
	case 5:
		return "�����������";
	case 6:
		return "���������� ������ - ����������������� ������";
	case 7:
		return "���� ������";
	case 8:
		return "���������� �������";
	default:
		throw exception("������ ���� ������ ���.");
	}
}