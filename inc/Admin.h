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
	Admin() : Korisnik() { }
	void odobriZahtjev(string);
	bool ispisiZahtjeve();
	string getIme();
	string getPrezime();
	string getSifra();
	string getKorisnickoIme();
	string getEmail();
	void izmjenaPodatakaRadnika(std::string tipRadnika);
	void pretrazivanjeNalogaRadnika();
	void pronadjiRadnike(std::string parametar, std::string informacija, std::string tipRadnika);
	bool Ulogovanje() override { return false; }
};
