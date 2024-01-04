<<<<<<< HEAD
#ifndef GETCH_H
#define GETCH_H

=======
>>>>>>> develop
#include "Korisnik.h"
#include "Admin.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Izuzeci.h"
#include <filesystem>
<<<<<<< HEAD
=======
#include "Izuzeci.h"
>>>>>>> develop
#include "RadnikTehnicki.h"
#include "AdminTehnicki.h"
namespace fs = std::filesystem;
using namespace std;

void AdminTehnicki::Prijava()
{
	string AT_korisnickoIme, AT_sifra, rezultat,
		korisnickoIme_rezultat, sifra_rezultat;
	cout << "Unesite korisnicko ime" << endl;
	cin >> AT_korisnickoIme;

	while (!provjeriKorisnickoImeAdminT(AT_korisnickoIme)) {
		cout << "Korisnicko ime nije pronadjeno! Molim unesite ponovo." << endl;
		cin >> AT_korisnickoIme;
	}

	ifstream file(AT_korisnickoIme + "_administratorTehnicki.txt");
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
	}
	cout << "Unesite sifru" << endl;
	AT_sifra = UnesiSifru();
<<<<<<< HEAD
=======
	string AT_rezultat;
>>>>>>> develop
	while (1)
	{
		if (AT_sifra != rezultat)
		{
			cout << "Netacna sifra. Molim unesite ponovo." << endl;
			AT_sifra = UnesiSifru();
		}
		else
		{
<<<<<<< HEAD
			cout << "Dobrodosli " << korisnickoIme_rezultat << " nazad!" << endl;
=======
			AT_rezultat = vrati_ignorisiDvotacku(korisnickoIme_rezultat);
			cout << "Dobrodosli " << AT_rezultat << " nazad!" << endl;
>>>>>>> develop
			break;
		}
	}
}

//Ovdje treba jos doraditi kod dodajRadnikaTehnicki()
void AdminTehnicki::dodajRadnikaTehnicki()
{
	string KorisnickoImeRadnikaT, LozinkaRadnikaT,
		ImeRadnikaT, PrezimeRadnikT, EmailRadnikaT;
	cout << "Unesite korisnicko ime." << endl;
	cin >> KorisnickoImeRadnikaT;
	cout << "Unesite Ime." << endl;
	while (1)
	{
		cin >> ImeRadnikaT;
		try {
			if (!ValidnoIme(ImeRadnikaT))
			{
				throw InvalidIme();
			}
			else {
				Ime = ImeRadnikaT;
				break;
			}
		}
		catch (InvalidIme& e)
		{
			cout << e.what() << endl;
		}
	}
	cout << "Unesite Prezime." << endl;
	while (1)
	{
		cin >> PrezimeRadnikT;
		try {
			if (!ValidnoIme(PrezimeRadnikT))
			{
				throw InvalidIme();
			}
			else {
				Prezime = PrezimeRadnikT;
				break;
			}
		}
		catch (InvalidIme& e)
		{
			cout << e.what() << endl;
		}
	}
	cout << "Unesite Email." << endl;


	ofstream file(KorisnickoImeRadnikaT + "_radnikTehnicki.txt");
	try {
		if (!file.is_open())
		{
			throw FajlNijeOtvoren();
		}
		else
		{
			file << "Korisnicko ime:" << KorisnickoImeRadnikaT << "\n";
		}
	}
	catch (FajlNijeOtvoren& e)
	{
		cout << e.what() << endl;
	}
	//TODO: implementirati ostalo

}

void AdminTehnicki::obrisiRadnikaTehnicki()
{
	string KorisnickoImeRadnikaT;

	if (!provjeriKorisnickoImeAdminT(KorisnickoImeRadnikaT + "_radnikTehnicki"))
	{
		cout << "Nalog nije pronadjen." << endl;
	}
	else
	{
		if (remove((KorisnickoImeRadnikaT + "_radnikTehnicki.txt").c_str()) == 0) {
			cout << "Nalog radnika tehnickog pregleda uspjesno obrisan." << endl;
		}
		else {
			cout << "Greska prilikom brisanja naloga." << endl;
		}
	}
}

//Funkcija za pregled svih radnika za tehnicki pregled gdje se ispisuju korisnicka imena
// <filesystem> omogucava rad sa fajl sistemom, pruzajuci funkcionalnosti za manipulaciju fajlovima
// prolazi kroz sve fajlove u trenutnom direktorijumu ("./"), entry.path().filename().string() uzima putanju trenutnog fajla u iteraciji,
// zatim dohvata samo ime fajla
//dodatno mozemo imati funckiju gdje na osnovu tih imena pristupamo datoteci za jos detaljnije informacija 
<<<<<<< HEAD
//kao sto su email, ime, prezime itd. sto se radi u f-ji isipiInfoRadnika()
=======
//kao sto su email, ime, prezime itd. sto se radi u f-ji isipiInfoRadnika
>>>>>>> develop
void AdminTehnicki::PregledNalogaRadnika()
{
	for (const auto& entry : fs::directory_iterator("./")) { //Ovo je trenutni direktorijum 
		string imeFajla = entry.path().filename().string();

		if (imeFajla.find("_radnikTehnicki.txt") != string::npos) {
			cout << "Radnik: " << imeFajla.substr(0, imeFajla.find("_radnikTehnicki.txt")) << endl;
		}
	}
}

void AdminTehnicki::ispisInfoRadnika(string userNameRadnikT)
{
	radnikTehnicki.ispisFajla(userNameRadnikT);
}

bool AdminTehnicki::provjeriKorisnickoImeAdminT(const string username)
{
	ifstream file(username + "_administratorTehnicki.txt");
	return file.good();
}

<<<<<<< HEAD
#endif
=======
>>>>>>> develop
