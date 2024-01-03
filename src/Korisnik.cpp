#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "Izuzeci.h"
#include <conio.h>
#include "Korisnik.h"
using namespace std;

<<<<<<< HEAD
// ove dvije funkcije(ValidFirtName i ValidLastName) su istog ponasanja
//  moze se koristiti samo jedna za provjeru prvog i zadnjeg imena
// ali zbog preglednosti su definisane zasebno
=======
// ove dvije funkcije(ValidFirtName i ValidLastName) su istog ponašanja
//  moze se koristiti samo jedna za provjeru prvog i zadnjeg imena
// ali zbog preglednosti su definisane zasebno

>>>>>>> e18e0b8 (Izvrsene promjene naziva sa eng na srpski)
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
<<<<<<< HEAD
=======
		//cout << "Invalid email input." << endl;
		//throw InvalidEmail();
>>>>>>> e18e0b8 (Izvrsene promjene naziva sa eng na srpski)
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
<<<<<<< HEAD
=======
		//cout << "Invalid email input." << endl;
>>>>>>> e18e0b8 (Izvrsene promjene naziva sa eng na srpski)
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

<<<<<<< HEAD
//f-ja provjerava preko imena fajla da li je korisnicko ime zauzeto ili da li postoji u bazi podataka
//ako datoteka postoji vraca true, inace false
=======
//f-ja provjerava preko imena fajla da li je korisnicko ime zauzeto 
//ako datoteka postoji vraca true, inaèe false

>>>>>>> e18e0b8 (Izvrsene promjene naziva sa eng na srpski)
bool Korisnik::zauzetKorisnickoIme(const string korisnicko_ime)
{
	ifstream file(korisnicko_ime + ".txt");
	return file.good();
}

//f-ja koju ce dijeliti svi ucesnici za unos sifre
//Unosom se svaki put pojavljuje *
<<<<<<< HEAD
//npr. Unesi sifru:******
=======
//npr. Enter password:******

>>>>>>> e18e0b8 (Izvrsene promjene naziva sa eng na srpski)
string Korisnik::UnesiSifru()
{
	string novaSifra;
	char ch;
	ch = _getch();
	while (ch != 13) {  // Provjeri za ENTER key ASCII 13
		if (ch != 8) {   // Provjeri za backspace ASCII 8
			novaSifra.push_back(ch);
			cout << '*';
		}
		else if (!novaSifra.empty()) {
			novaSifra.pop_back();
			cout << "\b \b";  // Obrisi zadnju * (asterisk)
		}
		ch = _getch();
	}
	cout << endl;
	return novaSifra;
}

string Korisnik::provjeriKorisnickoIme(string korisnico_ime)
{
	while (!zauzetKorisnickoIme(korisnico_ime))
	{
		cout << "Korisnicko ime je zauzeto! " << endl;
		cin >> korisnico_ime;
	}
	return korisnico_ime;
}

//f-ja koja ignorise string do pojave ':'
<<<<<<< HEAD
//Prilikom ispisa iz datoteke-> Korisnicko ime:
//                              Sifra:
// itd. ce ignorisati te ispisati samo username, password...
=======
//Prilikom ispisa iz datoteke-> Username:
//                              Password:
// itd. ce ignorisati te ispisati samo username, password...

>>>>>>> e18e0b8 (Izvrsene promjene naziva sa eng na srpski)
void Korisnik::ignorisiDvotacku(string imeDatoteke)
{
	size_t pozicija = imeDatoteke.find(':');
	if (pozicija != string::npos)
	{
		string rezultat = imeDatoteke.substr(pozicija + 1);
		cout << rezultat << endl;
	}
}

<<<<<<< HEAD
//ima istu logiku kao i gornja funkcija, s tim sto sada vraca rezultat
=======
//ima istu logiku kao i gornja funkcija, s tim što sada vraca rezultat

>>>>>>> e18e0b8 (Izvrsene promjene naziva sa eng na srpski)
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
