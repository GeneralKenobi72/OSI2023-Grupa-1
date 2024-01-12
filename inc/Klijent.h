#pragma once
#include <iostream>
#include "Korisnik.h"
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>
namespace fs = std::filesystem;
using namespace std;

class Klijent : public Korisnik {
private:
	string statusTermina;
	string markaVozila;
	string modelVozila;
	string godinaProizvodnje;
	string registarskiBroj;
public:
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
	Klijent() noexcept : Korisnik() {}
	Klijent(const string C_Ime, const string C_Prezime,
		const string C_korisnickoIme, const string C_sifra, const string c_email);
	Klijent(bool ulogovan) noexcept : Korisnik() { this->ulogovan = ulogovan; }
	void upisFajla(string korisnicko_ime);
	void ispisFajla(string korisnicko_ime);
	void novaRegistracija();
	bool Ulogovanje() override;
	void prikaziMeni() override;
	bool provjeriKlijenta(string korisnickoIme, string sifra);
	Korisnik* provjeri(string korisnickoIme, string sifra) override
	{
		if (this->provjeriKlijenta(korisnickoIme, sifra)) {
			return new Klijent(true);
		}
		else {
			cout << "Izgleda da nemate nalog." << endl;
			cout << "Nova registracija? (da/Da)" << endl;
			string da;
			cin >> da;
			if (da == "da" || da == "Da")
			{
				cout << "Prikaz Meni" << endl;
				return new Klijent();
			}
			else
			{
				return nullptr;
			}
		}
	}
	void unesiPodatke();
	void odaberiTermin();
	void setStatusTermin(string status) { this->statusTermina = status; }
	void setMarkaVozila(string markaVozila) { this->markaVozila = markaVozila; }
	void setModelVozila(string modelVozila) { this->modelVozila = modelVozila; }
	void setGodinaProizvodnje(string godina) { this->godinaProizvodnje = godina; }
	void setRegistarskiBroj(string broj) { this->registarskiBroj = broj; }

	string getMarkaVozila() { return this->markaVozila; }
	string getModelVozila() { return this->modelVozila; }
	string getGodinaProizvodnje() { return this->godinaProizvodnje; }
	string getRegistarskiBroj() { return this->registarskiBroj; }

	int provjeriTermin(const string& datum, const string& vrijeme);
	void upisiTerminUFajl(const string&, const string&, const string&);

	int vrijemeUMinute(const string& vrijeme) {
		int sati, minute;
		char dvotacka;

		istringstream stream(vrijeme);
		stream >> sati >> dvotacka >> minute;

		return sati * 60 + minute;
	}
	bool jeVrijemeURadnomVremenu(const string& vrijeme) {
		int sati, minute;
		char dvotacka;
		stringstream ss(vrijeme);
		ss >> sati >> dvotacka >> minute;

		// nE moze se zakazivati poslije 20:00
		if (sati > 20 || sati<8)
		{
			cout << "Vrijeme je van radnog vremena." << endl;
			return false;
		}
		return true;
	}
	void otkaziTermin();
};
