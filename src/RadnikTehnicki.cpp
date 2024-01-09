#ifndef GETCH_H
#define GETCH_H

#include <iostream>
#include "Korisnik.h"
#include "Radnik.h"
#include <string>
#include <fstream>
#include "RadnikTehnicki.h"
#include <functional>
using namespace std;

// Vraca podstring od pocetka do pozicije underscore-a
string RadnikT::fajlKorisnickoImeRadnikaT(const string fileIme) {
	size_t pozicija = fileIme.find('_');
	if (pozicija != string::npos) {

		string R_korisnickoIme = fileIme.substr(0, pozicija);
		return R_korisnickoIme;
	}
	else {
		return NULL;
	}
}

bool RadnikT::provjeriKorisnickoImeRadnikaT(const string korisnickoIme)
{
	ifstream file(putanja+korisnickoIme + ".txt");
	return file.good();
}

bool RadnikT::provjeriRadnikaTehnicki(string korisnickoIme_, string sifra_)
{
	ifstream fajl(putanja + korisnickoIme_ + ".txt");
	if (!fajl.is_open())
	{
		//cout << "Greska pri pristupu datoteke RT." << endl;
		return false;
	}
	string linija1, linija2;
	getline(fajl, linija1);
	getline(fajl, linija2);
	string rez1 = vrati_ignorisiDvotacku(linija1);
	string rez2 = vrati_ignorisiDvotacku(linija2);
	int i = 0;
	for (; i < 3; i++)
	{
		if (rez1 != korisnickoIme_)
		{
			cout << "Unesite korisnicko ime ponovo." << endl;
			cin >> korisnickoIme_;
		}
		else
		{
			break;
		}
	}
	if (i == 3)
	{
		cout << "Pogresno korisnicko ime." << endl;
		return false;
	}
	i = 0;
	for (; i < 3; i++)
	{
		if (rez2 != sifra_)
		{
			cout << "Unesite sifru ponovo. " << endl;
			sifra_ = UnesiSifru();
		}
		else
		{
			break;
		}
	}
	if (i == 3)
	{
		cout << "Pogresna sifra." << endl;
		return false;
	}
	return true;
}


//Ovjde se pohranjuju info. o nekom radniku za tehnicki pregled
void RadnikT::postaviInfo(string korisnickoIme)
{
	try {
		if (!provjeriKorisnickoImeRadnikaT(korisnickoIme))
		{
			throw KorisnickoImeNijePronadjeno();
		}
	}
	catch (const KorisnickoImeNijePronadjeno& e)
	{
		cout << e.what() << endl;
	}

	ifstream out(putanja+korisnickoIme + ".txt");
	try {
		if (!out.is_open())
		{
			throw FajlNijeOtvoren();
		}
	}
	catch (const FajlNijeOtvoren& e)
	{
		cout << e.what() << endl;
	}
	string R_korisnickoIme, R_sifra, R_Ime, R_Prezime, R_Email, R_datumRodjenja, R_pozicija;
	getline(out, R_korisnickoIme); ignorisiDvotacku(R_korisnickoIme);
	korisnickoIme = R_korisnickoIme;
	getline(out, R_sifra); ignorisiDvotacku(R_sifra);
	sifra = R_sifra;
	getline(out, R_Ime);  ignorisiDvotacku(R_Ime);
	Ime = R_Ime;
	getline(out, R_Prezime);  ignorisiDvotacku(R_Prezime);
	Prezime = R_Prezime;
	getline(out, R_Email); ignorisiDvotacku(R_Email);
	email = R_Email;
	getline(out, R_datumRodjenja); ignorisiDvotacku(R_datumRodjenja);
	datumRodjenja = R_datumRodjenja;
	getline(out, R_pozicija); ignorisiDvotacku(R_pozicija);
	pozicija = R_pozicija;
}

void RadnikT::ispisFajla(string korisnicko_ime)
{
	try {
		if (!provjeriKorisnickoImeRadnikaT(korisnicko_ime))
		{
			throw KorisnickoImeNijePronadjeno();
		}
	}
	catch (const KorisnickoImeNijePronadjeno& e)
	{
		cout << e.what() << endl;
	}
	ifstream out(putanja+korisnicko_ime + ".txt");
	try {
		if (!out.is_open())
		{
			throw FajlNijeOtvoren();
		}
		else
		{
			string R_korisnickoIme, R_sifra, R_Ime, R_Prezime, R_Email, R_datumRodjenja, R_pozicija;
			getline(out, R_korisnickoIme);
			cout << "Korisnicko ime (iz baze podataka): "; ignorisiDvotacku(R_korisnickoIme);
			getline(out, R_sifra);
			cout << "Sifra (iz baze podataka): "; ignorisiDvotacku(R_sifra);
			getline(out, R_Ime);
			cout << "Ime (iz baze podataka): "; ignorisiDvotacku(R_Ime);
			getline(out, R_Prezime);
			cout << "Prezime (iz baze podataka): "; ignorisiDvotacku(R_Prezime);
			getline(out, R_Email);
			cout << "Email (iz baze podataka): ";  ignorisiDvotacku(R_Email);
			getline(out, R_datumRodjenja);
			cout << "Datum rodjenja (iz baze podataka): "; ignorisiDvotacku(R_datumRodjenja);
			getline(out, R_pozicija);
			cout << "Pozicija (iz baze podataka): "; ignorisiDvotacku(R_pozicija);
		}
	}
	catch (const FajlNijeOtvoren& e)
	{
		cout << e.what() << endl;
	}
}

//Ovjde je radnik vec registrovan na sistem te je samo potrebno ulogovanje 
bool RadnikT::Ulogovanje()
{
	string R_korisnickoIme, R_sifra, rezultat,
		korisnickoIme_rezultat, sifra_rezultat;
	cout << "Unesite korisnicko ime." << endl;
	cin >> R_korisnickoIme;
	bool nastavi = true;
	int i = 0;
	while (!provjeriKorisnickoImeRadnikaT(R_korisnickoIme) && i<2) {
		cout << "Korisnicko ime nije pronadjeno! Molim unesite ponovo." << endl;
		cin >> R_korisnickoIme;
		i++;
	}
	if (i == 2)
	{
		return false;
	}
	ifstream file(putanja+R_korisnickoIme + ".txt");
	try {
		if (!file.is_open())
		{
			throw FajlNijeOtvoren();
		}
		else
		{
			getline(file, korisnickoIme_rezultat);
			getline(file, sifra_rezultat);
			rezultat = vrati_ignorisiDvotacku(sifra_rezultat);
		}
	}
	catch (const FajlNijeOtvoren& e)
	{
		cout << e.what() << endl;
		return false;
	}
	cout << "Unesite sifru." << endl;
	R_sifra = UnesiSifru();
	string R_rezultat;
	while (1)
	{
		if (R_sifra != rezultat)
		{
			cout << "Netacna sifra! Unesite ponovo." << endl;
			R_sifra = UnesiSifru();
		}
		else
		{
			R_rezultat = vrati_ignorisiDvotacku(korisnickoIme_rezultat);
			korisnickoIme = R_rezultat;
			sifra = R_sifra;
			cout << "Dobrodosli " << korisnickoIme << " nazad!" << endl;
			break;
		}
	}
	ulogovan = true;
	return true;
}

void RadnikT::prikaziMeni()
{
	bool kraj = false;
	while (!kraj) {
		int izbor;
		cout << endl;
		cout << "Meni za Radnika T" << endl;
		cout << "1. Odjava" << endl;
		cout << "2. Izlaz" << endl;
		cout << "Unesite izbor: ";
		cin >> izbor;

		switch (izbor) {
		case 1:
			Odjava();
			kraj = true;
			break;
		case 2:
			kraj = true;
			break;
		default:
			cout << "Nepostojeca opcija!" << endl;
			break;
		}
	}
}

#endif
