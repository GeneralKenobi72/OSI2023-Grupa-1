#pragma once
#include <iostream>
#include "Korisnik.h"
#include "Radnik.h"
#include <string>
#include <fstream>
#include <functional>
using namespace std;

// RadnikT-za tehnicki pregled
class RadnikT : public Radnik {
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
	RadnikT() noexcept : Radnik() {}
	RadnikT(function<void()> func) : Radnik(), dodajRadnikaFunc(func) {}
	//Ovjde se pohranjuju info. o nekom radniku za tehnicki pregled
	RadnikT(bool ulogovan) noexcept : Radnik() { this->ulogovan = ulogovan; }
	void postaviInfo(string korisnickoIme);

	void ispisFajla(string korisnicko_ime);

	//Ovjde je radnik vec registrovan na sistem te je samo potrebno ulogovanje 
	bool Ulogovanje() override;
	void prikaziMeni() override;
	bool provjeriKorisnickoImeRadnikaT(const string korisnickoIme);
	bool provjeriRadnikaTehnicki(string korisnickoIme_, string sifra_);
	void postaviPozicija() { pozicija = "Radnik za Tehnicki Pregled"; }
	string vratiPoziciju(){ return pozicija; }
	void setRegistraciju() { this->registrovan = true; }
	Korisnik* provjeri(string korisnickoIme, string sifra) override
	{
		if (this->provjeriRadnikaTehnicki(korisnickoIme, sifra)) {
			return new RadnikT(true);
		}
		else {
			cout << "Izgleda da nemate nalog." << endl;
			cout << "Nova registracija? (da/Da)" << endl;
			string da;
			cin >> da;
			if (da == "da" || da == "Da")
			{
				cout << "Prikaz Meni" << endl;
				return new RadnikT(dodajRadnikaFunc);
			}
			else
			{
				return nullptr;
			}
		}
	}
};