#ifndef GETCH_H
#define GETCH_H

#include <iostream>
#include "Korisnik.h"
#include "Izuzeci.h"
#include "Klijent.h"
#include <string>
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;

Klijent::Klijent(const string C_Ime, const string C_Prezime,
	const string C_korisnickoIme, const string C_sifra, const string c_email)
	: Korisnik()
{
	Ime = C_Ime;
	Prezime = C_Prezime;
	sifra = C_sifra;
	email = c_email;
	korisnickoIme = C_korisnickoIme;
}

void Klijent::upisFajla(string korisnicko_ime)
{
	if (!provjeriPutanju(putanja))
	{
		return;
	}
	else
	{
		ofstream file(putanja + korisnicko_ime + ".txt", ios::app);
		try {
			if (!file.is_open())
			{
				throw FajlNijeOtvoren();
			}
		}
		catch (const FajlNijeOtvoren& e)
		{
			cout << e.what() << endl;
		}
		file << "Korisnicko Ime:" << korisnicko_ime << "\n";
		file << "Sifra:" << sifra << "\n";
		file << "Ime:" << Ime << "\n";
		file << "Prezime:" << Prezime << "\n";
		file << "Email:" << email << "\n";
		file.flush();
		file.close();
	}
}
void Klijent::ispisFajla(string korisnicko_ime)
{
	//ovdje provjerava da li je klijent u bazi podataka
	if (pronadjiKorisnickoIme(korisnicko_ime)) {

		ifstream out(putanja + korisnicko_ime + ".txt");
		try {
			if (!out.is_open())
			{
				throw FajlNijeOtvoren();
			}
			else
			{
				string K_korisnickoIme, K_sifra, K_Ime, K_prezime, Email;
				getline(out, K_korisnickoIme);
				cout << "Korisnicko Ime: "; ignorisiDvotacku(K_korisnickoIme);
				getline(out, K_sifra);
				cout << "Sifra: ";  ignorisiDvotacku(K_sifra);
				getline(out, K_Ime);
				cout << "Ime: "; ignorisiDvotacku(K_Ime);
				getline(out, K_prezime);
				cout << "Prezime: "; ignorisiDvotacku(K_prezime);
				getline(out, Email);
				cout << "Email: ";  ignorisiDvotacku(Email);
			}
		}
		catch (const FajlNijeOtvoren& e)
		{
			cout << e.what() << endl;
			return;
		}
	}
	else
	{
		cout << "Korisnicko ime nije pronadjeno." << endl;
	}
}

void Klijent::novaRegistracija()
{
	string K_Ime;
	string K_Prezime;
	string K_sifra;
	string K_korisnickoIme;
	string K_email;
	cout << "Ime " << endl;
	while (1)
	{
		cin >> K_Ime;
		try {
			if (!ValidnoIme(K_Ime))
			{
				throw InvalidIme();
			}
			else {
				this->Ime = K_Ime;
				break;
			}
		}
		catch (InvalidIme& e)
		{
			cout << e.what() << endl;
		}
	}
	cout << "Prezime " << endl;
	while (1)
	{
		cin >> K_Prezime;
		try {
			if (!ValidnoPrezime(K_Prezime))
			{
				throw InvalidPrezime();
			}
			else {
				this->Prezime = K_Prezime;
				break;
			}
		}
		catch (InvalidPrezime& e)
		{
			cout << e.what() << endl;
		}
	}
	cout << "Email" << endl;
	while (1) {
		cin >> K_email;
		try {
			if (ValidanEmail(K_email))
			{
				this->email = K_email;
				break;
			}
			else
			{
				throw InvalidEmail();
			}
		}
		catch (const InvalidEmail& e)
		{
			cout << e.what() << endl;
		}
	}
	cout << "Korisnicko Ime" << endl;
	cin >> K_korisnickoIme;
	string result = provjeriKorisnickoIme(K_korisnickoIme);
	korisnickoIme = result;
	cout << "Sifra" << endl;
	int i = 0;
	do {
		K_sifra = UnesiSifru();
		i++;
	} while (i < 10 && !ValidnaSifra(K_sifra));
	this->sifra = K_sifra;
	this->registrovan = true;
	upisFajla(korisnickoIme);
}

bool Klijent::Ulogovanje()
{
	string K_korisnickoIme, K_sifra, rezultat,
		korisnickoIme_rezultat, sifra_rezultat;
	cout << "Unesite korisnicko ime" << endl;
	cin >> K_korisnickoIme;
	if (!pronadjiKorisnickoIme(K_korisnickoIme))
	{
		return false;
	}
	ifstream file(putanja+K_korisnickoIme + ".txt");
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
	cout << "Unesite sifru" << endl;
	K_sifra = UnesiSifru();
	string K_rezultat;
	while (1)
	{
		if (K_sifra != rezultat)
		{
			cout << "Netacna sifra. Molim unesite ponovo." << endl;
			K_sifra = UnesiSifru();
		}
		else
		{
			K_rezultat = vrati_ignorisiDvotacku(korisnickoIme_rezultat);
			cout << "Dobrodosli " << K_rezultat << " nazad!" << endl;
			break;
		}
	}
	this->ulogovan = true;
	return true;
}

void Klijent::prikaziMeni()
{
	int izbor;
	bool kraj = false;
	while (!kraj) {
		cout << "Meni za Klijenta" << endl;
		cout << "1. Odjava" << endl;
		cout << "2. Izlaz." << endl;
		cout << "Unesite izbor: ";
		cin >> izbor;

		switch (izbor) {
		case 1:
			Odjava();
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

bool Klijent::provjeriKlijenta(string korisnickoIme_, string sifra_)
{
	ifstream fajl(putanja + korisnickoIme_ + ".txt");
	if (!fajl.is_open())
	{
		//cout << "Greska pri pristupu datoteke." << endl;
		//return false;
	}
	string linija1, linija2;
	getline(fajl, linija1);
	getline(fajl, linija2);
	string rez1 = vrati_ignorisiDvotacku(linija1);
	string rez2 = vrati_ignorisiDvotacku(linija2);
	int i = 0;
	for (; i < 5; i++)
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
	if (i == 5)
	{
		cout << "Pogresno korisnicko ime." << endl;
		return false;
	}
	i = 0;
	for (; i < 5; i++)
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
	if (i == 5)
	{
		cout << "Pogresna sifra." << endl;
		return false;
	}
	return true;
}

#endif
