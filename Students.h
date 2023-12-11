#pragma once
#define ID_LENGTH 6
#define BASE_SCHOLARSHIP 125.90
#include "AllDependencies.h"
#include "System.h"

class Scholarship
{
	double scholarship;
	double averagegrade;
	int Benefit;

	double GetPersantageByGrade(int average_grade);
	double GetPersantageOfBenefit(int benefit);
public:
	int GetBenefitCode();
	void SetBenefit(int Benefit);
	void SetAverageGrade(double averagegrade);
	void RecountScholarship();
	Scholarship();
	Scholarship(double average_grade, double benefit);
	double GetScholarship();
	double GetAverageGrade();
	string GetBenefit();
};

class Student
{
	Scholarship *scholarship;
	string Full_Name;
	string GroupID;
public:
	Student(string Full_Name, string GroupID, double averagegrade, int benefit);

	Student(string Full_Name);

	Student();

	void GenerateID();

	string GetStudentFullName();

	string GetID();

	Scholarship& GetAccessToScholarship();

	void SetFIO();
};