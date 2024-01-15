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
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, AR_korisnickoIme);

	while (!provjeriKorisnickoImeAdminaR(AR_korisnickoIme)) {
		cout << "Korisnicko ime nije pronadjeno! Molim unesite ponovo." << endl;
		getline(cin, AR_korisnickoIme);
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
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, KorisnickoImeRadnikaR);

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

void AdminRegistracija::PregledNalogaRadnika()
{
	if (provjeriUlogovanje() != true)
	{
		cout << "Potrebno je da se ulogujete!" << endl;
		return;
	}
	cout << "Pregled svih radnika za registraciju: " << endl;
	for (const auto& entry : std::filesystem::directory_iterator(putanja))
	{
		ifstream file(entry.path());
		string linija;
		while (getline(file, linija))
		{
			if (linija == "funkcija:radnikR")
			{
				cout << endl << entry.path().filename().string().substr(0, entry.path().filename().string().length() - 4) << endl;
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
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Unesite Ime." << endl;
	while (1)
	{
		getline(cin,ImeRadnikaR);
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
		getline(cin,PrezimeRadnikR);
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
		getline(cin, EmailRadnikaR);
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
	getline(cin,KorisnickoImeRadnikaR);
	while (radnikRegistracija.provjeriKorisnickoImeRadnikaR(KorisnickoImeRadnikaR))
	{
		cout << "Korisnicko Ime zauzeto. Unesite ponovo." << endl;
		getline(cin, KorisnickoImeRadnikaR);
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
		cout << "6: Pregled zahtjeva za resetovanje lozinke" << endl;
		cout << "7. Odjava" << endl;
		cout << "Unesite izbor: ";
		cin >> izbor;
		bool flag = true;
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
		case 7:
			Odjava();
			this->ulogovan = false;
			this->ulogovan = false;
			kraj = true;
			break;
		case 6:
			if (!ispisiZahtjeve()) {
				cout << "Ne postoje aktivni zahtjevi. " << endl;
				break;
			}
			cout << "Zelite li odobriti promjenu sifre nekom od korisnika <da/ne>: " << endl;
			do {
				string odgovor;
				cin >> odgovor;
				if (odgovor == "da" || odgovor == "Da") {
					cout << "Kojem korisniku zelite omoguciti promjenu sifre:" << endl;
					string korisnik;
					cin >> korisnik;
					odobriZahtjev(korisnik);
					flag = true;
				}
				else if (odgovor == "ne" || odgovor == "Ne") flag = false;
				else cout << "Nepostojeca komanda. Pokusajte ponovo." << endl;
			} while (flag == true);
			cout << "Izmjene uspjesno izvrsene." << endl;
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
