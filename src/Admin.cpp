#include "Korisnik.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Admin.h"
using namespace std;

Admin::Admin(const string A_firstName, const string A_lastName, const string A_password, const string A_email)
	: Korisnik()
{
	Ime = A_firstName;
	Prezime = A_lastName;
	email = A_email;
	sifra = A_password;
}

inline string Admin::getFirstName() { return Ime; }

inline string Admin::getLasttName() { return Prezime; }

inline string Admin::getPassword() { return sifra; }

inline string Admin::getUserName() { return korisnickoIme; }

inline string Admin::getEmail() { return email; }

