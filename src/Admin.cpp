#include "Korisnik.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Admin.h"
using namespace std;

Admin::Admin(const string A_Ime, const string A_Prezime, const string A_sifra, const string A_email)
	: Korisnik()
{
	Ime = A_Ime;
	Prezime = A_Prezime;
	email = A_email;
	sifra = A_sifra;
}

inline string Admin::getIme() { return Ime; }

inline string Admin::getPrezime() { return Prezime; }

inline string Admin::getSifra() { return sifra; }

inline string Admin::getKorisnickoIme() { return korisnickoIme; }

inline string Admin::getEmail() { return email; }

