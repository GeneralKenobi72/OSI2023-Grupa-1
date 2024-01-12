#ifndef GETCH_H
#define GETCH_H

#include <iostream>
#include "Korisnik.h"
#include "Radnik.h"
#include <string>
#include <fstream>
#include "RadnikTehnicki.h"
#include <functional>
#include <vector>
#include "Termin.h"

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

void RadnikT::unesiPodatke(const string& korisnickoImeKlijenta)
{
	if (!provjeriUlogovanje())
	{
		cout << "Niste ulogovani." << endl;
		return;
	}
	string markaVozila, modelVozila, registarskiBroj;
	string godinaProizvodnje;

	ofstream file(putanja + korisnickoImeKlijenta + ".txt", ios::app);
	try {
		if (!file.is_open())
		{
			throw FajlNijeOtvoren();
		}
		else
		{
			cout << "Unesite marku vozila klijenta " << korisnickoImeKlijenta << ": ";
			cin >> markaVozila;
			cout << "Unesite model vozila klijenta " << korisnickoImeKlijenta << ": ";
			cin >> modelVozila;
			cout << "Unesite godinu proizvodnje vozila klijenta " << korisnickoImeKlijenta << ": ";
			cin >> godinaProizvodnje;
			cout << "Unesite registarski broj vozila klijenta " << korisnickoImeKlijenta << ": ";
			cin >> registarskiBroj;
			string korisnicko_ime = getKorisnickoIme();

			file << "Model vozila:" << modelVozila << "\n";
			file << "Marka vozila:" << markaVozila << "\n";
			file << "Godina proizvodnje:" << godinaProizvodnje << "\n";
			file << "Registarski broj vozila:" << registarskiBroj << "\n";
		}
	}
	catch (const FajlNijeOtvoren& e)
	{
		cout << e.what() << endl;
	}

}

void RadnikT::odaberiTermin()
{
	if (!provjeriUlogovanje())
	{
		cout << "Niste ulogovani." << endl;
		return;
	}
	ifstream file1(putanja + "Termini.txt");
	if (!file1)
	{
		cout << "Error kod otvaranja Termina" << endl;
		return;
	}
	cout << "Unesite korisnicko ime klijenta" << endl;
	string korisnickoImeKlijenta;
	cin >> korisnickoImeKlijenta;
	string fileKorisnickoIme, fileDatum, fileVrijeme;
	if (pronadjiKorisnickoIme(korisnickoImeKlijenta)==false)
	{
		cout << "Korisnik ne postoji. " << endl;
		return;
	}
	while (file1 >> fileKorisnickoIme >> fileDatum >> fileVrijeme) {
		if (fileKorisnickoIme == korisnickoImeKlijenta) {
			cout << "Izgleda da klijent ima zakazni termin." << endl;
			return;
		}
	}
	unesiPodatke(korisnickoImeKlijenta);
	string datum, vrijeme;

	int statusTermina;
	do {
		cout << "Unesite datum (godina/mjesec/dan): ";
		cin >> datum;
		cout << "Unesite vrijeme (SS:MM): ";
		cin >> vrijeme;

		if (!jeVrijemeURadnomVremenu(vrijeme)) {
			cout << "Uneseno vrijeme nije unutar radnog vremena. Molimo unesite vrijeme izmeðu 08:00 i 20:00." << endl;
			continue;
		}

		statusTermina = provjeriTermin(datum, vrijeme);

		if (statusTermina == -2) {
			cout << "Vrijeme termina je zauzeto. Molim unesite ponovo." << endl;
		}
		else if (statusTermina == -3) {
			cout << "Svi termini za ovaj datum su zauzeti. Molimo izaberite drugi datum." << endl;
		}
		else if (statusTermina == -1)
		{
			cout << "Vas termin je zakazan." << endl;
			break;
		}

	} while (statusTermina != 1);

	//Termin noviTermin(korisnicko_ime, datum, vrijeme, reg_broj);
	upisiTerminUFajl(korisnickoImeKlijenta, datum, vrijeme);
}

int RadnikT::provjeriTermin(const string& datum, const string& vrijeme)
{
	ifstream file(putanja + "Termini.txt");
	string fileKorisnickoIme, fileDatum, fileVrijeme;
	int brojTermina = 0;
	while (file >> fileKorisnickoIme >> fileDatum >> fileVrijeme) {

		if (fileKorisnickoIme == getKorisnickoIme())
		{
			file.close();
			return -1;
		}
		else if (fileDatum == datum) {
			brojTermina++;
			//ovdje se gleda razlika vremena da bude veca od 30 minuta, kako bi se mogao termin zakazati
			int razlikaUMinutama = abs(vrijemeUMinute(vrijeme) - vrijemeUMinute(fileVrijeme));
			if (razlikaUMinutama < 30) { // Ako je razlika manja od 30 minuta, termin je zauzet
				file.close();
				return -2;
			}
		}

	}
	if (brojTermina >= 24) {
		file.close();
		return -3;
	}

	file.close();
	cout << "Uspjesno zakazan termin." << endl;
	return 1;
}

void RadnikT::upisiTerminUFajl(const string& kIme, const string& datum, const string& vrijeme)
{
	ofstream file(putanja + "Termini.txt", ios::app);
	try {
		if (!file.is_open())
		{
			throw FajlNijeOtvoren();
		}
		else
		{
			file << kIme << " " << datum << " " << vrijeme << "\n";
		}
	}
	catch (const FajlNijeOtvoren& e)
	{
		cout << e.what() << endl;
	}
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
	this->ulogovan = true;
	return true;
}
void RadnikT::otkazivanjeTermina()
{
	if (!provjeriUlogovanje())
	{
		cout << "Niste ulogovani." << endl;
		return;
	}
	ifstream file1(putanja + "Termini.txt");
	if (!file1)
	{
		cout << "Error kod otvaranja Termina" << endl;
		return;
	}
	cout << "Unesite korisnicko ime klijenta ciji se termin otkazuje." << endl;
	string korisnickoImeKlijenta;
	cin >> korisnickoImeKlijenta;
	string fileKorisnickoIme, fileDatum, fileVrijeme;
	if (pronadjiKorisnickoIme(korisnickoImeKlijenta) == false)
	{
		cout << "Klijent ne postoji. " << endl;
		return;
	}
	while (file1 >> fileKorisnickoIme >> fileDatum >> fileVrijeme) {
		if (fileKorisnickoIme != korisnickoImeKlijenta) {
			cout <<"Klijenta nije moguce pronaci u listi termina." << endl;
			return;
		}
	}
	string line;
	vector<string> lines;

	bool found = false;

	// Cita datoteku i sprema sve linije osim one koja se treba obrisati
	while (getline(file1, line)) {
		if (line.find(korisnickoIme) == string::npos) {
			lines.push_back(line);
		}
		else {
			found = true;
		}
	}

	file1.close();

	if (!found) {
		cout << "Termin nije pronadjen." << endl;
		return;
	}
	ofstream outFile(putanja + "Termini.txt");
	for (const auto& savedLine : lines) {
		outFile << savedLine << endl;
	}
	cout << "Termin uspjesno otkazan." << endl;
}

void RadnikT::izmjeniTermin()
{
	Termin t;
	vector<Termin> termini=t.ucitajTermine();
	string korisnickoIme, datum, vrijeme;

	cout << "Unesite korisnicko ime klijenta za izmjenu termina "<<endl;
	cin >> korisnickoIme;
	bool terminPronadjen = false;
	for (auto& termin : termini) {
		if (termin.korisnickoIme == korisnickoIme) {
			terminPronadjen = true;
			int statusTermina;
			do {
				cout << "Unesite datum (godina/mjesec/dan): ";
				cin >> datum;
				cout << "Unesite vrijeme (SS:MM): ";
				cin >> vrijeme;

				if (!jeVrijemeURadnomVremenu(vrijeme)) {
					cout << "Molimo unesite vrijeme izmeðu 08:00 i 20:00." << endl;
					continue;
				}

				statusTermina = provjeriTermin(datum, vrijeme);

				if (statusTermina == -2) {
					cout << "Vrijeme termina je zauzeto. Molim unesite ponovo." << endl;
				}
				else if (statusTermina == -3) {
					cout << "Svi termini za ovaj datum su zauzeti. Molimo izaberite drugi datum." << endl;
				}
				else {
					break;
				}

			} while (statusTermina != 1);
			termin.setDatum(datum);
			termin.setVrijeme(vrijeme);
			break;
		}
	}
	if (!terminPronadjen)
	{
		cout << "Korisnicko ime nije pronadjeno." << endl;
		return;
	}
	ofstream file(putanja+"Termini.txt", ios::out | ios::trunc);
	for (const auto& termin : termini) {
		file << termin.korisnickoIme << " " << termin.datum << " " << termin.vrijeme << endl;
	}
	file.close();

	cout << "Termin je uspjesno izmijenjen." << endl;
}

void RadnikT::pregledTermina()
{
	ifstream file(putanja + "Termini.txt");
	string kIme, kDatum, kVrijeme;
	cout << "====Pregled termina za tehnicki pregled vozila====" << endl;
	while (file >> kIme >> kDatum >> kVrijeme)
	{
		cout <<"Korisnicko ime: " << kIme << "[ datum: " << kDatum << ", vrijeme: " << kVrijeme <<" ]" << endl;
	}
	file.close();
}

void RadnikT::ispisInfoKlijenta()
{
	cout << "Unesite korisnicko ime klijenta za tehnicki pregled." << endl;
	string kIme;
	cin >> kIme;
	ifstream file(putanja + "Termini.txt");
	string fileIme, kDatum, kVrijeme;
	bool pronadjen = false;
	while (file >> fileIme >> kDatum>> kVrijeme)
	{
		if (kIme == fileIme)
		{
			pronadjen = true;
			break;
		}
	}
	if (!pronadjen)
	{
		cout << "Ne postoji klijent sa zakazanim terminom." << endl;
		return;
	}
	else {
		file.close();
		string linija;
		ifstream klijentFile(putanja + kIme + ".txt");
		try {
			if (!klijentFile.is_open())
			{
				throw FajlNijeOtvoren();
			}
			else
			{
				while (getline(klijentFile, linija)) {
					if (linija.find("Korisnicko Ime:") == string::npos &&
						linija.find("Sifra:") == string::npos &&
						linija.find("Funkcija:") == string::npos) {
						cout << linija << endl;
					}
				}
			}
		}
		catch (const FajlNijeOtvoren& e)
		{
			cout << e.what() << endl;
			return;
		}
		klijentFile.close();
	}
}

void RadnikT::prikaziMeni()
{
	bool kraj = false;
	while (!kraj) {
		int izbor;
		cout << endl;
		cout << "Meni za Radnika T" << endl;
		cout << "1. Odjava" << endl;
		cout << "2. Izmjena termina" << endl;
		cout << "3. Unos termina" << endl;
		cout << "4. Pregled termina" << endl;
		cout << "5. Pregled detaljnijih informacija klijenta sa zakazanim terminom" << endl;
		cout << "Unesite izbor: ";
		cin >> izbor;

		switch (izbor) {
		case 1:
			Odjava();
			this->ulogovan = false;
			kraj = true;
			break;
		case 2:
			izmjeniTermin();
			break;
		case 3:
			odaberiTermin();
			break;
		case 4:
			pregledTermina();
			break;
		case 5:
			ispisInfoKlijenta();
			break;
		default:
			cout << "Nepostojeca opcija!" << endl;
			break;
		}
	}
}

#endif
