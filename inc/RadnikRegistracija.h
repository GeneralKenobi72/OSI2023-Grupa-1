#pragma once
#include <iostream>
#include "Korisnik.h"
#include "Radnik.h"
#include <string>
#include <fstream>
using namespace std;

class RadnikR : public Radnik {
private:
	// Vra�a podstring od po�etka do pozicije underscore-a
	string fajlKorisnickoImeRadnikaT(const string fileIme);
	bool provjeriKorisnickoImeRadnikaT(const string korisnickoIme);
public:
	RadnikR() noexcept : Radnik() {}

	//Ovjde se pohranjuju info. o nekom radniku za tehni�ki pregled iz postojece datoteke
	void postaviInfo(string korisnickoIme);

	void ispisFajla(string korisnickoIme);

	void Ulogovanje();

};