#pragma once
#include <iostream>
#include "Korisnik.h"
#include "Radnik.h"
#include <string>
#include "Termin.h"
#include <fstream>
#include <vector>
#include <functional>
#include <ctime>
#include <random>
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
	RadnikR(std::string ime, std::string prezime, std::string korisnicko,
			std::string sifra, std::string email) : Radnik(ime,prezime,korisnicko,sifra,email) {};
	//Ovjde se pohranjuju info. o nekom radniku za tehnicki pregled iz postojece datoteke
	void postaviInfo(string korisnickoIme);
	void odobriRegistraciju(string kIme);
	void prikaziSveRegistracije();
	void ispisFajla(string korisnickoIme);
	void kreirajZahtjev(string, string);
	bool postojiKorisnikUZahtjevimaZaRegistraciju(string);//dodano
	void provjeriZahtjeveZaRegistracije();
	void posaljiZahtjevZaPromjenuSifre(string kIme, string novaSifra);
	void promjenaSifre() override;
	bool Ulogovanje() override;
	void prikaziMeni() override;
	void pregledKazniIRacuna();
	bool provjeriKorisnickoImeRadnikaR(const string korisnickoIme);
	bool provjeriRadnikaRegistracija(string korisnickoIme_, string sifra_);
	void postaviPozicija() { pozicija = "Radnik za Registraciju";  }
	string vratiPoziciju() { return pozicija; }
	void setRegistraciju() { this->registrovan = true; }
	Korisnik* provjeri(string korisnickoIme, string sifra) override
	{
		if (this->provjeriRadnikaRegistracija(korisnickoIme, sifra)) {
			return new RadnikR(true);
		}
		else {
			cout << "Izgleda da nemate nalog." << endl;
			cout << "Nova registracija? (da/Da)" << endl;
			string da;
			cin >> da;
			if (da == "da" || da == "Da")
			{
				cout << "Prikaz Meni" << endl;
				return new RadnikR(dodajRadnikaFunc);
			}
			else
			{
				return nullptr;
			}
		}
	}
	Vozilo unosPodatakaVozila();
	string generisiRegistracioneTablice() {
		// dakle tablice su oblika ABC-TD012, dakle samo ta jedna '-'
		string tablice;
		random_device rd; // ovdje cemo generisati neki nasumican broj
		mt19937 gen(rd());
		uniform_int_distribution<> distribucijaSlova(65, 90);
		uniform_int_distribution<> distribucijaBrojeva(0, 9);
		// ovdje cemo dodati neka 3 nasumicna slova
		for (int i = 0; i < 3; ++i) {
			char slovo = distribucijaSlova(gen);
			tablice.push_back(slovo);
		}
		tablice.push_back('-');

		for (int i = 0; i < 3; ++i) {
			char broj = '0' + distribucijaBrojeva(gen); //pretvara u char
			tablice.push_back(broj);
		}

		return tablice;
	}
};
