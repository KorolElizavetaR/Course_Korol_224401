#include "AllDependencies.h"
#include "LogIntoTheSystem.h"


void main()
{
    setlocale(LC_ALL, "Rus");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    srand(time(NULL));
    try
    {
        System authorization;
        authorization.Menu();
    }
    catch (exception& ex)
    {
        cout << ex.what() << endl;
    }
}