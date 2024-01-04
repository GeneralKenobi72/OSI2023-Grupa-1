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
	Admin(const string, const string, const string, const string);
	Admin() : Korisnik() {}
	string getIme();
	string getPrezime();
	string getSifra();
	string getKorisnickoIme();
	string getEmail();

};
