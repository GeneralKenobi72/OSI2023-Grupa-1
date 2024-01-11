#pragma once
#include "Korisnik.h"
#include "Admin.h"
#include <iostream>
#include <fstream>
#include <string>
#include "RadnikRegistracija.h"
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;

class AdminRegistracija : public Admin
{
private:
	RadnikR radnikRegistracija;
public:
	AdminRegistracija(std::string Ime, std::string Prezime, std::string korisnickoIme, std::string sifra, std::string email) noexcept
		: Admin(Ime, Prezime, korisnickoIme, sifra, email) {}
	AdminRegistracija() noexcept : Admin() {}
	AdminRegistracija(bool ulogovan) noexcept : Admin() { this->ulogovan = ulogovan; }

	bool Ulogovanje() override;


	//Funkcija za pregled svih radnika za registraciju gdje se ispisuju korisnicka imena
	//dodatno mozemo imati funckiju gdje na osnovu tih imena pristupamo datoteci za jos detaljnije informacija 
	//kao sto su email, ime, prezime itd. sto se radi u f-ji isipiInfoRadnika
	void PregledNalogaRadnika();

	void dodajRadnikaRegistracija();
	void obrisiRadnikaRegistracija();
	void ispisInfoRadnika(string userNameRadnikR);
	void prikaziMeni() override;
	bool provjeriAdminRegistracija(string korisnickoIme, string sifra);
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
	Korisnik* provjeri(string korisnickoIme, string sifra) override
	{
		if (this->provjeriAdminRegistracija(korisnickoIme, sifra)) {
			return new AdminRegistracija(true);
		}
		else {
			//cout << "Niste ovlasteni administrator za tehnicki pregled i ne mozete se prijaviti kao administrator." << endl;
			return nullptr;
		}
	}
private:
	bool provjeriKorisnickoImeAdminaR(const string username);
};
