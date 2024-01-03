#pragma once
#include "Korisnik.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Admin : public Korisnik {
protected:
	bool registrovan = true;
public:
	Admin(const string A_firstName, const string A_lastName, const string A_password, const string A_email);
	Admin() : Korisnik() {}
	string getFirstName();
	string getLasttName();
	string getPassword();
	string getUserName();
	string getEmail();

};