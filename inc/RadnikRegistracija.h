#pragma once
#include <iostream>
#include "Korisnik.h"
#include "Radnik.h"
#include <string>
#include <fstream>
#include <functional>
using namespace std;

class RadnikR : public Radnik {
private:
	// Vraca podstring od pocetka do pozicije underscore-a
	string fajlKorisnickoImeRadnikaT(const string fileIme);
	function<void()> dodajRadnikaFunc;
	bool provjeriUlogovanje() override { 
		if (ulogovan == false)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	
public:
	RadnikR() noexcept : Radnik() {}
	RadnikR(function<void()> func) : Radnik(), dodajRadnikaFunc(func) {}
	RadnikR(bool ulogovan) noexcept : Radnik() { this->ulogovan = ulogovan; }
	//Ovjde se pohranjuju info. o nekom radniku za tehnicki pregled iz postojece datoteke
	void postaviInfo(string korisnickoIme);

	void ispisFajla(string korisnickoIme);

	bool Ulogovanje() override;
	void prikaziMeni() override;
	bool provjeriKorisnickoImeRadnikaR(const string korisnickoIme);
	bool provjeriRadnikaRegistracija(string korisnickoIme_, string sifra_);
	void postaviPozicija() { pozicija = "Radnik za Registraciju";  }
	string vratiPoziciju() { return pozicija; }
	void setRegistraciju() { this->registrovan = true; }
};
