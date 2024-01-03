#include <iostream>
#include "Korisnik.h"
#include "Admin.h"
#include <iostream>
#include <fstream>
#include <string>
#include "RadnikRegistracija.h"
#include "AdminRegistracija.h"
#include <filesystem>
using namespace std;

void AdminRegistracija::Prijava()
{
	string AR_korisnickoIme, AR_sifra, rezultat,
		korisnickoIme_rezultat, sifra_rezultat;
	cout << "Unesite korisnicko ime" << endl;
	cin >> AR_korisnickoIme;

	while (!provjeriKorisnickoImeAdminaR(AR_korisnickoIme)) {
		cout << "Korisnicko ime nije pronadjeno! Molim unesite ponovo." << endl;
		cin >> AR_korisnickoIme;
	}

	ifstream file(AR_korisnickoIme + "_administratorRegistracija.txt");
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
	AR_sifra = UnesiSifru();
	string AT_rezultat;
	while (1)
	{
		if (AR_sifra != rezultat)
		{
			cout << "Netacna sifra. Molim unesite ponovo." << endl;
			AR_sifra = UnesiSifru();
		}
		else
		{
			AT_rezultat = vrati_ignorisiDvotacku(korisnickoIme_rezultat);
			cout << "Dobrodosli " << AT_rezultat << " nazad!" << endl;
			cout << "Dobrodosli " << korisnickoIme_rezultat << " nazad!" << endl;
			break;
		}
	}
}

void AdminRegistracija::obrisiRadnikaRegistracija()
{
	string KorisnickoImeRadnikaR;

	if (!provjeriKorisnickoImeAdminaR(KorisnickoImeRadnikaR + "_radnikRegistracija"))
	{
		cout << "Nalog nije pronadjen." << endl;
	}
	else
	{
		if (remove((KorisnickoImeRadnikaR + "_radnikRegistracija.txt").c_str()) == 0) {
			cout << "Nalog radnika za registraciju uspjesno obrisan." << endl;
		}
		else {
			cout << "Greska prilikom brisanja naloga." << endl;
		}
	}
}

//Funkcija za pregled svih radnika za registraciju gdje se ispisuju korisnicka imena
//dodatno mozemo imati funckiju gdje na osnovu tih imena pristupamo datoteci za jos detaljnije informacija 
//kao sto su email, ime, prezime itd. sto se radi u f-ji isipiInfoRadnika

void AdminRegistracija::PregledNalogaRadnika()
{
	for (const auto& entry : fs::directory_iterator("./")) { //Ovo je trenutni direktorijum 
		string fileIme = entry.path().filename().string();

		if (fileIme.find("_radnikRegistracija.txt") != string::npos) {
			cout << "Radnik: " << fileIme.substr(0, fileIme.find("_radnikRegistracija.txt")) << endl;
		}
	}
}

void AdminRegistracija::ispisInfoRadnika(string userNameRadnikR)
{
	radnikRegistracija.ispisFajla(userNameRadnikR);
}

bool AdminRegistracija::provjeriKorisnickoImeAdminaR(const string username)
{
	ifstream file(username + "_administratorRegistracija.txt");
	return file.good();
}
