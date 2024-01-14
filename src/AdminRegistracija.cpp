#ifndef GETCH_H
#define GETCH_H

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

bool AdminRegistracija::Ulogovanje()
{
	string AR_korisnickoIme, AR_sifra, rezultat,
		korisnickoIme_rezultat, sifra_rezultat;
	cout << "Unesite korisnicko ime" << endl;
	cin >> AR_korisnickoIme;

	while (!provjeriKorisnickoImeAdminaR(AR_korisnickoIme)) {
		cout << "Korisnicko ime nije pronadjeno! Molim unesite ponovo." << endl;
		cin >> AR_korisnickoIme;
	}

	ifstream file(putanja+AR_korisnickoIme + ".txt");
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
		return false;
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
			break;
		}
	}
	ulogovan = true;
	return true;
}

void AdminRegistracija::obrisiRadnikaRegistracija()
{
	if (provjeriUlogovanje() != true)
	{
		cout << "Potrebno je da se ulogujete!" << endl;
		return;
	}
	string KorisnickoImeRadnikaR;
	cout << "Unesite korisnicko ime radnika za registraciju." << endl;
	cin >> KorisnickoImeRadnikaR;

	cout << "Da li ste sigurni da zelite obrisati nalog radnika " << KorisnickoImeRadnikaR << "?(da/Ne)" << endl;
	string daNe;
	cin >> daNe;
	if(daNe != "da")
		return;

	if (!radnikRegistracija.provjeriKorisnickoImeRadnikaR(KorisnickoImeRadnikaR))
	{
		cout << "Nalog nije pronadjen." << endl;
	}
	else
	{
		if (remove((putanja+KorisnickoImeRadnikaR + ".txt").c_str()) == 0) {
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
	for (const auto& entry : fs::directory_iterator("data")) {
		if(fs::is_regular_file(entry.path())) {
			std::ifstream fajl(entry.path());
			if(!fajl.is_open()) {
				std::cerr << "Nemoguce otvoriti fajl: " << putanja << std::endl;
				continue;
			}
			std::string linija;
			int brojLinije = 0;
			bool pronadjen = false;
			while(std::getline(fajl, linija)) {
				brojLinije++;
				if(linija == ("funkcija:radnikR")) {
					pronadjen = true;
					break;
				}
			}
			fajl.close();
			if(pronadjen) {
				std::ifstream fajl(putanja);
				if(!fajl.is_open()) {
					std::cerr << "Nemoguce otvoriti fajl: " << putanja << std::endl;
					continue;
				}
				int i=0;
				while(std::getline(fajl, linija)) {
					if(i != 1) {
						std::cout << linija << endl;
					}
					i++;
				}
				std::cout << std::endl;
			}
		}

	}
}

void AdminRegistracija::ispisInfoRadnika(string userNameRadnikR)
{
	if (provjeriUlogovanje() != true)
	{
		cout << "Potrebno je da se ulogujete!" << endl;
		return;
	}

	radnikRegistracija.ispisFajla(userNameRadnikR);
}


bool AdminRegistracija::provjeriAdminRegistracija(string korisnickoIme_, string sifra_)
{
	ifstream fajl(putanja + korisnickoIme_ + ".txt");
	if (!fajl.is_open())
	{
		//cout << "Greska pri pristupu datoteke AR." << endl;
		return false;
	}
	string linija1, linija2;
	getline(fajl, linija1);
	getline(fajl, linija2);
	string rez1= vrati_ignorisiDvotacku(linija1);
	string rez2 = vrati_ignorisiDvotacku(linija2);
	int i = 0;
	for (; i < 3; i++)
	{
		if (rez1 != korisnickoIme_)
		{
			cout << "Unesite korisnicko ime ponovo." << endl;
			cin >> korisnickoIme_;
		}
		else
		{
			break;
		}
	}
	if (i == 3)
	{
		cout << "Pogresno korisnicko ime." << endl;
		return false;
	}
	i = 0;
	for (; i < 3; i++)
	{
		if (rez2!= sifra_)
		{
			cout << "Unesite sifru ponovo. " << endl;
			sifra_ = UnesiSifru();
		}
		else
		{
			break;
		}
	}
	if (i == 3)
	{
		cout << "Pogresna sifra." << endl;
		return false;
	}
	return true;
}

void AdminRegistracija::dodajRadnikaRegistracija()
{
	if (provjeriUlogovanje() != true)
	{
		cout << "Potrebno je da se ulogujete!" << endl;
		return;
	}
	string KorisnickoImeRadnikaR, LozinkaRadnikaR,
		ImeRadnikaR, PrezimeRadnikR, EmailRadnikaR, DatumRodjenjaRR;

	cout << "Unesite Ime." << endl;
	while (1)
	{
		cin >> ImeRadnikaR;
		try {
			if (!ValidnoIme(ImeRadnikaR))
			{
				throw InvalidIme();
			}
			else {
				radnikRegistracija.postaviIme(ImeRadnikaR);
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
		cin >> PrezimeRadnikR;
		try {
			if (!ValidnoIme(PrezimeRadnikR))
			{
				throw InvalidIme();
			}
			else {
				radnikRegistracija.postaviPrezime(PrezimeRadnikR);
				break;
			}
		}
		catch (InvalidIme& e)
		{
			cout << e.what() << endl;
		}
	}
	cout << "Unesite Email." << endl;
	while (1) {
		cin >> EmailRadnikaR;
		try {
			if (ValidanEmail(EmailRadnikaR))
			{
				radnikRegistracija.postaviEmail(EmailRadnikaR);
				break;
			}
			else
			{
				throw InvalidEmail();
			}
		}
		catch (const InvalidEmail& e)
		{
			cout << e.what() << endl;
		}
	}
	radnikRegistracija.postaviPozicija();

	cout << "Unesite korisnicko ime." << endl;
	cin >> KorisnickoImeRadnikaR;
	while (radnikRegistracija.provjeriKorisnickoImeRadnikaR(KorisnickoImeRadnikaR))
	{
		cout << "Korisnicko Ime zauzeto. Unesite ponovo." << endl;
		cin >> KorisnickoImeRadnikaR;
	}
	radnikRegistracija.postaviKorisnickoIme(KorisnickoImeRadnikaR);

	cout << "Unesite sifru." << endl;
	int i = 0;
	do {
		LozinkaRadnikaR = radnikRegistracija.UnesiSifru();
		i++;
	} while (i < 10 && !ValidnaSifra(LozinkaRadnikaR));
	radnikRegistracija.postaviSifra(LozinkaRadnikaR);

	cout << "Proces autentifikacije..." << endl;
	if (podaciValidni) {
		// Ovdje mozemo dodati sleep()
		ofstream file(putanja + KorisnickoImeRadnikaR + ".txt");
		try {
			if (!file.is_open())
			{
				throw FajlNijeOtvoren();
			}
			else
			{
				file << "Korisnicko ime:" << KorisnickoImeRadnikaR << "\n";
				file << "Sifra:" << LozinkaRadnikaR << "\n";
				file << "Ime:" << ImeRadnikaR << "\n";
				file << "Prezime:" << PrezimeRadnikR << "\n";
				file << "Email:" << EmailRadnikaR << "\n";;
				file << "funkcija:" << "radnikR" << "\n";
				cout << "Uspjesno kreiran nalog." << endl;
				radnikRegistracija.setRegistraciju();
			}
		}
		catch (FajlNijeOtvoren& e)
		{
			cout << e.what() << endl;
			return;
		}
	}
	else {
		cout << "Zahtijev za registraciju nije odobren. Molim pokusajte ponovo." << endl;
	}

}

bool AdminRegistracija::provjeriKorisnickoImeAdminaR(const string username)
{
	ifstream file(putanja+username + ".txt");
	return file.good();
}

void AdminRegistracija::prikaziMeni()
{
	bool kraj = false;
	string ime;
	while (!kraj) {
		int izbor;
		cout << endl;
		cout << "Meni za Admina Registracija" << endl;
		cout << "1. Dodaj Radnika za Registraciju" << endl;
		cout << "2. Obrisi radika za Registraciju" << endl;
		cout << "3. Pregled radnika za Registraciju" << endl;
		cout << "4. Pretrazivanje radnika za Registraciju" << endl;
		cout << "5. Ispis detaljnijih informacija o radniku" << endl;
		cout << "6. Odjava" << endl;
		cout << "Unesite izbor: ";
		cin >> izbor;

		switch (izbor) {
		case 1:
			dodajRadnikaRegistracija();
			break;
		case 2:
			obrisiRadnikaRegistracija();
			break;
		case 3:
			PregledNalogaRadnika();
			break;
		case 4:
			pretrazivanjeNalogaRadnika();
			break;
		case 5:
			cout << "Unesite korisnicko ime radnika." << endl;
			cin >> ime;
			ispisInfoRadnika(ime);
			break;
		case 6:
			Odjava();
			this->ulogovan = false;
			this->ulogovan = false;
			kraj = true;
			break;
		default:
			cout << "Nepostojeca opcija!" << endl;
			break;
		}
	}
}

void AdminRegistracija::pretrazivanjeNalogaRadnika() {
	std::cout << "Parametri za pretragu radnika:\n";
	std::cout << "1. Korisnicko ime\n";
	std::cout << "2. Ime\n";
	std::cout << "3. Prezime\n";
	std::cout << "4. Email\n";
	std::cout << "5. Nazad\n";
	std::cout << "Unos: ";

	int opcija;
	do {
		std::cin >> opcija;
	} while(opcija>5 || opcija<1);
	std::cout << "Unesite parametar: ";
	std::string informacija;
	std::cin >> informacija;

	if(opcija == 1) {
		pronadjiRadnike("Korisnicko", informacija, "radnikR");
	} else if(opcija == 2) {
		pronadjiRadnike("Ime", informacija, "radnikR");
	} else if(opcija == 3) {
		pronadjiRadnike("Prezime", informacija, "radnikR");
	} else if(opcija == 4) {
		pronadjiRadnike("Email", informacija, "radnikR");
	} else if(opcija == 5) {
		return;
	}
}

#endif
