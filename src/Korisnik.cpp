#ifndef GETCH_H
#define GETCH_H

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "Izuzeci.h"
#include "Korisnik.h"
#include "getChar.h"
#endif

#include <filesystem>
namespace fs = std::filesystem;

using namespace std;

// ove dvije funkcije(ValidFirtName i ValidLastName) su istog pona�anja
//  moze se koristiti samo jedna za provjeru prvog i zadnjeg imena
// ali zbog preglednosti su definisane zasebno

bool Korisnik::ValidnoIme(string ime)
{
	int i = 1;
	int duzina = size(ime);
	if (!isupper(ime[0]) || duzina == 0)
	{
		return false;
	}
	else
	{
		while (i < duzina)
		{
			if (!islower(ime[i]))
				return false;
			i++;
		}
	}
	return true;
}

bool Korisnik::ValidnoPrezime(string prezime)
{
	int i = 1;
	int duzina = size(prezime);
	if (!isupper(prezime[0]) || duzina == 0)
	{
		return false;
	}
	else
	{
		while (i < duzina)
		{
			if (!islower(prezime[i]))
				return false;
			i++;
		}
	}
	return true;
}

bool Korisnik::ValidanEmail(string email)
{
	if (!isalpha(email[0]))
	{
		return false;
	}
	int at = -1, tacka = -1;
	int brojac_at = 0, brojac_tacka = 0;
	for (int i = 0; i < email.size(); i++)
	{
		if (isspace(email[i]))
		{
			//throw InvalidEmail();
			return false;
		}
		else if (email[i] == '@')
		{
			at = i;
			brojac_at++;
		}
		else if (email[i] == '.')
		{
			tacka = i;
			brojac_tacka++;
		}
	}
	if (at == -1 || tacka == -1)
	{
		return false;
		//throw InvalidEmail();
	}
	if (brojac_at >= tacka)
	{
		//throw InvalidEmail();
		return false;
	}
	if (brojac_tacka > 1 || brojac_at > 1)
	{
		//throw InvalidEmail();
		return false;
	}

	return true;
}

bool Korisnik::ValidnaSifra(string sifra)
{
	int broj = 0, velikaSlova = 0, malaSlova = 0, specijalniChar = 0;
	try {
		if (sifra.size() <= 4 && sifra.size() >= 15)
		{
			throw InvalidSifra();
		}
		else
		{
			if (sifra.find(" ") == -1)
			{
				for (int i = 0; i < sifra.length(); i++)
				{
					if (sifra[i] >= '0' && sifra[i] <= '9')
					{
						++broj;
					}
					else if (sifra[i] >= 'a' && sifra[i] <= 'z')
					{
						++malaSlova;
					}
					else if (sifra[i] >= 'A' && sifra[i] <= 'Z')
					{
						++velikaSlova;
					}
					else if (sifra[i] == '@' || sifra[i] == '*' || sifra[i] == '_')
					{
						++specijalniChar;
					}

				}
				if (broj == 0 || malaSlova == 0 || velikaSlova == 0)
				{
					throw InvalidSifra();
				}
				else
				{
					return true;
				}
			}
			else if (sifra.find(" ") != -1)
			{
				throw InvalidSifra();
			}
		}
		return true;
	}
	catch (const InvalidSifra& e)
	{
		cout << e.what() << endl;
		return false;
	}

}

//f-ja provjerava preko imena fajla da li je korisnicko ime zauzeto ili da li postoji u bazi podataka
//ako datoteka postoji vraca true, inace false
bool Korisnik::pronadjiKorisnickoIme(const string korisnicko_ime)
{
	ifstream file(putanja+korisnicko_ime + ".txt");
	return file.good();
}

//f-ja koju ce dijeliti svi ucesnici za unos sifre
//Unosom se svaki put pojavljuje *
//npr. Unesi sifru:******
string Korisnik::UnesiSifru()
{
	string novaSifra;
	char ch;
	ch = getChar();
	while (ch!=13) {  // Provjeri za ENTER key ASCII 13
		if (ch != 8) {   // Provjeri za backspace ASCII 8
			novaSifra.push_back(ch);
			cout << '*' << std::flush;
		}
		else if (!novaSifra.empty()) {
			novaSifra.pop_back();
			cout << "\b \b";  // Obrisi zadnju * (asterisk)
		}
		ch = getChar();
	}
	cout << endl;
	return novaSifra;
}

string Korisnik::provjeriKorisnickoIme(string korisnico_ime)
{
	while (pronadjiKorisnickoIme(korisnico_ime))
	{
		cout << "Korisnicko ime je zauzeto! " << endl;
		cin >> korisnico_ime;
	}
	return korisnico_ime;
}

bool Korisnik::provjeriPutanju(string putanja)
{
	if (!filesystem::exists(putanja)) {
		if (!filesystem::create_directory(putanja)) {
			cerr << "Greska prilikom stvaranja direktorija!" << endl;
			return false;
		}
		return true;
	}
	return true;
}


//f-ja koja ignorise string do pojave ':'
//Prilikom ispisa iz datoteke-> Korisnicko ime:
//                              Sifra:
// itd. ce ignorisati te ispisati samo username, password...
void Korisnik::ignorisiDvotacku(string imeDatoteke)
{
	size_t pozicija = imeDatoteke.find(':');
	if (pozicija != string::npos)
	{
		string rezultat = imeDatoteke.substr(pozicija + 1);
		cout << rezultat << endl;
	}
}

//ima istu logiku kao i gornja funkcija, s tim sto sada vraca rezultat
string Korisnik::vrati_ignorisiDvotacku(string imeDatoteke)
{
	size_t pozicija = imeDatoteke.find(':');
	if (pozicija != string::npos)
	{
		string rezultat = imeDatoteke.substr(pozicija + 1);
		return rezultat;
	}
	else
	{
		return NULL;
	}
}
