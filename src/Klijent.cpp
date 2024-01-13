#ifndef GETCH_H
#define GETCH_H

#include <iostream>
#include "Korisnik.h"
#include "Izuzeci.h"
#include "Klijent.h"
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>
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
		file << "Funkcija:klijent" << "\n";
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
				string K_korisnickoIme, K_sifra, K_Ime, K_prezime, Email,
					K_markaVozila,K_modelVozila,K_godinaProizvodnje,K_registarskiBroj;
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
				getline(out, K_modelVozila);
				cout << "Model vozila:"; ignorisiDvotacku(K_modelVozila);
				getline(out, K_markaVozila); 
				cout << "Marka vozila:"; ignorisiDvotacku(K_markaVozila);
				getline(out, K_godinaProizvodnje);
				cout << "Godina proizvodnje:"; ignorisiDvotacku(K_godinaProizvodnje);
				getline(out, K_registarskiBroj); 
				cout << "Registarski broj:"; ignorisiDvotacku(K_registarskiBroj);
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
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Ime " << endl;
	while (1)
	{
		getline(cin, K_Ime);
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
		//cin >> K_Prezime;
		getline(cin, K_Prezime);
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
		//cin >> K_email;
		getline(cin, K_email);
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
	setKorisnickoIme(K_rezultat);
	return true;
}

void Klijent::prikaziMeni()
{
	int izbor;
	bool kraj = false;
	while (!kraj) {
		cout << "Meni za Klijenta" << endl;
		cout << "1. Odjava" << endl;
		cout << "2. Unos Termina" << endl;
		cout << "3. Otkazivanje Termina" << endl;
		cout << "Unesite izbor: ";
		cin >> izbor;

		switch (izbor) {
		case 1:
			Odjava();
			this->ulogovan = false;
			kraj = true;
			break;
		case 2:
			odaberiTermin();
			break;
		case 3:
			otkaziTermin();
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

void Klijent::unesiPodatke()
{
	if (!provjeriUlogovanje())
	{
		cout << "Niste ulogovani." << endl;
		return;
	}
	string markaVozila, modelVozila, registarskiBroj;
	string godinaProizvodnje;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do {
		cout << "Unesite marku vozila(npr. Golf): ";
		getline(cin, markaVozila);
	} while (!ValidnoVozilo(markaVozila));
	setMarkaVozila(markaVozila);
	do {
		cout << "Unesite model vozila(npr. mk6): ";
		getline(cin, modelVozila);
	} while (!ValidnoVozilo(modelVozila));
	setModelVozila(modelVozila);
	do {
		cout << "Unesite godinu proizvodnje vozila(npr. 2012): ";
		getline(cin, godinaProizvodnje);
	} while (!ValidnaGodina(godinaProizvodnje));
	setGodinaProizvodnje(godinaProizvodnje);
	do {
		cout << "Unesite registarski broj vozila(npr. O46K457): ";
		getline(cin, registarskiBroj);
	} while (!ValidanRegistracijskiBroj(registarskiBroj));
	setRegistarskiBroj(registarskiBroj);
	string korisnicko_ime = getKorisnickoIme();
	ofstream file(putanja+korisnicko_ime+".txt", ios::app);
	try {
		if (!file.is_open())
		{
			throw FajlNijeOtvoren();
		}
		else
		{
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

void Klijent::odaberiTermin()
{
	if (!provjeriUlogovanje())
	{
		return;
	}
	cout << "====Odabir termina za tehnicki pregled=====" << endl;
	ifstream file(putanja + "Termini.txt");
	if (!file)
	{
		cout << "Error kod otvaranja Termina" << endl;
		return;
	}
	vector<Termin> termini;
	string fileKorisnickoIme, fileDatum, fileVrijeme;
	while (file >> fileKorisnickoIme >> fileDatum >> fileVrijeme) {
		Termin temp(fileKorisnickoIme, fileDatum, fileVrijeme, "");
		termini.push_back(temp);
		if (fileKorisnickoIme == this->getKorisnickoIme()) {
			cout << "Izgleda da imate zakazni termin." << endl;
			return;
		}
	}
	file.close();

	sort(termini.begin(), termini.end());

	unesiPodatke();

	string datum, vrijeme, korisnicko_ime;
	korisnicko_ime = getKorisnickoIme();
	string reg_broj = getRegistarskiBroj();
	Termin temp;
	Termin slobodanTermin = temp.nadjiSlobodanTermin(termini, korisnicko_ime);

	cout << "Predlozeni slobodan termin je: " << slobodanTermin.datum << " u " << slobodanTermin.vrijeme << endl;
	cout << "Da li zelite rezervisati ovaj termin? (da/ne): ";
	string da;
	cin >> da;
	if (da == "da")
	{
		upisiTerminUFajl(this->getKorisnickoIme(), slobodanTermin.datum, slobodanTermin.vrijeme);
		cout << "Vas termin je uspjesno zakazan." << endl;
	}
	else {
		int statusTermina;
		do {
			do {
				cout << "Unesite datum (godina.mjesec.dan): ";
				cin >> datum;
			} while (!jeValidanDatum(datum));
			do {
				cout << "Unesite vrijeme (SS:MM): ";
				cin >> vrijeme;
			} while (!jeValidnoVrijeme(vrijeme));

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

		}while (statusTermina != 1);

		//Termin noviTermin(korisnicko_ime, datum, vrijeme, reg_broj);
		upisiTerminUFajl(korisnicko_ime, datum, vrijeme);
	}
}

int Klijent::provjeriTermin(const string& datum, const string& vrijeme)
{
	ifstream file(putanja+"Termini.txt");
	string fileKorisnickoIme, fileDatum, fileVrijeme;
	int brojTermina = 0;
	while (file >> fileKorisnickoIme >> fileDatum >> fileVrijeme) {

		if (fileKorisnickoIme == getKorisnickoIme())
		{
			file.close();
			return -1;
		}
		else if(fileDatum == datum) {
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

void Klijent::upisiTerminUFajl(const string& kIme, const string& datum,const string& vrijeme)
{
	ofstream file(putanja + "Termini.txt", ios::app);
	try {
		if (!file.is_open())
		{
			throw FajlNijeOtvoren();
		}
		else
		{
			file<< getKorisnickoIme() << " " << datum << " " << vrijeme << "\n";
		}
	}
	catch (const FajlNijeOtvoren& e)
	{
		cout << e.what() << endl;
	}
}
void Klijent::otkaziTermin()
{
	ifstream file(putanja+"Termini.txt");
	string line;
	vector<string> lines;

	bool found = false;

	// Cita datoteku i sprema sve linije osim one koja se treba obrisati
	while (getline(file, line)) {
		if (line.find(korisnickoIme) == string::npos) {
			lines.push_back(line);
		}
		else {
			found = true;
		}
	}

	file.close();

	if (!found) {
		cout << "Vas termin nije pronadjen." << endl;
		return;
	}
	ofstream outFile(putanja+"Termini.txt");
	for (const auto& savedLine : lines) {
		outFile << savedLine << endl;
	}

	cout << "Termin uspjesno otkazan." << endl;
}
#endif
