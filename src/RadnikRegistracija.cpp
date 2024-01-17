#ifndef GETCH_H
#define GETCH_H

#include <iostream>
#include "Korisnik.h"
#include "Radnik.h"
#include <string>
#include <fstream>
#include "RadnikRegistracija.h"
#include "Termin.h"
#include <vector>
#include <functional>
#include <AdminRegistracija.h>
using namespace std;

// Vraca podstring od pocetka do pozicije underscore-a
string RadnikR::fajlKorisnickoImeRadnikaT(const string fileIme) {
	size_t pozicija = fileIme.find('_');
	if (pozicija != string::npos) {

		string R_korisnickoIme = fileIme.substr(0, pozicija);
		return R_korisnickoIme;
	}
	else {
		return NULL;
	}
}

void RadnikR::promjenaSifre()
{
	cout << "Unesite trenutnu sifru: " << endl;
	string trenutnaSifra = this->UnesiSifru();
	string korisnickoImeRezultat;
	string sifraRezultat;
	string rezultat;
	ifstream file(putanja + this->getKorisnickoIme() + ".txt");
	try {
		if (!file.is_open())
		{
			throw FajlNijeOtvoren();
		}
		else
		{
			getline(file, korisnickoImeRezultat);
			getline(file, sifraRezultat);
			rezultat = vrati_ignorisiDvotacku(sifraRezultat);
		}
	}
	catch (const FajlNijeOtvoren& e)
	{
		cout << e.what() << endl;
	}
	while (rezultat != trenutnaSifra) {
		cout << "Neispravna sifra. Pokusajte ponovo. " << endl;
		trenutnaSifra = this->UnesiSifru();
	}
	string novaSifraDrugiPut, novaSifra;
	do {
		int i = 0;
		do {
			if(!i) cout << "Unesite novu sifru: " << endl;
			novaSifra = this->UnesiSifru();
			i++;
		} while (!ValidnaSifra(novaSifra));
		cout << "Potvrdite novu sifru ponovnim unosom: " << endl;
		novaSifraDrugiPut = this->UnesiSifru();
	} while (novaSifra != novaSifraDrugiPut);

	posaljiZahtjevZaPromjenuSifre(korisnickoImeRezultat,novaSifra);
	cout << "Zahtjev za promjenu sifre je poslan. Molimo sacekajte odobrenje. " << endl;

}

void RadnikR::posaljiZahtjevZaPromjenuSifre(string kIme, string novaSifra)
{
	kreirajZahtjev(kIme,novaSifra);
}

void RadnikR::kreirajZahtjev(string kIme, string novaSifra) {
	if (!std::filesystem::exists(putanja + putanja2)) std::filesystem::create_directory(putanja + putanja2);
	ofstream file(putanja + putanja2 + kIme + +"Zahtjev" + ".txt");
	file << kIme << endl;
	file << novaSifra << endl;
	file.close();
}

bool RadnikR::provjeriKorisnickoImeRadnikaR(const string korisnickoIme)
{
	ifstream file(putanja+korisnickoIme + ".txt");
	return file.good();
}

//Ovjde se pohranjuju info. o nekom radniku za tehnicki pregled iz postojece datoteke
void RadnikR::postaviInfo(string korisnickoIme)
{
	try {
		if (!provjeriKorisnickoImeRadnikaR(korisnickoIme))
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
	string R_KorisnikcoIme, R_sifra, R_Ime, R_Prezime, R_Email, R_datumRodjenja, R_pozicija;
	getline(out, R_KorisnikcoIme); ignorisiDvotacku(R_KorisnikcoIme);
	korisnickoIme = R_KorisnikcoIme;
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

void RadnikR::ispisFajla(string korisnickoIme)
{
	try {
		if (!provjeriKorisnickoImeRadnikaR(korisnickoIme))
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
		else {
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

bool RadnikR::Ulogovanje()
{
	string R_korisnickoIme, R_sifra, rezultat,
		korisnickoIme_rezultat, sifra_rezultat;
	cout << "Unesite korisnicko ime" << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, R_korisnickoIme);
	int i = 0;
	while (!provjeriKorisnickoImeRadnikaR(R_korisnickoIme) && i<5) {
		cout << "Korisnicko ime nije pronadjeno! Molim unesite ponovo." << endl;
		getline(cin, R_korisnickoIme);
		i++;
	}
	if (i == 5)
	{
		return false;
	}

	ifstream file(putanja+R_korisnickoIme + "_radnikRegistracija.txt");
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
	R_sifra = UnesiSifru();
	string R_rezultat;
	while (1)
	{
		if (R_sifra != rezultat)
		{
			cout << "Netacna sifra. Molim unesite ponovo." << endl;
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

void RadnikR::prikaziMeni()
{
	bool kraj = false;
	Vozilo vozilo;
	while (!kraj) {
		int izbor;
		cout << endl;
		cout << "Meni za Radnika R" << endl;
		cout << "1. Odjava" << endl;
		cout << "2. Promjena sifre" << endl;
		cout << "3. Unos vozila" << endl;
		cout << "4. Pregled zahtjeva za registraciju vozila" << endl;
		cout << "Unesite izbor: ";
		cin >> izbor;

		switch (izbor) {
		case 1:
			Odjava();
			this->ulogovan = false;	
			kraj = true;
			break;
		case 2:
			promjenaSifre();
			break;
		case 3:
			vozilo = unosPodatakaVozila();
			break;
		case 4:
			provjeriZahtjeveZaRegistracije();
			break;
		default:
			cout << "Nepostojeca opcija!" << endl;
			break;
		}
	}
}
void RadnikR::provjeriZahtjeveZaRegistracije() {
	if (std::filesystem::is_empty(putanja + putanjaDoNeregVozila)) {
		cout << "Ne postoje zahtjevi na cekanju" << endl << endl;
		return;
	}
	for (const auto& entry : std::filesystem::directory_iterator(putanja + putanjaDoNeregVozila)) {
		ifstream file(entry.path());
		string kIme;
		char c;
		string info;
		getline(file, kIme);
		getline(file, info);
		//while (cin.get(c) && c != ' ') kIme.push_back(c);
		cout << kIme << endl;
		file.close();
	}
	
	bool flag = false;
	do {
		cout << "Zelite li odobriti neku od registracija: <da/ne> " << endl;
		string odgovor;
		cin >> odgovor;
		if (odgovor == "ne" || odgovor == "Ne") flag = false;
		else if (odgovor == "da" || odgovor == "Da") {
			cout << "Registraciju kojeg korisnika zelite odobriti " << endl;
			string kname;
			cin >> kname;
			odobriRegistraciju(kname);
			flag = true;
		}
		else {
			cout << "Nepostojeca komanda. Pokusajte ponovo. " << endl;
		}
	} while (flag == true);
}

void RadnikR::odobriRegistraciju(string kIme) {
	string s;
	bool flag = false;
	for (const auto& entry : std::filesystem::directory_iterator(putanja + putanjaDoNeregVozila)) {
		ifstream file(entry.path());
		string kkIme;
		char c;
		getline(file, kkIme);
		cout << kIme << kkIme<< endl;
		if (kIme == kkIme) {
			getline(file, s);
			file.close();
			flag = true;
			std::filesystem::remove(entry.path());
			break;
		}
		file.close();
	}
	if (!flag) {
		cout << "Nepostojeci korisnik. " << endl;
		return;
	}
	if (!std::filesystem::exists(putanja + putanjaDoRegVozila)) std::filesystem::create_directory(putanja + putanjaDoRegVozila);

	ofstream file1(putanja + putanjaDoRegVozila + kIme + ".txt");
	file1 << kIme << endl;
	file1 << s << endl;
	file1.close();
}


bool RadnikR::provjeriRadnikaRegistracija(string korisnickoIme_, string sifra_)
{
	ifstream fajl(putanja + korisnickoIme_ + "_radnikRegistracija.txt");
	if (!fajl.is_open())
	{
		//cout << "Greska pri pristupu datoteke RR." << endl;
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

Vozilo RadnikR::unosPodatakaVozila()
{
	string marka, model, registarskiBroj,kIme, godinaProizvodnje;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	Vozilo vozilo;
	cout << "Unesite korisnicko ime ciji se podaci vozila unose." << endl;
	getline(cin, kIme);

	string putanjaDatoteke =putanja+ kIme + ".txt";
	if (filesystem::exists(putanjaDatoteke))
	{
		vozilo.korisnickoIme = kIme;
		do {
			cout << "Unesite marku vozila klijenta(npr. ImeVozila)" << kIme << ": ";
			getline(cin, marka);
		} while (!ValidnoVozilo(marka));
		vozilo.marka = marka;
		do {
			cout << "Unesite model vozila klijenta (bez '-' npr. mk6) " << kIme << ": ";
			getline(cin, model);
		} while (!ValidnoVozilo(model));
		vozilo.model = model;
		do {
			cout << "Unesite godinu proizvodnje vozila klijenta(npr. 2000) " << kIme << ": ";
			getline(cin, godinaProizvodnje);
		} while (!ValidnaGodina(godinaProizvodnje));
		vozilo.godinaProizvodnje = godinaProizvodnje;
		do {
			cout << "Unesite registarski broj vozila klijenta(npr. ABC-123) " << kIme << ": ";
			getline(cin, registarskiBroj);
		} while (!ValidanRegistracijskiBroj(registarskiBroj));
		vozilo.regBroj = registarskiBroj;
		
		string podaciVozila = marka + " " + model + " " + godinaProizvodnje + " " + registarskiBroj;
		
		ifstream fajlVozila(putanja + "vozila.txt");
		string tempLine;
		bool postoji = false;
		while (getline(fajlVozila, tempLine)) {
			if (tempLine.find(kIme + " " + podaciVozila) != string::npos) {
				postoji = true;

				break;
			}
		}
		fajlVozila.close();

		if (!postoji) {
			ofstream file(putanja + "vozila.txt", ios::app);
			ofstream fajlKazneIRacuni(putanja + "KazneIRacuni.txt", ios::app);
			try {
				if (!file.is_open()) {
					throw FajlNijeOtvoren();
				}
				else {
					file << kIme << " " << podaciVozila << "\n";
				}
			}
			catch (const FajlNijeOtvoren& e) {
				cout << e.what() << endl;
			}
			file.close();
		}
		else {
			cout << "Podaci o vozilu su vec upisani." << endl;
		}

		return vozilo;
	}
	else
	{
		cout << "Korisnik sa korisnickim imenom: " << kIme << " nije pronadjen." << endl;
		return Vozilo();
	}
}


#endif
