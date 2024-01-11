#pragma once
#include "Korisnik.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Admin : public Korisnik {
protected:
	bool registrovan = true;
	bool podaciValidni = true;
	//bool provjeriUlogovanje() override { return false; }
public:
	Admin(const string, const string, const string, const string, const string);
	Admin() : Korisnik() {}
	string getIme();
	string getPrezime();
	string getSifra();
	string getKorisnickoIme();
	string getEmail();
	bool Ulogovanje() override { return false; }
};
