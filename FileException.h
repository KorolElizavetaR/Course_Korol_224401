#pragma once
#include <iostream>
#include <string>

using namespace std;

class FileException : public exception
{
	const char* filename;
public:
	FileException(const char* filename) :exception("File is not found: ")
	{
		this->filename = filename;
	}
	string GetFileName()
	{
		return filename;
	}
};