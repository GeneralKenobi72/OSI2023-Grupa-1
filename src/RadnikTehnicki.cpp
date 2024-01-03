#include <iostream>
#include "Korisnik.h"
#include "Radnik.h"
#include <string>
#include <fstream>
#include "RadnikTehnicki.h"
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
	ifstream file(korisnickoIme + "_radnikTehnicki.txt");
	return file.good();
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

	ifstream out(korisnickoIme + "_radnikTehnicki.txt");
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
	ifstream out(korisnicko_ime + "_radnikTehnicki.txt");
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
void RadnikT::Ulogovanje()
{
	string R_korisnickoIme, R_sifra, rezultat,
		korisnickoIme_rezultat, sifra_rezultat;
	cout << "Unesite korisnicko ime." << endl;
	cin >> R_korisnickoIme;

	while (!provjeriKorisnickoImeRadnikaT(R_korisnickoIme)) {
		cout << "Korisnicko ime nije pronadjeno! Molim unesite ponovo." << endl;
		cin >> R_korisnickoIme;
	}
	ifstream file(R_korisnickoIme + "_radnikTehnicki.txt");
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
			cout << "Dobrodosli " << R_rezultat << " nazad!" << endl;
			break;
		}
	}
}