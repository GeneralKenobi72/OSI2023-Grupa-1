#ifndef GETCH_H
#define GETCH_H

#include "Korisnik.h"
#include "Admin.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Izuzeci.h"
#include <filesystem>
#include "Izuzeci.h"
#include "RadnikTehnicki.h"
#include "AdminTehnicki.h"
namespace fs = std::filesystem;
using namespace std;

bool AdminTehnicki::Ulogovanje()
{
	string AT_korisnickoIme, AT_sifra, rezultat,
		korisnickoIme_rezultat, sifra_rezultat;
	cout << "Unesite korisnicko ime" << endl;
	cin >> AT_korisnickoIme;
	while (!provjeriKorisnickoImeAdminT(AT_korisnickoIme)) {
		cout << "Korisnicko ime nije pronadjeno! Molim unesite ponovo." << endl;
		cin >> AT_korisnickoIme;
	}

	ifstream file(putanja+AT_korisnickoIme + ".txt");
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
	AT_sifra = UnesiSifru();
	string AT_rezultat;
	while (1)
	{
		if (AT_sifra != rezultat)
		{
			cout << "Netacna sifra. Molim unesite ponovo." << endl;
			AT_sifra = UnesiSifru();
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

void AdminTehnicki::dodajRadnikaTehnicki()
{
	string KorisnickoImeRadnikaT, LozinkaRadnikaT,
		ImeRadnikaT, PrezimeRadnikT, EmailRadnikaT,DatumRodjenjaRT;
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
				radnikTehnicki.postaviIme( ImeRadnikaT);
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
				 radnikTehnicki.postaviPrezime( PrezimeRadnikT);
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
		cin >> EmailRadnikaT;
		try {
			if (ValidanEmail(EmailRadnikaT))
			{
				radnikTehnicki.postaviEmail(EmailRadnikaT);
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
	radnikTehnicki.postaviPozicija();
	cout << "Unesite korisnicko ime." << endl;
	cin >> KorisnickoImeRadnikaT;
	while (radnikTehnicki.provjeriKorisnickoImeRadnikaT(KorisnickoImeRadnikaT))
	{
		cout << "Korisnicko Ime zauzeto. Unesite ponovo." << endl;
		cin >> KorisnickoImeRadnikaT;
	}
	radnikTehnicki.postaviKorisnickoIme(KorisnickoImeRadnikaT);
	cout << "Unesite sifru." << endl;
	int i = 0;
	do {
		LozinkaRadnikaT = radnikTehnicki.UnesiSifru();
		i++;
	} while (i < 10 && !ValidnaSifra(LozinkaRadnikaT));
	radnikTehnicki.postaviSifra(LozinkaRadnikaT);
	cout << "Proces autentifikacije..." << endl;
	if (podaciValidni) {
		//ovjde mozemo dodati sleep() da se ceka neko vrijeme dok se ne izvrsi autentifikacija
		ofstream file(putanja+KorisnickoImeRadnikaT + ".txt");
		try {
			if (!file.is_open())
			{
				throw FajlNijeOtvoren();
			}
			else
			{
				file << "Korisnicko ime:" << KorisnickoImeRadnikaT << "\n";
				file << "Sifra:" << LozinkaRadnikaT << "\n";
				file << "Ime:" << ImeRadnikaT << "\n";
				file << "Prezime:" << PrezimeRadnikT << "\n";
				file << "Email:" << EmailRadnikaT << "\n";
				file << "funkcija:" << "radnikT" << "\n";
				cout << "Uspjesno kreiran nalog." << endl;
				radnikTehnicki.setRegistraciju();
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

void AdminTehnicki::obrisiRadnikaTehnicki()
{
	if (provjeriUlogovanje() != true)
	{
		cout << "Potrebno je da se ulogujete!" << endl;
		return;
	}
	string KorisnickoImeRadnikaT;
	cout << "Unesite korisnicko ime radnika za tehnicki ciji se nalog brise." << endl;
	cin >> KorisnickoImeRadnikaT;

	cout << "Da li ste sigurni da zelite obrisati nalog radnika " << KorisnickoImeRadnikaT << "?(da/Ne)" << endl;
	string daNe;
	cin >> daNe;
	if(daNe != "da")
		return;

	if (!radnikTehnicki.provjeriKorisnickoImeRadnikaT(KorisnickoImeRadnikaT))
	{
		cout << "Nalog nije pronadjen." << endl;
	}
	else
	{
		if (remove((putanja+KorisnickoImeRadnikaT + ".txt").c_str()) == 0) {
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
//kao sto su email, ime, prezime itd. sto se radi u f-ji isipiInfoRadnika
void AdminTehnicki::PregledNalogaRadnika()
{
	if (provjeriUlogovanje() != true)
	{
		cout << "Potrebno je da se ulogujete!" << endl;
		return;
	}
	for (const auto& entry : fs::directory_iterator(putanja)) { //Ovo je trenutni direktorijum 
		string imeFajla = entry.path().filename().string();

		if (imeFajla.find("_radnikTehnicki.txt") != string::npos) {
			cout << "Radnik: " << imeFajla.substr(0, imeFajla.find("_radnikTehnicki.txt")) << endl;
		}
	}
}

void AdminTehnicki::ispisInfoRadnika(string userNameRadnikT)
{
	if (provjeriUlogovanje() != true)
	{
		cout << "Potrebno je da se ulogujete!" << endl;
		return;
	}
	radnikTehnicki.ispisFajla(userNameRadnikT);
}

bool AdminTehnicki::provjeriAdminTehnicki(string korisnickoIme_, string sifra_)
{
	ifstream fajl(putanja + korisnickoIme_ + ".txt");
	if (!fajl.is_open())
	{
		//cout << "Greska pri pristupu datoteke AT." << endl;
		return false;
	}
	string linija1, linija2;
	getline(fajl, linija1);
	getline(fajl, linija2);
	string rez1 = vrati_ignorisiDvotacku(linija1);
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
		if (rez2 != sifra_)
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

bool AdminTehnicki::provjeriKorisnickoImeAdminT(const string username)
{
	ifstream file(putanja+username + ".txt");
	return file.good();
}
void AdminTehnicki::prikaziMeni()
{
	bool kraj = false;
	string ime;
	while (!kraj) {
		int izbor;
		cout << endl;
		cout << "Meni za Admina T" << endl;
		cout << "1. Dodaj Radnika za Tehnicki" << endl;
		cout << "2. Obrisi radika za Tehnicki" << endl;
		cout << "3. Pregled radnika za Tehnicki" << endl;
		cout << "4. Ispis detaljnijih informacija o radniku" << endl;
		cout << "5. Odjava" << endl;
		cout << "Unesite izbor: ";
		cin >> izbor;

		switch (izbor) {
		case 1:
			dodajRadnikaTehnicki();
			break;
		case 2:
			obrisiRadnikaTehnicki();
			break;
		case 3:
			PregledNalogaRadnika();
			break;
		case 4:
			cout << "Unesite korisnicko ime radnika." << endl;
			cin >> ime;
			ispisInfoRadnika(ime);
			break;
		case 5:
			Odjava();
			kraj = true;
			break;
		default:
			cout << "Nepostojeca opcija!" << endl;
			break;
		}
	}
}

#endif
