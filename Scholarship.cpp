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
		//��������� ������
		return 0;
	case 1:
		// 1. ������� � ��������
		return 0.4;
	case 2:
		// 2. �������
		return 0.3;
	case 3:
		// 3. �������
		return 0.35;
	case 4:
		// 4. ������
		return 0.5;
	case 5:
		// 5. �����������
		return 0.25;
	case 6:
		// 6. ���������� ������-����������������� ������
		return 0.3;
	case 7:
		// 7. ���� ������
		return 0.3;
	case 8:
		// 8. ���������� �������
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