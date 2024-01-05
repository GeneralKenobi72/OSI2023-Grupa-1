#pragma once
#include "Korisnik.h"
#include "Admin.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Izuzeci.h"
#include <filesystem>
#include "RadnikTehnicki.h"
namespace fs = std::filesystem;
using namespace std;

class AdminTehnicki : public Admin
{
private:
	RadnikT radnikTehnicki;

public:
	AdminTehnicki(std::string Ime, std::string Prezime, std::string sifra, std::string email) noexcept
		: Admin(Ime, Prezime, sifra, email) {}
	AdminTehnicki() noexcept : Admin() {}

	void Prijava();
	//Ovdje treba jos doraditi kod dodajRadnikaTehnicki()
	void dodajRadnikaTehnicki();
	void obrisiRadnikaTehnicki();
	//Funkcija za pregled svih radnika za tehnicki pregled gdje se ispisuju korisnicka imena
	// <filesystem> omogucava rad sa fajl sistemom, pruzajuci funkcionalnosti za manipulaciju fajlovima
	// prolazi kroz sve fajlove u trenutnom direktorijumu ("./"), entry.path().filename().string() uzima putanju trenutnog fajla u iteraciji,
	// zatim dohvata samo ime fajla
	//dodatno mozemo imati funckiju gdje na osnovu tih imena pristupamo datoteci za jos detaljnije informacija 
	//kao sto su email, ime, prezime itd. sto se radi u f-ji isipiInfoRadnika
	void PregledNalogaRadnika();
	void ispisInfoRadnika(string userNameRadnikT);
private:

	bool provjeriKorisnickoImeAdminT(const string username);
};
