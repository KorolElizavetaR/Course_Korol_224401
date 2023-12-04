#include <iostream>
#include <Windows.h>
#include "LogIntoTheSystem.h"

using namespace std;

void main()
{
    setlocale(LC_ALL, "Rus");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    try
    {
        LogIntoTheSystem authorization;
    }
    catch (exception& ex)
    {
        cout << ex.what() << endl;
    }
}