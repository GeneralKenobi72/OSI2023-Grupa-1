#pragma once
#include <iostream>
#include <exception>
using namespace std;
class FileNotOpen : public exception {
public:
	virtual const char* what() const noexcept override final
	{
		return "Error! File cannot open.";
	}
};
class InvalidEmail : public exception {
public:
	virtual const char* what() const noexcept override final
	{
		return "Invalid email input.";
	}
};
class InvalidFName : public exception {
public:
	virtual const char* what() const noexcept override final
	{
		return "First name not valid.";
	}
};
class InvalidLName : public exception {
public:
	virtual const char* what() const noexcept override final
	{
		return "last name not valid. ";
	}
};
class InvalidPassword : public exception {
public:
	virtual const char* what() const noexcept override final
	{
		return "Password not valid. Please enter again. ";
	}
};
class UserNameNotFound : public exception {
public:
	virtual const char* what() const noexcept override final
	{
		return "Username not found. ";
	}
};