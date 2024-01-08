#pragma once
#include <iostream>
#include "Korisnik.h"
#include <string>
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;

class Klijent : public Korisnik {
private:
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
	Klijent() noexcept : Korisnik() {}

	Klijent(const string C_Ime, const string C_Prezime,
		const string C_korisnickoIme, const string C_sifra, const string c_email);
	Klijent(bool ulogovan) noexcept : Korisnik() { this->ulogovan = ulogovan; }
	void upisFajla(string korisnicko_ime);
	void ispisFajla(string korisnicko_ime);
	void novaRegistracija();
	bool Ulogovanje() override;
	void prikaziMeni() override;
};
