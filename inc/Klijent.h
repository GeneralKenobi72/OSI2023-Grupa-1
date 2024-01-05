#pragma once
#include <iostream>
#include "Korisnik.h"
#include <string>
#include <fstream>
using namespace std;

class Klijent : public Korisnik {
private:
public:
	Klijent() noexcept : Korisnik() {}

	Klijent(const string C_Ime, const string C_Prezime,
		const string C_korisnickoIme, const string C_sifra, const string c_email);

	void upisFajla(string korisnicko_ime);
	void ispisFajla(string korisnicko_ime);
	void novaRegistracija();
	void Ulogovanje();
};
