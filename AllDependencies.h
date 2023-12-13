#pragma once

#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <algorithm>
#include <math.h> 

const int color = system("color F0");

using namespace std;

namespace WrongValue
{
	template<typename VALUE>
	void CatchWrongValue(VALUE value)
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			throw exception("Неккоректный ввод.");
		}
	}
}