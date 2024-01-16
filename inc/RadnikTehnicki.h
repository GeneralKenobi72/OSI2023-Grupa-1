#pragma once
#include <iostream>
#include "Korisnik.h"
#include "Klijent.h"
#include "Radnik.h"
#include <string>
#include <fstream>
#include "Termin.h"
#include <vector>
#include <functional>
#include <ctime>
#include <iomanip>
#include <sstream>
using namespace std;

// RadnikT-za tehnicki pregled
class RadnikT : public Radnik {
private:
	// Vraca podstring od pocetka do pozicije underscore-a
	string fajlKorisnickoImeRadnikaT(const string fileIme);
	function<void()> dodajRadnikaFunc;
	bool provjeriUlogovanje() override { 
		if (ulogovan == false)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	Klijent klijent;
	bool potvrdaIzvjestaja = false;
public:
	RadnikT(std::string ime, std::string prezime, std::string korisnicko,
			std::string sifra, std::string email) : Radnik(ime,prezime,korisnicko,sifra,email) {};
	RadnikT() noexcept : Radnik() {}
	RadnikT(function<void()> func) : Radnik(), dodajRadnikaFunc(func) {}
	//Ovjde se pohranjuju info. o nekom radniku za tehnicki pregled
	RadnikT(bool ulogovan) noexcept : Radnik() { this->ulogovan = ulogovan; }
	void postaviInfo(string korisnickoIme);

	void ispisFajla(string korisnicko_ime);

	//Ovjde je radnik vec registrovan na sistem te je samo potrebno ulogovanje 
	bool Ulogovanje() override;
	void prikaziMeni() override;
	bool provjeriKorisnickoImeRadnikaT(const string korisnickoIme);
	bool provjeriRadnikaTehnicki(string korisnickoIme_, string sifra_);
	void postaviPozicija() { pozicija = "Radnik za Tehnicki Pregled"; }
	string vratiPoziciju(){ return pozicija; }
	void setRegistraciju() { this->registrovan = true; }
	Korisnik* provjeri(string korisnickoIme, string sifra) override
	{
		if (this->provjeriRadnikaTehnicki(korisnickoIme, sifra)) {
			return new RadnikT(true);
		}
		else {
			cout << "Izgleda da nemate nalog." << endl;
			cout << "Nova registracija? (da/Da)" << endl;
			string da;
			cin >> da;
			if (da == "da" || da == "Da")
			{
				cout << "Prikaz Meni" << endl;
				return new RadnikT(dodajRadnikaFunc);
			}
			else
			{
				return nullptr;
			}
		}
	}

	void unesiPodatke(const string& korisnickoImeKlijenta);
	void odaberiTermin();
	int provjeriTermin(const string& datum, const string& vrijeme, const string&, const string&);
	void upisiTerminUFajl(const string&, const string&, const string&, const string& );

	int vrijemeUMinute(const string& vrijeme) {
		int sati, minute;
		char dvotacka;

		istringstream stream(vrijeme);
		stream >> sati >> dvotacka >> minute;

		return sati * 60 + minute;
	}
	bool jeVrijemeURadnomVremenu(const string& vrijeme) {
		int sati, minute;
		char dvotacka;
		stringstream ss(vrijeme);
		ss >> sati >> dvotacka >> minute;

		// nE moze se zakazivati poslije 20:00
		if (sati > 20 || sati < 8)
		{
			cout << "Vrijeme je van radnog vremena." << endl;
			return false;
		}
		return true;
	}
	bool jeValidnoVrijeme(const string& vrijeme) {
		int sati, minute;
         #ifdef _WIN32 
		if (sscanf_s(vrijeme.c_str(), "%d:%d", &sati, &minute) != 2) {
			return false;
		}
        #else 
		if (sscanf(vrijeme.c_str(), "%d:%d", &sati, &minute) != 2) {
			return false;
		}
        #endif
		return sati >= 8 && sati <= 20 && minute >= 0 && minute < 60;
	}
	bool jePrestupnaGodina(int godina) {
		if ((godina % 4 == 0 && godina % 100 != 0) || godina % 400 == 0) {
			return true;
		}
		else {
			return false;
		}
	}
	bool jeValidanDatum(const string& datum) {
		int godina, mjesec, dan;
        #ifdef _WIN32
		if (sscanf_s(datum.c_str(), "%d.%d.%d", &godina, &mjesec, &dan) != 3) {
			return false;
		}
        #else
		if (sscanf(datum.c_str(), "%d.%d.%d", &godina, &mjesec, &dan) != 3) {
			return false;
		}
        #endif

		struct tm unetiDatum = { 0 };
		unetiDatum.tm_year = godina - 1900;
		unetiDatum.tm_mon = mjesec - 1;
		unetiDatum.tm_mday = dan;

		if (godina < 1900 || godina > 2024) return false;
		if (mjesec < 1 || mjesec > 12) return false;
		if (dan < 1 || dan > 31) return false;

		if (mjesec == 2) {
			int maxDaniUFeb;
			if (jePrestupnaGodina(godina)) {
				maxDaniUFeb = 29;
			}
			else {
				maxDaniUFeb = 28;
			}
			if (dan > maxDaniUFeb) {
				return false;
			}
		}
		else if (mjesec == 4 || mjesec == 6 || mjesec == 9 || mjesec == 11) {
			if (dan > 30)
				return false;
		}

		time_t trenutnoVrijeme = time(0);
		struct tm trenutno;
        #ifdef _WIN32
		localtime_s(&trenutno, &trenutnoVrijeme);
        #else
		localtime_r(&trenutnoVrijeme, &trenutno);
         #endif

		time_t unetiDatumTemp = mktime(&unetiDatum);
		time_t trenutnoTemp = mktime(&trenutno);
		if (unetiDatumTemp >= trenutnoTemp)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void otkazivanjeTermina();
	void izmjeniTermin();
	void pregledTermina();
	void ispisInfoKlijenta();

	struct Izvjestaj {
		Termin termin;
		Vozilo vozilo;
		string izvrseniRad;
		vector<string> dodatniProblemi;
		int cijenaTehnickogPregleda;
	};
	void popunjavanjeIzvjestaja();
	void cuvanjeIzvjestaja(const Izvjestaj& izvjestaj);
	void izdajPotvrdu(const Izvjestaj& izvjestaj);
	bool voziloSpremnoZaRegistraciju(const Izvjestaj& izvjestaj) {
		// Vozilo je spremno za registraciju ako nema dodatnih problema
		return izvjestaj.dodatniProblemi.size() == 1 && izvjestaj.dodatniProblemi[0] == "Nema";
	}
	void centrirajTekst(const string& tekst, ofstream& file, int sirinaLinije = 153) {
		int duzinaTeksta = tekst.length();
		int pocetak = (sirinaLinije - duzinaTeksta) / 2;
		string razmaci(pocetak, ' ');
		file << razmaci << tekst << "\n";
	}

	string formatirajDatum(const std::tm& tm) {
		ostringstream oss;
		oss << put_time(&tm, "%Y.%m.%d");
		return oss.str();
	}

	string dodajDaneNaDatum(int brojDana) {
		time_t trenutno = time(nullptr);

#ifdef _WIN32
		std::tm tm;
		localtime_s(&tm, &trenutno);
#else
		std::tm tm = *std::localtime(&trenutno);
#endif
		tm.tm_mday += brojDana;
		std::mktime(&tm);

		return formatirajDatum(tm);
	}
	bool provjeriPotvrduIzvjestaja()
	{
		if (potvrdaIzvjestaja == true)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	string izaberiVozilo(string korisnickoImeKlijnta)
	{
		ifstream file(putanja + "vozila.txt");
		if (!file.is_open())
		{
			cout << "Ne moze se otvoriti datoteka." << endl;
			return "";
		}

		vector<string> registarskiBrojevi;
		string line;

		while (getline(file, line))
		{
			if (line.find(korisnickoImeKlijnta + " ") == 0)
			{
				size_t lastSpace = line.find_last_of(" ");
				string regBroj = line.substr(lastSpace + 1);
				registarskiBrojevi.push_back(regBroj);
			}
		}

		file.close();

		if (registarskiBrojevi.empty())
		{
			cout << "Nemate registrovanih vozila." << endl;
			return "";
		}

		cout << "Izaberite vozilo" << endl;
		for (size_t i = 0; i < registarskiBrojevi.size(); i++)
		{
			cout << i + 1 << ". " << registarskiBrojevi[i] << endl;
		}

		int izbor;
		do {
			cout << "Unesite broj vozila: ";
			cin >> izbor;

			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}
			if (izbor < 1 || izbor > registarskiBrojevi.size()) {
				cout << "Neispravan izbor. Molimo unesite broj izmedju 1 i " << registarskiBrojevi.size() << "." << endl;
			}

		} while (izbor < 1 || izbor > registarskiBrojevi.size());

		return registarskiBrojevi[izbor - 1];
	}

	bool daLiJeIzvjestajVecIzdat(const string& regBroj) {
		ifstream fajl(putanja + "Izvjestaji.txt");
		string linija;
		while (getline(fajl, linija)) {
			istringstream iss(linija);
			vector<string> dijelovi;
			string dio;
			while (std::getline(iss, dio, ',')) {
				dijelovi.push_back(dio);
			}
			if (dijelovi.size() > 6 && dijelovi[6] == regBroj) {
				return true; 
			}
		}
		return false;
	}
};
