#pragma once
#include <iostream>
#include "Korisnik.h"
#include <string>
#include <fstream>
using namespace std;

class Radnik : public Korisnik {
protected:
	bool registrovan = true;
	string datumRodjenja;
	string pozicija;
public:
	Radnik() noexcept : Korisnik() {}
	Radnik(std::string ime, std::string prezime, std::string korisnicko,
			std::string Sifra, std::string Email) {
		Ime = ime;
		Prezime = prezime;
		korisnickoIme = korisnicko;
		email = Email;
		sifra = Sifra;
	}
	void postaviDatumRodjenja(string datumRodjenja) { this->datumRodjenja = datumRodjenja; }
};
