#include <iostream>
#include "Korisnik.h"
#include <string>
#include <fstream>
#include <conio.h> 
#include "Klijent.h"
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
	ofstream file(korisnicko_ime + ".txt", ios::app);
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
}

void Klijent::ispisFajla(string korisnicko_ime)
{
	//ovdje provjerava da li je klijent u bazi podataka
	try {
		if (!zauzetKorisnickoIme(korisnicko_ime))
		{
			throw KorisnickoImeNijePronadjeno();
		}
	}
	catch (const KorisnickoImeNijePronadjeno& e)
	{
		cout << e.what() << endl;
	}

	ifstream out(korisnicko_ime + ".txt");
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
				Ime = K_Ime;
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
				Prezime = K_Prezime;
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
				email = K_email;
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
	cout << "Password" << endl;
	int i = 0;
	do {
		K_sifra = UnesiSifru();
		i++;
	} while (i < 10 && !ValidnaSifra(K_sifra));
	sifra = K_sifra;
	upisFajla(korisnickoIme);
}

void Klijent::Ulogovanje()
{
	string K_korisnickoIme, K_sifra, rezultat,
		korisnickoIme_rezultat, sifra_rezultat;
	cout << "Unesite korisnicko ime" << endl;
	cin >> K_korisnickoIme;

	ifstream file(K_korisnickoIme + ".txt");
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
	}
	cout << "Unesite sifru" << endl;
	K_sifra = UnesiSifru();
	while (1)
	{
		if (K_sifra != rezultat)
		{
			cout << "Netacna sifra. Molim unesite ponovo." << endl;
			K_sifra = UnesiSifru();
		}
		else
		{
			cout << "Dobrodosli" << korisnickoIme_rezultat << " nazad!" << endl;
			break;
		}
	}
}
