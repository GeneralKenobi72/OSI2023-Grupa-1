#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Korisnik.h"
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;
class Termin {
public:
	string datum;
	string vrijeme;
	string voziloID="";
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
		string putanja = "data\\";
#else
		string putanja = "data/";
#endif
		ifstream file(putanja+"Termini.txt");
		Termin temp;

		while (file >> temp.korisnickoIme >> temp.datum >> temp.vrijeme) {
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
	Termin nadjiSlobodanTermin(const vector<Termin>& termini, const string& kIme) {
		if (termini.empty()) {
			//neka ovo bude default termin
			Termin slobodanTermin(kIme, "2024.01.22", "08:00", "");
			return slobodanTermin;
		}

		Termin posljednjiTermin = termini.back();
		int minute = posljednjiTermin.vrijemeUMinute() + 30;
		int sati = minute / 60;
		minute %= 60;

		string novoVrijeme = to_string(sati) + ":" + (minute < 10 ? "0" : "") + to_string(minute);
		Termin slobodanTermin(kIme, posljednjiTermin.datum, novoVrijeme, "");
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
	string imeKlijnta, prezimeKlijnta;
	Vozilo() {}
	Vozilo(string korisnickoIme, string marka, string model, string godProiz, string regBroj) : 
		korisnickoIme(korisnickoIme) , marka(marka), model(model) , godinaProizvodnje(godProiz) {}
	Vozilo ucitajPodatkeVozila(const string& korisnickoIme)
	{
#ifdef _WIN32
		string putanja = "data\\";
#else
		string putanja = "data/";
#endif
		Vozilo vozilo;
		ifstream datoteka(putanja + korisnickoIme + ".txt");
		try {
			if (!datoteka.is_open())
			{
				throw FajlNijeOtvoren();
			}
			else {
				string linija;
				while (getline(datoteka, linija)) {
					istringstream iss(linija);
					string kljuc;
					getline(iss, kljuc, ':');

					if (kljuc == "Marka vozila") {
						getline(iss, vozilo.marka);
					}
					else if (kljuc == "Model vozila") {
						getline(iss, vozilo.model);
					}
					else if (kljuc == "Godina proizvodnje") {
						getline(iss, vozilo.godinaProizvodnje);
					}
					else if (kljuc == "Registarski broj vozila") {
						getline(iss, vozilo.regBroj);
					}
					else if (kljuc == "Korisnicko Ime")
					{
						getline(iss, vozilo.korisnickoIme);
					}
					else if (kljuc == "Ime")
					{
						getline(iss, vozilo.imeKlijnta);
					}
					else if (kljuc == "Prezime")
					{
						getline(iss, vozilo.prezimeKlijnta);
					}
				}
				datoteka.close();
			}
		}
		catch (FajlNijeOtvoren& e)
		{
			cout << e.what() << endl;
		}
		return vozilo;
	}
};

