#pragma once

class FileException : public exception
{
	string filename;
public:
	FileException(string filename) :exception("File is not found: ")
	{
		this->filename = filename;
	}
	string GetFileName()
	{
		return filename;
	}
};