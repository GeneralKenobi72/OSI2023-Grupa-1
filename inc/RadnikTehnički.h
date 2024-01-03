#pragma once
#include <iostream>
#include "Korisnik.h"
#include "Radnik.h"
#include <string>
#include <fstream>
using namespace std;

// RadnikT-za tehnièki pregled
class RadnikT : public Radnik {
private:
	// Vraæa podstring od poèetka do pozicije underscore-a
	string fajlKorisnickoImeRadnikaT(const string fileIme);
	bool provjeriKorisnickoImeRadnikaT(const string korisnickoIme);
public:

	RadnikT() noexcept : Radnik() {}

	//Ovjde se pohranjuju info. o nekom radniku za tehnièki pregled
	void postaviInfo(string korisnickoIme);

	void ispisFajla(string korisnicko_ime);

	//Ovjde je radnik vec registrovan na sistem te je samo potrebno ulogovanje 
	void Ulogovanje();
};