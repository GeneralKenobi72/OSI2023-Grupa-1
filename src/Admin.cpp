#ifndef GETCH_H
#define GETCH_H

#include "Korisnik.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include "Admin.h"
namespace fs = std::filesystem;
using namespace std;

Admin::Admin(const string A_Ime, const string A_Prezime, const string KorisnickoIme, const string A_sifra, const string A_email)
	: Korisnik()
{
	Ime = A_Ime;
	Prezime = A_Prezime;
	korisnickoIme = KorisnickoIme;
	email = A_email;
	sifra = A_sifra;
}

inline string Admin::getIme() { return Ime; }

inline string Admin::getPrezime() { return Prezime; }

inline string Admin::getSifra() { return sifra; }

inline string Admin::getKorisnickoIme() { return korisnickoIme; }

inline string Admin::getEmail() { return email; }

std::vector<std::string> pretraziFajl(const std::string& putanja, const std::string& trazeniString, std::string tipRadnika) {
	std::vector<std::string> poklapanja;

	std::ifstream fajl(putanja);
    if (!fajl.is_open()) {
	    std::cerr << "Nemoguce otvoriti fajl: " << putanja << std::endl;
        return poklapanja;
    }

    std::string linija;
	int brojLinije = 0;
	int brojPoklapanja = 0;
    while (std::getline(fajl, linija)) {
		brojLinije++;

		if(linija == trazeniString) {
			brojPoklapanja++;
	    } else if(linija == ("funkcija:" + tipRadnika)) {
			brojPoklapanja++;
		}
    }
	fajl.close();
	if(brojPoklapanja == 2) {
		std::ifstream fajl(putanja);
    	if (!fajl.is_open()) {
	    	std::cerr << "Nemoguce otvoriti fajl: " << putanja << std::endl;
        	return poklapanja;
    	}
		int i=0;
		while(std::getline(fajl, linija)) {
			if(i != 1) { 						// Da ne ispisuje Sifru
				std::cout << linija << endl;
			}
			i++;
		}
		std::cout << std::endl;
	}
	return poklapanja;
}

/*std::vector<std::string> pretraziDirektorijum(const std::string& direktorijum, const std::string& trazeniString, std::string tipRadnika) {
	std::vector<std::string> poklapanja;
	for (const auto& entry : fs::directory_iterator(direktorijum)) {
		if (fs::is_regular_file(entry.path())) {
		    std::vector<std::string> rezultatiFajla = pretraziFajl(entry.path(), trazeniString, tipRadnika);
			if (!rezultatiFajla.empty()) {
				poklapanja.insert(poklapanja.end(), rezultatiFajla.begin(), rezultatiFajla.end());
			}
		}
    }
    return poklapanja;
}*/
std::vector<std::string> pretraziDirektorijum(const std::string& direktorijum, const std::string& trazeniString, std::string tipRadnika) {
	std::vector<std::string> poklapanja;
	for (const auto& entry : fs::directory_iterator(direktorijum)) {
		if (fs::is_regular_file(entry.path())) {
			std::vector<std::string> rezultatiFajla = pretraziFajl(entry.path().string(), trazeniString, tipRadnika);
			if (!rezultatiFajla.empty()) {
				poklapanja.insert(poklapanja.end(), rezultatiFajla.begin(), rezultatiFajla.end());
			}
		}
	}
	return poklapanja;
}

void Admin::pronadjiRadnike(std::string parametar, std::string informacija, std::string tipRadnika) {
	if(parametar == "Korisnicko") {
		pretraziDirektorijum("data", "KorisnickoIme:" + informacija, tipRadnika);
	} else if(parametar == "Ime") {
		pretraziDirektorijum("data", "Ime:" + informacija, tipRadnika);
	} else if(parametar == "Prezime") {
		pretraziDirektorijum("data", "Prezime:" + informacija, tipRadnika);
	} else if(parametar == "Email") {
		pretraziDirektorijum("data", "Email:" + informacija, tipRadnika);
	}
}

#endif
