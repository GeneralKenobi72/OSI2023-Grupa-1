#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Korisnik.h"
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <random>
using namespace std;
class Termin {
public:
	string datum;
	string vrijeme;
	string voziloID;
	string status="";
	string korisnickoIme;
public:
	Termin() {}
	Termin(const string& korisnickoIme,const string& datum, const string& vrijeme,
		const string& voziloID)
		: korisnickoIme(korisnickoIme), datum(datum), vrijeme(vrijeme), voziloID(voziloID), status("false") {}
	void setDatum(string datum) { this->datum = datum; }
	void setVrijeme(string vrijeme) { this->vrijeme = vrijeme; }
	void setVoziloID(string voziloId) { this->voziloID = voziloId; }
	void setStatus(string status) { this->status = status; }

	string getDatum() { return this->datum; }
	string getVrijeme() { return this->vrijeme; }
	string getVoziloID() { return this->voziloID; }
	string getStatus() { return this->status; }
	string getKorisnickoIme() { return this->korisnickoIme; }
	vector<Termin> ucitajTermine() {
		vector<Termin> termini;
#ifdef _WIN32
		string putanjaDoNeregVozila = "NeregistrovanaVozila\\";
		string putanja = "data\\";
#else
		string putanjaDoNeregVozila = "NeregistrovanaVozila/";
		string putanja = "data/";
#endif
		ifstream file(putanja+"Termini.txt");
		Termin temp;

		while (file >> temp.korisnickoIme >> temp.datum >> temp.vrijeme >>temp.voziloID) {
			termini.push_back(temp);
		}

		file.close();
		return termini;
	}
	int vrijemeUMinute() const {
		int sati, minute;
        #ifdef _WIN32
		if (sscanf_s(vrijeme.c_str(), "%d:%d", &sati, &minute) != 2) {
			return -1;
		}
        #else
		if (sscanf(vrijeme.c_str(), "%d:%d", &sati, &minute) != 2) {
			return -1;
		}
        #endif

		return sati * 60 + minute;
	}
	bool operator<(const Termin& t) const {
		if (datum < t.datum) {
			return true;
		}
		else if (datum > t.datum) {
			return false;
		}
		else {
			return vrijeme < t.vrijeme;
		}
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
	Termin nadjiSlobodanTermin(const vector<Termin>& termini, const string& kIme, const string& regBroj) {

		if (termini.empty()) {
			//neka ovo bude default termin
			Termin slobodanTermin(kIme, "2024.01.22", "08:00", regBroj);
			return slobodanTermin;
		}

		Termin posljednjiTermin = termini.back();
		int minute = posljednjiTermin.vrijemeUMinute() + 30;
		int sati = minute / 60;
		minute %= 60;

		string novoVrijeme = to_string(sati) + ":" + (minute < 10 ? "0" : "") + to_string(minute);
		Termin slobodanTermin(kIme, posljednjiTermin.datum, novoVrijeme, regBroj);
		return slobodanTermin;
	}
};

class Vozilo {
public:
	string marka;
	string model;
	string godinaProizvodnje;
	string regBroj;
	string korisnickoIme;
	string problem = "";
	string imeKlijnta, prezimeKlijnta;
	string brojOsiguranja;

	int vrijednostKazne;
	int cijenaTehnickog;
	int cijenaRegistracije;

	Vozilo() {}
	Vozilo(string korisnickoIme, string marka, string model, string godProiz, string regBroj) :
		korisnickoIme(korisnickoIme), marka(marka), model(model), godinaProizvodnje(godProiz) {
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 100);

		if (dist6(rng) < 60) {
			vrijednostKazne = 0;
		}
		else {
			std::uniform_int_distribution<std::mt19937::result_type> dist6(50, 1000);
			vrijednostKazne = dist6(rng);
		}
		for (int i = 0; i < 10; i++) {
			std::uniform_int_distribution<std::mt19937::result_type> broj(0, 10);
			char buffer[5];
			itoa(broj(rng), buffer, 10);
			brojOsiguranja.push_back(buffer[0]);
		}
	}

	vector<Vozilo> ucitajPodatkeVozila(const string& korisnickoIme)
	{
#ifdef _WIN32
		string putanja = "data\\";
		string putanjaDoNeregVozila = "NeregistrovanaVozila\\";
#else
		string putanja = "data/";
		string putanjaDoNeregVozila = "NeregistrovanaVozila/";
#endif
		Vozilo vozilo;
		vector<Vozilo> vozilaKorisnika;
		ifstream datotekaKlijenta(putanja + korisnickoIme + ".txt");
		try {
			if (!datotekaKlijenta.is_open())
			{
				throw FajlNijeOtvoren();
			}
			else {
				string linija;
				while (getline(datotekaKlijenta, linija)) {
					istringstream iss(linija);
					string kljuc;
					getline(iss, kljuc, ':');
					 if (kljuc == "Ime")
					{
						getline(iss, vozilo.imeKlijnta);
					}
					else if (kljuc == "Prezime")
					{
						getline(iss, vozilo.prezimeKlijnta);
					}
				}
				datotekaKlijenta.close();
			}
		}
		catch (FajlNijeOtvoren& e)
		{
			cout << e.what() << endl;
		}
		ifstream fileVozila(putanja + "vozila.txt");
		if (!fileVozila.is_open()) {
			throw FajlNijeOtvoren();
		}
		while (fileVozila >> vozilo.korisnickoIme >> vozilo.marka >> vozilo.model >> vozilo.godinaProizvodnje >> vozilo.regBroj >> brojOsiguranja) {
			if (vozilo.korisnickoIme == korisnickoIme) {
				vozilaKorisnika.push_back(vozilo);
			}
		}

		return vozilaKorisnika;
	}
};

