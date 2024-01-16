#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "Izuzeci.h"
#include "getChar.h"
#include <cstdlib>
#include "Termin.h"
#include <chrono>
#include <algorithm>
#include <ctime>
#include <sstream>
using namespace std;
#include <filesystem>
namespace fs = std::filesystem;

class Korisnik {
public:
	Korisnik() noexcept {}
	Korisnik(const string korisnickoIme, const string sifra) noexcept : korisnickoIme(korisnickoIme), sifra(sifra) {}

	//  moze se koristiti samo jedna za provjeru prvog i zadnjeg imena
	// ali zbog preglednosti su definisane zasebno
	bool ValidnoIme(string ime);
	bool ValidnoPrezime(string prezime);
	bool ValidanEmail(string email);
	bool ValidnaSifra(string sifra);

	//f-ja provjerava preko imena fajla da li je korisnicko ime pronadjeno 
	//ako datoteka postoji vraca true, inače false
	bool pronadjiKorisnickoIme(const string korisnicko_ime);

	//f-ja koju ce dijeliti svi ucesnici za unos sifre
	//Unosom se svaki put pojavljuje *
	//npr. Enter password:******
	static string UnesiSifru();

	string provjeriKorisnickoIme(string korisnico_ime);
	string getIme() { return Ime; }
	string getPrezime() { return Prezime; }
	string getSifra() { return sifra; }
	string getKorisnickoIme() { return korisnickoIme; }
	string getEmail() { return email; }

	void setKorisnickoIme(string korisnickoIme) { this->korisnickoIme = korisnickoIme; }

	bool provjeriPutanju(string putanja);
	virtual bool Ulogovanje() = 0;
	virtual void prikaziMeni() = 0;
	void postaviKorisnickoIme(string korisnickoIme) {
		this->korisnickoIme = korisnickoIme;
	}
	void postaviIme(string Ime) { this->Ime = Ime; }
	void postaviPrezime(string Prezime) { this->Prezime = Prezime; }
	void postaviSifra(string sifra) { this->sifra = sifra; }
	void postaviEmail(string email) { this->email = email; }
	virtual Korisnik* provjeri(string, string) = 0;
	static string vrati_ignorisiDvotacku(string imeDatoteke);
	#ifdef _WIN32
	string putanja = "data\\";
	string putanja2 = "zahtjevi\\";
	#else
	string putanja2 = "zahtjevi/";
	string putanja = "data/";
	#endif
	bool ulogovan= false;
	//provjera Marke vozila i Modela vozila
	bool ValidnoVozilo(const string& vozilo) {
		if (vozilo.empty()) {
			cout << "Nije validno." << endl;
			return false;
		}
		for (char znak : vozilo) {
			if (!isalnum(znak)) {
				cout << "Nije validno." << endl;
				return false;
			}
		}
		return true;
	}
	bool ValidnaGodina(const string& godinaStr) {
		if (godinaStr.length() == 4) {
			for (char c : godinaStr) {
				if (!isdigit(c)) {
					cout << "Nije validno." << endl;
					return false;
				}
			}
			int godina = std::stoi(godinaStr);
			return (godina >= 1900 && godina <= 2024);
		}
		return false;
	}
	bool ValidanRegistracijskiBroj(const string& regBroj) {
		if (regBroj.length() < 5 || regBroj.length() > 10) {
			cout << "Nije validno: duzina nije u validnom opsegu." << endl;
			return false;
		}

		int brojCrtica = 0;
		for (size_t i = 0; i < regBroj.length(); ++i) {
			if (regBroj[i] == '-') {
				if (i == 0 || i == regBroj.length() - 1 || brojCrtica > 0) {
					cout << "Nije validno: neispravna pozicija crtice." << endl;
					return false;
				}
				brojCrtica++;
			}
			else if (!isalnum(regBroj[i])) {
				cout << "Nije validno: sadrzi neispravne karaktere." << endl;
				return false;
			}
		}

		return true;
	}

protected:
	//f-ja koja ignorise string do pojave ':'
	//Prilikom ispisa iz datoteke-> Username:
	//                              Password:
	// itd. ce ignorisati te ispisati samo username, password...
	void ignorisiDvotacku(string imeDatoteke);
	//ima istu logiku kao i gornja funkcija, s tim što sada vraca rezultat
	//int userID;
	virtual bool provjeriUlogovanje() = 0;
	void Odjava()
	{
			this->korisnickoIme = "";
			this->sifra = "";
			this->ulogovan = false;
			cout << "Uspjesno ste odjavljeni." << endl;
	}
	string korisnickoIme;
	string Ime, Prezime;
	string email;
	string sifra;
	bool registrovan = false;
	//opciono string userEmail;
};

