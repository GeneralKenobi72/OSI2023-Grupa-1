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
	cout << "Unos podataka o novom vozilu za tehnicki pregled." << endl;
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
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			do {
				cout << "Unesite marku vozila klijenta " << korisnickoImeKlijenta << ": ";
				getline(cin, markaVozila);
			} while (!ValidnoVozilo(markaVozila));
			
			do {
				cout << "Unesite model vozila klijenta " << korisnickoImeKlijenta << ": ";
				getline(cin, modelVozila);
			} while (!ValidnoVozilo(modelVozila));
			
			do {
				cout << "Unesite godinu proizvodnje vozila klijenta " << korisnickoImeKlijenta << ": ";
				getline(cin, godinaProizvodnje);
			} while (!ValidnaGodina(godinaProizvodnje));

			do {
				cout << "Unesite registarski broj vozila klijenta " << korisnickoImeKlijenta << ": ";
				getline(cin, registarskiBroj);
			} while (!ValidanRegistracijskiBroj(registarskiBroj));
			string korisnicko_ime = getKorisnickoIme();
		}
	}
	catch (const FajlNijeOtvoren& e)
	{
		cout << e.what() << endl;
	}


	string podaciVozila = markaVozila + " " + modelVozila + " " + godinaProizvodnje + " " + registarskiBroj;

	ifstream fajlVozila(putanja + "vozila.txt");
	string tempLine;
	bool postoji = false;
	while (getline(fajlVozila, tempLine)) {
		if (tempLine.find(korisnickoImeKlijenta + " " + podaciVozila) != string::npos) {
			postoji = true;
			break;
		}
	}
	fajlVozila.close();

	if (!postoji) {
		ofstream file(putanja + "vozila.txt", ios::app);
		try {
			if (!file.is_open()) {
				throw FajlNijeOtvoren();
			}
			else {
				file << korisnickoImeKlijenta << " " << podaciVozila << "\n";
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
	string fileKorisnickoIme, fileDatum, fileVrijeme,fileRegBroj;
	if (pronadjiKorisnickoIme(korisnickoImeKlijenta)==false)
	{
		cout << "Korisnik ne postoji. " << endl;
		return;
	}
	cout << "Da li klijent vec ima vozilo koje zeli odvesti na tehnicki pregled? (da/ne):";
	string d;
	string regBroj;
	cin >> d;
	if (d == "da" || d == "Da")
	{
		regBroj = izaberiVozilo(korisnickoImeKlijenta);
		if (regBroj.empty()) {
			cout << "Nema registrovanih vozila." << endl;
			return;
		}
	}
	else {
		unesiPodatke(korisnickoImeKlijenta);
		regBroj = izaberiVozilo(korisnickoImeKlijenta);
		if (regBroj.empty()) {
			cout << "Nema registrovanih vozila." << endl;
			return;
		}
	}
	vector<Termin> termini;
	while (file1 >> fileKorisnickoIme >> fileDatum >> fileVrijeme>>fileRegBroj) {
		Termin temp(fileKorisnickoIme, fileDatum, fileVrijeme, fileRegBroj);
		termini.push_back(temp);
		if (fileKorisnickoIme == korisnickoImeKlijenta && fileRegBroj==regBroj) {
			cout << "Izgleda da klijent ima zakazni termin za vozilo: "<<regBroj << endl;
			return;
		}
	}

	file1.close();

	sort(termini.begin(), termini.end());

	string datum, vrijeme;
	Termin temp;
	Termin slobodanTermin = temp.nadjiSlobodanTermin(termini,korisnickoImeKlijenta,regBroj);

	cout << "Predlozeni slobodan termin je: " << slobodanTermin.datum << " u " << slobodanTermin.vrijeme << endl;
	cout << "Da li zelite rezervisati ovaj termin? (da/ne): ";
	string da;
	cin >> da;
	if (da == "da")
	{
		upisiTerminUFajl(korisnickoImeKlijenta, slobodanTermin.datum, slobodanTermin.vrijeme, regBroj);
		cout << "Termin klijenta je uspjesno zakazan." << endl;
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

			statusTermina = provjeriTermin(datum, vrijeme, regBroj,korisnickoImeKlijenta);

			if (statusTermina == -2) {
				cout << "Vrijeme termina je zauzeto. Molim unesite ponovo." << endl;
			}
			else if (statusTermina == -3) {
				cout << "Svi termini za ovaj datum su zauzeti. Molimo izaberite drugi datum." << endl;
			}
			else if (statusTermina == -1)
			{
				cout << "Vas termin je zakazan za vozilo: "<<regBroj << endl;
				break;
			}

		} while (statusTermina != 1);

		//Termin noviTermin(korisnicko_ime, datum, vrijeme, reg_broj);
		upisiTerminUFajl(korisnickoImeKlijenta, datum, vrijeme, regBroj);
	}
}

int RadnikT::provjeriTermin(const string& datum, const string& vrijeme, const string& regBroj,const string& kIme)
{
	ifstream file(putanja + "Termini.txt");
	string fileKorisnickoIme, fileDatum, fileVrijeme, fileRegBroj;
	int brojTermina = 0;
	while (file >> fileKorisnickoIme >> fileDatum >> fileVrijeme>>fileRegBroj) {

		if (fileKorisnickoIme == kIme && fileRegBroj==regBroj)
		{
			file.close();
			return -1;
		}
		else if (fileDatum == datum) {
			brojTermina++;

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

void RadnikT::upisiTerminUFajl(const string& kIme, const string& datum, const string& vrijeme, const string& regBroj)
{
	ofstream file(putanja + "Termini.txt", ios::app);
	try {
		if (!file.is_open())
		{
			throw FajlNijeOtvoren();
		}
		else
		{
			file << kIme << " " << datum << " " << vrijeme <<" "<<regBroj << "\n";
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
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, R_korisnickoIme);
	bool nastavi = true;
	int i = 0;
	while (!provjeriKorisnickoImeRadnikaT(R_korisnickoIme) && i<2) {
		cout << "Korisnicko ime nije pronadjeno! Molim unesite ponovo." << endl;
		getline(cin, R_korisnickoIme);
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
	////Termini.txt
	ifstream file1(putanja + "Termini.txt");
	if (!file1)
	{
		cout << "Error kod otvaranja Termina" << endl;
		return;
	}
	cout << "Unesite korisnicko ime klijenta ciji se termin otkazuje." << endl;
	string korisnickoImeKlijenta,regBrojZaOtkaz;
	cin >> korisnickoImeKlijenta;

	//cout << "Unesite registracijski broj klijenta." << endl;
	regBrojZaOtkaz = izaberiVozilo(korisnickoImeKlijenta);

	string fileKorisnickoIme, fileDatum, fileVrijeme,fileRegBroj;
	if (pronadjiKorisnickoIme(korisnickoImeKlijenta) == false)
	{
		cout << "Klijent ne postoji. " << endl;
		return;
	}

	string line;
	vector<string> lines;

	bool found = false;

	while (getline(file1, line)) {
		if (line.find(korisnickoImeKlijenta) != string::npos && line.find(regBrojZaOtkaz) != string::npos) {
			found = true;
		}
		else {
			lines.push_back(line);
		}
	}

	file1.close();

	if (!found) {
		cout << "Termin klijenta nije pronadjen za vozilo sa registarskim brojem : " << regBrojZaOtkaz << endl;
		return;
	}
	ofstream outFile(putanja + "Termini.txt");
	for (const auto& savedLine : lines) {
		outFile << savedLine << endl;
	}
	///////VOZILA.txt
	ifstream fileVozila(putanja + "vozila.txt");
	try {
		if (!fileVozila.is_open())
		{
			throw FajlNijeOtvoren();
		}
	}
	catch (FajlNijeOtvoren& e)
	{
		cout << e.what() << endl;
		return;
	}
	vector<string> linijeVozila;
	bool voziloZaBrisanjePronadjeno = false;
	string linijaVozila;
	while (getline(fileVozila, linijaVozila)) {
		if (linijaVozila.find(korisnickoImeKlijenta) != string::npos && linijaVozila.find(regBrojZaOtkaz) != string::npos) {
			voziloZaBrisanjePronadjeno = true;
			continue; 
		}
		linijeVozila.push_back(linijaVozila);
	}

	fileVozila.close();

	if (voziloZaBrisanjePronadjeno) {
		ofstream outFileVozila(putanja + "vozila.txt");
		if (!linijeVozila.empty()) {
			for (size_t i = 0; i < linijeVozila.size() - 1; ++i) {
				outFileVozila << linijeVozila[i] << endl;
			}

			outFileVozila << linijeVozila.back();
		}
		//cout << "Informacije o vozilu sa registarskim brojem " << regBrojZaOtkaz << " su uspjesno obrisane." << endl;
	}
	else {
		//cout << "Nije pronadjeno vozilo sa registarskim brojem " << regBrojZaOtkaz << endl;
	}
	
	/*bool pronadjen = false;
	while (file1 >> fileKorisnickoIme >> fileDatum >> fileVrijeme >>fileRegBroj) {
		if (fileKorisnickoIme == korisnickoImeKlijenta && fileRegBroj==regBrojZaOtkaz) {
			pronadjen = true;
			break;
		}
	}
	if (!pronadjen) {
		cout << "Klijenta nije moguce pronaci u listi termina." << endl;
		return;
	}
	string line;
	vector<string> lines;

	bool found = false;

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
	ifstream fileKlijenta(putanja + korisnickoImeKlijenta + ".txt");
	try {
		if (!fileKlijenta.is_open())
		{
			throw FajlNijeOtvoren();
		}
	}
	catch (FajlNijeOtvoren& e)
	{
		cout << e.what() << endl;
		return;
	}
	vector<string> linijeZaSacuvati;
	string linija;
	int preskoci = 0;

	while (getline(fileKlijenta, linija)) {
		if (preskoci > 0) {
			preskoci--;
			continue;
		}

		if (linija.find("Registarski broj vozila:" + regBrojZaOtkaz) != string::npos) {
			preskoci = 3;
			continue;
		}

		linijeZaSacuvati.push_back(linija);
	}

	fileKlijenta.close();

	ofstream outFileKlijenta(putanja + korisnickoImeKlijenta + ".txt");
	for (const auto& linija : linijeZaSacuvati) {
		outFileKlijenta << linija << endl;
	}
	outFileKlijenta.close();*/
	cout << "Termin uspjesno otkazan." << endl;
}

void RadnikT::izmjeniTermin()
{
	Termin t;
	vector<Termin> termini=t.ucitajTermine();
	string korisnickoIme, datum, vrijeme, regBroj;

	cout << "Unesite korisnicko ime klijenta za izmjenu termina "<<endl;
	cin >> korisnickoIme;
	cout << "Unesite njegov registarski broj vozila " << endl;
	regBroj = izaberiVozilo(korisnickoIme);
	bool terminPronadjen = false;
	for (auto& termin : termini) {
		if (termin.korisnickoIme == korisnickoIme && termin.voziloID == regBroj) {
			terminPronadjen = true;
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
					cout << "Molimo unesite vrijeme izmeðu 08:00 i 20:00." << endl;
					continue;
				}

				statusTermina = provjeriTermin(datum, vrijeme,regBroj,korisnickoIme);

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
		cout << "Korisnicko ime sa datim registracijskim brojem nije pronadjeno." << endl;
		return;
	}
	ofstream file(putanja+"Termini.txt", ios::out | ios::trunc);
	for (const auto& termin : termini) {
		file << termin.korisnickoIme << " " << termin.datum << " " << termin.vrijeme <<" "<<termin.voziloID << endl;
	}
	file.close();

	cout << "Termin je uspjesno izmijenjen." << endl;
}

void RadnikT::pregledTermina()
{
	ifstream file(putanja + "Termini.txt");
	string kIme, kDatum, kVrijeme, regBroj;
	cout << "====Pregled termina za tehnicki pregled vozila====" << endl;
	while (file >> kIme >> kDatum >> kVrijeme>>regBroj)
	{
		cout << "Korisnicko ime: " << kIme << "[ datum: " << kDatum << ", vrijeme: " << kVrijeme << 
			", registarski broj:" << regBroj<< " ]" << endl;
	}
	file.close();
}

void RadnikT::ispisInfoKlijenta()
{
	cout << "Unesite korisnicko ime klijenta za tehnicki pregled." << endl;
	string kIme;
	cin >> kIme;
	ifstream file(putanja + "Termini.txt");
	string fileIme, kDatum, kVrijeme, kRegBroj;
	bool pronadjen = false;
	while (file >> fileIme >> kDatum>> kVrijeme>>kRegBroj)
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

void RadnikT::popunjavanjeIzvjestaja()
{
	Izvjestaj izvjestaj;
	Termin temp;
	vector<Termin> termini = temp.ucitajTermine();
	Termin odabraniTermin;

	bool terminPronadjen = false;
	string korisnickoImeKlijenta;
	cout << "Unesite korisnicko ime ciji pregled vozila zelite izvrsiti: ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, korisnickoImeKlijenta);

	Vozilo vozilo_temp;
	vector<Vozilo> vozilaKlijenta = vozilo_temp.ucitajPodatkeVozila(korisnickoImeKlijenta);
	if (vozilaKlijenta.empty()) {
		cout << "Klijent nema vozila." << endl;
		return;
	}
	cout << "Izaberite vozilo" << endl;
	for (size_t i = 0; i < vozilaKlijenta.size(); i++) {
		cout << i + 1 << ". " << vozilaKlijenta[i].regBroj << endl;
	}
	int izbor;
	cout << "Unesite broj vozila: ";
	cin >> izbor;
	if (izbor < 1 || izbor > vozilaKlijenta.size()) {
		cout << "Neispravan izbor." << endl;
		return;
	}

	Vozilo odabranoVozilo = vozilaKlijenta[izbor - 1];

	if (daLiJeIzvjestajVecIzdat(odabranoVozilo.regBroj)) {
		cerr << "Izvjestaj za ovo vozilo " << odabranoVozilo.regBroj << " je vec izdato." << endl;
		return;
	}
	for (const auto& t : termini) {
		if (t.korisnickoIme == korisnickoImeKlijenta && t.voziloID == odabranoVozilo.regBroj) {
			odabraniTermin = t;
			terminPronadjen = true;
			break;
		}
	}
	if (!terminPronadjen) {
		cout << "Nije pronadjen odgovarajuci termin za izabrano vozilo." << endl;
		return;
	}

	izvjestaj.termin = odabraniTermin;
	izvjestaj.vozilo = odabranoVozilo;



		/*ifstream file(putanja + "Termini.txt");
		string fileIme, kDatum, kVrijeme;
		bool pronadjen = false;
		while (file >> fileIme >> kDatum >> kVrijeme)
		{
			if (korisnickoImeKlijenta == fileIme)
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
	for (const auto& t : termini)
	{
		if (t.korisnickoIme == korisnickoImeKlijenta)
		{
			odabraniTermin = t;
			terminPronadjen = true;
			break;
		}
	}
	if (!terminPronadjen) {
		cout << "Nije pronadjen odgovarajuci termin." << endl;
		return; 
	}
	izvjestaj.vozilo = vozilo_temp.ucitajPodatkeVozila(odabraniTermin.korisnickoIme);*/
	izvjestaj.izvrseniRad = "Generalni pregled";
	cout << "Da li je vozilo imalo neka ostecenja? (da/ne):";
	string da;
	cin >> da;
	if (da == "da" || da == "Da")
	{
		cout << "Navedite koji su problemi (problem1,problem2, ...) korisnika "<<korisnickoImeKlijenta 
			<<" vozila ("<< odabranoVozilo.regBroj<<"): ";
		string problemi;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, problemi);

		stringstream ss(problemi);
		string problem;
		while (getline(ss, problem, ',')) {
			problem.erase(problem.find_last_not_of(" \n\r\t") + 1);
			problem.erase(0, problem.find_first_not_of(" \n\r\t"));
			izvjestaj.dodatniProblemi.push_back(problem);
		}
		this->potvrdaIzvjestaja = true;
	}
	else
	{
		this->potvrdaIzvjestaja = true;
		izvjestaj.dodatniProblemi.push_back("Nema");
	}
	cuvanjeIzvjestaja(izvjestaj);
}

void RadnikT::cuvanjeIzvjestaja(const Izvjestaj& izvjestaj)
{
	ofstream fajl(putanja + "Izvjestaji.txt", ios::app);
	cout << "Cuvanje izvjestaja..." << endl;
	if (fajl.is_open()) {
		fajl << izvjestaj.termin.korisnickoIme << ","
			<< izvjestaj.termin.datum << ","
			<< izvjestaj.termin.vrijeme<<","
			<< izvjestaj.vozilo.marka << ","
			<< izvjestaj.vozilo.model << ","
			<< izvjestaj.vozilo.godinaProizvodnje << ","
			<< izvjestaj.vozilo.regBroj << ","
			<< izvjestaj.izvrseniRad << ";";
		for (auto it = izvjestaj.dodatniProblemi.begin(); it != izvjestaj.dodatniProblemi.end(); ++it) {
			fajl << (it != izvjestaj.dodatniProblemi.begin() ? ";" : "") << *it;
		}
		fajl <<"\n";
		cout << "Izvjestaj upsjesno sacuvan." << endl;
	}
	else {
		cerr << "Nije moguce otvoriti fajl." << endl;
	}

	cout << "Izdavanje potvrde..." << endl;
	izdajPotvrdu(izvjestaj);
}

void RadnikT::izdajPotvrdu(const Izvjestaj& izvjestaj)
{
	if (!provjeriPotvrduIzvjestaja())
	{
		cout << "Nije moguce izdati potvrdu." << endl;
		return;
	}

	ofstream potvrda(putanja+"Potvrda_" + izvjestaj.vozilo.korisnickoIme + ".txt", ios::app);
	centrirajTekst("Servis vozila - Potvrda", potvrda);
	potvrda <<string(153,'-')<<"\n";
	string datumIzdavanja=dodajDaneNaDatum(0);
	potvrda << "Datum izdavanja: " << datumIzdavanja << "\n";
	potvrda << "Ime i prezime klijenta: " << izvjestaj.vozilo.imeKlijnta << " " << izvjestaj.vozilo.prezimeKlijnta << "\n";

	potvrda << "Model vozila: " << izvjestaj.vozilo.model << "\n";
	potvrda << "Marka vozila: " << izvjestaj.vozilo.marka << "\n";
	potvrda << "Registarski broj:" << izvjestaj.vozilo.regBroj << "\n";

	potvrda << "Problemi: ";
	if (!izvjestaj.dodatniProblemi.empty()) {
		for (auto it = izvjestaj.dodatniProblemi.begin(); it != izvjestaj.dodatniProblemi.end(); ++it) {
			potvrda << *it;
			if (next(it) != izvjestaj.dodatniProblemi.end()) {
				potvrda << ",";
			}
		}
	}
	potvrda << "\n";

	potvrda << "Izdao/la: " << this->Ime << " " << this->Prezime << "\n";
	potvrda << string(153, '-') << "\n";
	cout << "Potvrda je uspjesno izdata." << "\n";
	potvrda.close();
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
		cout << "6. Otkazivanje termina klijenta" << endl;
		cout << "7. Popunjavanje izvjestaja" << endl;
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
		case 6:
			otkazivanjeTermina();
			break;
		case 7:
			popunjavanjeIzvjestaja();
			break;
		default:
			cout << "Nepostojeca opcija!" << endl;
			break;
		}
	}
}

#endif
