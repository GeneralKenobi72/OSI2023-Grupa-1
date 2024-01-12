#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Korisnik.h"
#include <vector>
using namespace std;
class Termin {
public:
	string datum;
	string vrijeme;
	string voziloID;
	string status;
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
       #ifdef _WIN32
		string putanja = "data\\";
        #else
		string putanja = "data/";
        #endif

		vector<Termin> termini;
		ifstream file(putanja+"Termini.txt");
		Termin temp;

		while (file >> temp.korisnickoIme >> temp.datum >> temp.vrijeme) {
			termini.push_back(temp);
		}

		file.close();
		return termini;
	}
};