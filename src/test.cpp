#include "RadnikRegistracija.h"
#include "RadnikTehnicki.h"
#include "Radnik.h"
#include "Klijent.h"
#include "Korisnik.h"
#include "AdminTehnicki.h"
#include "AdminRegistracija.h"
#include <filesystem>
#include <fstream>
#include <functional>
#include "Termin.h"
namespace fs = std::filesystem;
using namespace std;
#include <string>
#ifdef _WIN32
string putanja = "data\\";
#else
string putanja = "data/";
#endif

Korisnik* koSeLoguje(string korisnickoIme) {
	string Ime, Prezime, Sifra, Email, s;
	ifstream file(putanja+korisnickoIme+".txt");
	try {
		if (!file.is_open())
		{
			throw FajlNijeOtvoren();
		}
		else
		{
			getline(file, s);
			getline(file, Sifra);
			Sifra = Korisnik::vrati_ignorisiDvotacku(Sifra);
			getline(file, Ime);
			Ime = Korisnik::vrati_ignorisiDvotacku(Ime);
			getline(file, Prezime);
			Prezime = Korisnik::vrati_ignorisiDvotacku(Prezime);
			getline(file, Email);
			Email = Korisnik::vrati_ignorisiDvotacku(Email);
			getline(file, s);
			s = Korisnik::vrati_ignorisiDvotacku(s);
		}
	}
	catch (const FajlNijeOtvoren& e)
	{
		cout << e.what() << endl;
		return nullptr;
	}
	if(s == "klijent"){
		Klijent* k = new Klijent(Ime, Prezime, korisnickoIme, Sifra, Email);
		k->ulogovan = true;
		return k;
	} else if(s == "adminT") {
		AdminTehnicki* a = new AdminTehnicki(Ime,Prezime,korisnickoIme,Sifra,Email);
		a->ulogovan = true;
		return a;
	} else if(s == "adminR") {
		AdminRegistracija* a = new AdminRegistracija(Ime,Prezime,korisnickoIme,Sifra,Email);
		a->ulogovan = true;
		return a;
	} else if(s == "radnikT") {
		RadnikT* r = new RadnikT(Ime,Prezime,korisnickoIme,Sifra,Email);
		r->ulogovan = true;
		return r;
	} else if(s == "radnikR") {
		RadnikR* r = new RadnikR(Ime,Prezime,korisnickoIme,Sifra,Email);
		r->ulogovan = true;
		return r;
	}
	return nullptr;
}

bool provjeriKorisnickoIme(string s) {
	ifstream file(putanja+s+".txt");
	return file.good();
}

bool ulogujSe() {
	string korisnickoImeUnos, sifraUnos,
		   korisnickoIme, sifra;
	do {
		std::cout << "Unesite korisnicko ime:";
		std::cin >> korisnickoImeUnos;
	} while(!provjeriKorisnickoIme(korisnickoImeUnos));

	ifstream file(putanja+korisnickoImeUnos+".txt");
	try {
		if (!file.is_open())
		{
			throw FajlNijeOtvoren();
		}
		else
		{
			getline(file, korisnickoIme);
			getline(file, sifra);
			sifra = Korisnik::vrati_ignorisiDvotacku(sifra);
		}
	}
	catch (const FajlNijeOtvoren& e)
	{
		cout << e.what() << endl;
		return false;
	}
	cout << "Unesite sifru" << endl;
	sifraUnos = Korisnik::UnesiSifru();
	while (1)
	{
		if (sifraUnos != sifra)
		{
			cout << "Netacna sifra. Molim unesite ponovo." << endl;
			sifraUnos = Korisnik::UnesiSifru();
		}
		else
		{
			Korisnik* k = koSeLoguje(korisnickoImeUnos);
			cout << "\nDobrodosli " << korisnickoImeUnos << " nazad!" << endl;
			k->prikaziMeni();
			delete(k);
			break;
		}
	}
	return true;
}


int pocetniMeni() {
	std::cout << "====================================\n";
	std::cout << "Softver za registraciju vozila\n";
	std::cout << "====================================\n";
	std::cout << "Opcije:\n";
	std::cout << "1: Registracija\n";
	std::cout << "2: Log in\n";
	std::cout << "3: Kraj rada\n";
	std::cout << "Unos: ";
	int opcija;
	std::cin >> opcija;
	return opcija;
}

string unesi_sifru(){
    string novaSifra;
	char ch;
	ch = getChar();
	std::cout << std::flush;
#ifdef _WIN32
	while (ch!=13) {  // Provjeri za ENTER key ASCII 13
#else
	while (ch!='\n') {
#endif
		if (ch != 8) {   // Provjeri za backspace ASCII 8
			novaSifra.push_back(ch);
			cout << '*' << std::flush;
		}
		else if (!novaSifra.empty()) {
			novaSifra.pop_back();
			cout << "\b \b";  // Obrisi zadnju * (asterisk)
		}
		ch = getChar();
	}
	cout << endl;
	return novaSifra;
}

int main()
{
	while(true) {
		int opcija = pocetniMeni();
		if(opcija == 1) {
			Klijent k(true);
			k.novaRegistracija();	
			k.prikaziMeni();
		}
		if(opcija == 2)
			ulogujSe();
		if(opcija == 3){
			return 0;
		}
	}
}

