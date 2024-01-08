#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "Izuzeci.h"
#include "getChar.h"
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
	string UnesiSifru();

	string provjeriKorisnickoIme(string korisnico_ime);
	string getIme() { return Ime; }
	string getPrezime() { return Prezime; }
	string getSifra() { return sifra; }
	string getKorisnickoIme() { return korisnickoIme; }
	string getEmail() { return email; }
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
protected:
	//f-ja koja ignorise string do pojave ':'
	//Prilikom ispisa iz datoteke-> Username:
	//                              Password:
	// itd. ce ignorisati te ispisati samo username, password...
	void ignorisiDvotacku(string imeDatoteke);
	//ima istu logiku kao i gornja funkcija, s tim što sada vraca rezultat
	string vrati_ignorisiDvotacku(string imeDatoteke);
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
	string putanja = "data\\";
	bool registrovan = false;
	bool ulogovan= false;
	//opciono string userEmail;
};

