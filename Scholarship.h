#pragma once
#define BASE_SCHOLARSHIP 125.27
#include "AllDependencies.h"

class Scholarship
{
	double scholarship;
	double Grade_Persantage;
	double Benefits_Persantage;

	Scholarship()
	{
		scholarship = BASE_SCHOLARSHIP;
	}
	Scholarship(double average_grade, double benefit)
	{
		scholarship = BASE_SCHOLARSHIP * (1 + GetPersantageByGrade(average_grade) + GetPersantageOfBenefit(benefit));
	}
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
		throw exception("Íåêîğğåêòíûé ââîä ñğåäíåé îöåíêè.");
	}
	double GetPersantageOfBenefit(int benefit)
	{
		switch (benefit)
		{
		case 0:
			//îòñóñòâèå ëüãîòû
			return 0;
		case 1:
			// 1. Ñòóäåíò ñ ğåáåíêîì
			return 0.4;
		case 2:
			// 2. Âîåííèê
			return 0.3;
		case 3:
			// 3. Èíâàëèä
			return 0.35;
		case 4:
			// 4. Ñèğîòà
			return 0.5;
		case 5:
			// 5. Îëèìïèàäíèê
			return 0.25;
		case 6:
			// 6. Çàùèùåííàÿ íàó÷íî - èññëåäîâàòåëüñêàÿ ğàáîòà
			return 0.3;
		case 7:
			// 7. ×ÀİÑ æåğòâû
			return 0.3;
		case 8:
			// 8. Ìàëîèìóùèé ñòóäåíò
			return 0.5;
		default:
			throw exception("Òàêîãî êîäà ëüãîòû íåò.");
		}
	}
};