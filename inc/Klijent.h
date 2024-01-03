#pragma once
#include <iostream>
#include "Korisnik.h"
#include <string>
#include <fstream>
#include <conio.h> 
using namespace std;

class Klijent : public Korisnik {
private:
	//funkcija koja za ispis iz datoteke ignorise naziv do pojave : 
	// tj. "Username:","Password:" itd.
	//funckija za unos sifre, gdje se pri unosom umjesto sifre prikazuje *
public:
	Klijent() noexcept : Korisnik() {}

	Klijent(const string C_Ime, const string C_Prezime,
		const string C_korisnickoIme, const string C_sifra, const string c_email);

	void upisFajla(string korisnicko_ime);
	void ispisFajla(string korisnicko_ime);
	void novaRegistracija();
	void Ulogovanje();
};