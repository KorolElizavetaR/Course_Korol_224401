#pragma once
#define USERS "Users.txt"
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class LogIntoTheSystem
{
	vector <User*> users;

	LogIntoTheSystem()
	{
		if (Fillauthorizationfile())
			EmergencyAdminFile();
	}

	bool Fillauthorizationfile()
	{
		ifstream file;
		file.open(USERS);
		if (!file.is_open() || file.peek() == EOF)
			return true;

		string login;
		string password;
		bool role;
			
		while (!file.eof())
		{
			file >> login >> password >> role;
			if (role == false)
				users.push_back(new User(login, password));
			else if (role == true)
				users.push_back(new Admin(login, password));
		} 

		file.close();
		return false;
	}

	void EmergencyAdminFile()
	{
		cout << "ќшибка при открытии файла. ¬ведите данные об администраторе." << endl;
		ofstream file;
		file.open(USERS, ofstream::app);
		Admin user;
		user.SetLogin(users);
		file << login << " " << password << " " << "1";
		users.push_back(User(login, password, 1));
		file.close();
	}
		
public:

	LogIntoTheSystem()
	{
		Fillauthorizationfile();
	}
};

