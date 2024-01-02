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
	AdminRegistracija() noexcept : Admin() {}

	void Prijava();

	void obrisiRadnikaRegistracija();

	//Funkcija za pregled svih radnika za registraciju gdje se ispisuju korisnicka imena
	//dodatno mozemo imati funckiju gdje na osnovu tih imena pristupamo datoteci za jos detaljnije informacija 
	//kao sto su email, ime, prezime itd. sto se radi u f-ji isipiInfoRadnika
	void PregledNalogaRadnika();

	void ispisInfoRadnika(string userNameRadnikR);
private:

	bool provjeriKorisnickoImeAdminaR(const string username);
};
