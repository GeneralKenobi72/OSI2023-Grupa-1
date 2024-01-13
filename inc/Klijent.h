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
		if (sati > 20 || sati < 8)
		{
			cout << "Vrijeme je van radnog vremena." << endl;
			return false;
		}
		return true;
	}
	void otkaziTermin();
	bool jeValidnoVrijeme(const string& vrijeme) {
		int sati, minute;
        #ifdef _WIN32 
		if (sscanf_s(vrijeme.c_str(), "%d:%d", &sati, &minute) != 2) {
			return false;
		}
        #else 
		if (sscanf(vrijeme.c_str(), "%d:%d", &sati, &minute) != 2) {
			return false;
		}
        #endif

		return sati >= 8 && sati <= 20 && minute >= 0 && minute < 60;
	}
	bool jeValidanDatum(const string& datum) {
		int godina, mjesec, dan;
        #ifdef _WIN32
		if (sscanf_s(datum.c_str(), "%d.%d.%d", &godina, &mjesec, &dan) != 3) {
			return false;
		}
        #else
		if (sscanf(datum.c_str(), "%d.%d.%d", &godina, &mjesec, &dan) != 3) {
			return false;
		}
        #endif

		struct tm unetiDatum = { 0 };
		unetiDatum.tm_year = godina - 1900;
		unetiDatum.tm_mon = mjesec - 1;
		unetiDatum.tm_mday = dan;

		time_t trenutnoVrijeme = time(0);
		struct tm trenutno;
        #ifdef _WIN32
		localtime_s(&trenutno, &trenutnoVrijeme);
        #else
		localtime_r(&trenutnoVrijeme, &trenutno);
        #endif

		time_t unetiDatumTemp = mktime(&unetiDatum);
		time_t trenutnoTemp = mktime(&trenutno);
		if (unetiDatumTemp>= trenutnoTemp)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

};
