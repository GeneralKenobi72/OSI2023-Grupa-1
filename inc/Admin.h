#pragma once
#include "User.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Admin : public User {
public:
	Admin(const string A_firstName, const string A_lastName, const string A_password, const string A_email)
		: User()
	{
	    first_name= A_firstName ;
		last_name= A_lastName ;
		email = A_email;
		password = A_password;
	}
	Admin() : User () {}
	string getFirstName() { return first_name; }
	string getLasttName() { return last_name; }
	string getPassword() { return password; }
	string getUserName() { return userName; }
	string getEmail() { return email; }
	
};