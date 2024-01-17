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

bool Admin::ispisiZahtjeve() {
	vector<string> listOfUsers;
	if (!std::filesystem::exists(putanja + putanja2)) return false;
	for (const auto& file : std::filesystem::directory_iterator(putanja + putanja2)) {
		ifstream inputFile(file.path());
		string sample;
		getline(inputFile, sample);
		listOfUsers.push_back(sample);
	}
	bool flag = false;
	for (string sample : listOfUsers) {
		cout << sample << endl;
		flag = true;
	}
	return flag;
}

void Admin::odobriZahtjev(string kIme)
{
	ifstream file(putanja + putanja2 + kIme + "Zahtjev.txt");
	if (!file.is_open()) {
		cout << "Neispravno korisnicko ime. Pokusajte ponovo. " << endl;
		return;
	}
	string ime, novaSifra;
	getline(file, ime);
	getline(file, novaSifra);
	file.close();
	std::filesystem::remove(putanja + putanja2 + kIme + "Zahtjev.txt");
	ifstream file1(putanja + kIme + ".txt");
	string kime,staraSifra, prezime, email, fja;
	getline(file1, kime);
	getline(file1, staraSifra);
	getline(file1, ime);
	getline(file1, prezime);
	getline(file1, email);
	getline(file1, fja);
	file1.close();
	ofstream file2(putanja + kIme + ".txt");
	file2 << kime << "\n";
	file2 <<"Sifra:" << novaSifra << "\n";
	file2 << ime << "\n";
	file2 << prezime << "\n";
	file2 << email << "\n";
	file2 << fja << "\n";
	file2.close();
}


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

std::vector<std::string> pretraziFajl(const std::string& putanja, const std::string& trazeniString, std::string tipRadnika, bool& pronadjen) {
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
		pronadjen = true;
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
std::vector<std::string> pretraziDirektorijum(const std::string& direktorijum, const std::string& trazeniString, std::string tipRadnika, bool& pronadjen) {
	std::vector<std::string> poklapanja;
	for (const auto& entry : fs::directory_iterator(direktorijum)) {
		if (fs::is_regular_file(entry.path())) {
			std::vector<std::string> rezultatiFajla = pretraziFajl(entry.path().string(), trazeniString, tipRadnika, pronadjen);
			if (!rezultatiFajla.empty()) {
				poklapanja.insert(poklapanja.end(), rezultatiFajla.begin(), rezultatiFajla.end());
			}
		}
	}
	return poklapanja;
}


void Admin::pronadjiRadnike(std::string parametar, std::string informacija, std::string tipRadnika) {
	bool pronadjen = false;
	if(parametar == "Korisnicko") {
		pretraziDirektorijum("data", "KorisnickoIme:" + informacija, tipRadnika, pronadjen);
		if(!pronadjen) {
			std::cout << "Nije pronadjen radnik sa korisnickim imenom: " << informacija << std::endl;
		}
	} else if(parametar == "Ime") {
		pretraziDirektorijum("data", "Ime:" + informacija, tipRadnika, pronadjen);
		if(!pronadjen) {
			std::cout << "Nije pronadjen radnik sa imenom: " << informacija << std::endl;
		}
	} else if(parametar == "Prezime") {
		pretraziDirektorijum("data", "Prezime:" + informacija, tipRadnika, pronadjen);
		if(!pronadjen) {
			std::cout << "Nije pronadjen radnik sa prezimenom: " << informacija << std::endl;
		}
	} else if(parametar == "Email") {
		pretraziDirektorijum("data", "Email:" + informacija, tipRadnika, pronadjen);
		if(!pronadjen) {
			std::cout << "Nije pronadjen radnik sa emailom: " << informacija << std::endl;
		}
	}
}

#endif
