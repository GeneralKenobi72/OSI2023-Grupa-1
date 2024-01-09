#include "RadnikRegistracija.h"
#include "RadnikTehnicki.h"
#include "Radnik.h"
#include "Klijent.h"
#include "Korisnik.h"
#include "AdminTehnicki.h"
#include "AdminRegistracija.h"
#include <filesystem>
#include <fstream>
#include <functional>
namespace fs = std::filesystem;
using namespace std;
#include <string>
#ifdef _WIN32
string putanja = "data\\";
#else
string putanja = "data/";
#endif
/*Korisnik* autentifikacija(int tipKorisnika, AdminRegistracija& adminR, AdminTehnicki& adminT) {
    if (tipKorisnika == 1) { // AdminTehnicki
        string korisnickoIme, sifra;
        cout << "Unesite korisnicko ime: ";
        cin >> korisnickoIme;
        cout << "Unesite sifru: ";
        AdminTehnicki admin;
        sifra = admin.UnesiSifru();
        if (admin.provjeriAdminTehnicki(korisnickoIme, sifra)) {
            return new AdminTehnicki(true);
        }
        else {
            cout << "Niste ovlasteni administrator za tehnicki pregled i ne mozete se prijaviti kao administrator." << endl;
            return nullptr;
        }
    }
    else if (tipKorisnika == 2) { //AdminRegistrcija
        string korisnickoIme, sifra;
        cout << "Unesite korisnicko ime: ";
        cin >> korisnickoIme;
        cout << "Unesite sifru: ";
        AdminRegistracija admin;
        sifra = admin.UnesiSifru();
        if (admin.provjeriAdminRegistracija(korisnickoIme, sifra)) {
            return new AdminRegistracija(true);
        }
        else {
            cout << "Niste ovlasteni administrator za registraciju i ne mozete se prijaviti kao administrator." << endl;
            return nullptr;
        }
    }
    else if (tipKorisnika == 3) { // RadnikTehnicki
        string korisnickoIme, sifra;
        cout << "Unesite korisnicko ime: ";
        cin >> korisnickoIme;
        cout << "Unesite sifru: ";
        RadnikT radnik;
        sifra = radnik.UnesiSifru();
        function<void()> funkcijaDodajRadnikaT = [&adminT]() {
            adminT.dodajRadnikaTehnicki();
            };
        if (radnik.provjeriRadnikaTehnicki(korisnickoIme, sifra)) {
            return new RadnikT(true);
        }
        else {
            cout << "Izgleda da nemate nalog." << endl;
            cout << "Nova registracija? (da/Da)" << endl;
            string da;
            cin >> da;
            if (da == "da" || da == "Da")
            {
                cout << "Prikaz Meni" << endl;
                return new RadnikT(funkcijaDodajRadnikaT);
            }
            else
            {
                return nullptr;
            }
        }
    }
    else if (tipKorisnika == 4) //RadnikRegistracija
    {
        string korisnickoIme, sifra;
        cout << "Unesite korisnicko ime: ";
        cin >> korisnickoIme;
        cout << "Unesite sifru: ";
        RadnikR radnik;
        sifra = radnik.UnesiSifru();
        function<void()> funkcijaDodajRadnikaR = [&adminR]() {
            adminR.dodajRadnikaRegistracija();
            };
        if (radnik.provjeriRadnikaRegistracija(korisnickoIme, sifra)) {
            return new RadnikR(true);
        }
        else {
            cout << "Izgleda da nemate nalog." << endl;
            cout << "Nova registracija? (da/Da)" << endl;
            string da;
            cin >> da;
            if (da == "da" || da == "Da")
            {
                cout << "Prikaz Meni" << endl;
                return new RadnikR(funkcijaDodajRadnikaR);
            }
            else {
                return nullptr;
            }
        }

    }
    else
    {
        return new Klijent();
    }
}
int odrediTipKorisnika() {
    int izbor;
    cout << "Odaberite tip korisnika:" << endl;
    cout << "1. Administrator za Tehnicki Pregled" << endl;
    cout << "2. Administrator za Registraciju" << endl;
    cout << "3. Radnik za Tehnicki Pregled " << endl;
    cout << "4. Radnik za Registraciju" << endl;
    cout << "5. Klijent" << endl;
    cout << "0. Izlaz iz programa" << endl;
    cout << "Unesite broj: ";
    cin >> izbor;
    return izbor;
}
bool potvrdaIzbora(int tipKorisnika) {
    string odgovor;
    cout << "Izabrali ste tip korisnika: " << tipKorisnika << ". Da li ste sigurni? (da/ne): ";
    cin >> odgovor;
    return odgovor == "da";
}*/
Korisnik* koSeLoguje(string korisnickoIme) {
	string Ime, Prezime, Sifra, Email, s;
	ifstream file(putanja+korisnickoIme+".txt");
	cout << korisnickoIme << endl;
	try {
		if (!file.is_open())
		{
			throw FajlNijeOtvoren();
		}
		else
		{
			getline(file, s);
			getline(file, Sifra);
			Sifra = Korisnik::vrati_ignorisiDvotacku(Sifra);
			getline(file, Ime);
			Ime = Korisnik::vrati_ignorisiDvotacku(Ime);
			getline(file, Prezime);
			Prezime = Korisnik::vrati_ignorisiDvotacku(Prezime);
			getline(file, Email);
			Email = Korisnik::vrati_ignorisiDvotacku(Email);
			getline(file, s);
			s = Korisnik::vrati_ignorisiDvotacku(s);
		}
	}
	catch (const FajlNijeOtvoren& e)
	{
		cout << e.what() << endl;
		return nullptr;
	}
	cout << "Ime: " << Ime << " Funckija: " << s << endl;
	if(s == "klijent"){
		Klijent* k = new Klijent(Ime, Prezime, korisnickoIme, Sifra, Email);
		return k;
	} else if(s == "adminT") {
		AdminTehnicki* a = new AdminTehnicki(Ime,Prezime,korisnickoIme,Sifra,Email);
		return a;
	} else if(s == "adminR") {
		AdminRegistracija* a = new AdminRegistracija(Ime,Prezime,korisnickoIme,Sifra,Email);
		return a;
	} else if(s == "radnikT") {
		RadnikT* r = new RadnikT(Ime,Prezime,korisnickoIme,Sifra,Email);
		return r;
	} else if(s == "radnikR") {
		RadnikR* r = new RadnikR(Ime,Prezime,korisnickoIme,Sifra,Email);
		return r;
	}
	return nullptr;
}

bool provjeriKorisnickoIme(string s) {
	ifstream file(putanja+s+".txt");
	return file.good();
}

bool ulogujSe() {
	string korisnickoImeUnos, sifraUnos,
		   korisnickoIme, sifra;
	do {
		std::cout << "Unesite korisnicko ime:";
		std::cin >> korisnickoImeUnos;
	} while(!provjeriKorisnickoIme(korisnickoImeUnos));

	ifstream file(putanja+korisnickoImeUnos+".txt");
	try {
		if (!file.is_open())
		{
			throw FajlNijeOtvoren();
		}
		else
		{
			getline(file, korisnickoIme);
			getline(file, sifra);
			sifra = Korisnik::vrati_ignorisiDvotacku(sifra);
		}
	}
	catch (const FajlNijeOtvoren& e)
	{
		cout << e.what() << endl;
		return false;
	}
	cout << "Unesite sifru" << endl;
	sifraUnos = Korisnik::UnesiSifru();
	while (1)
	{
		if (sifraUnos != sifra)
		{
			cout << "Netacna sifra. Molim unesite ponovo." << endl;
			sifraUnos = Korisnik::UnesiSifru();
		}
		else
		{
			Korisnik* k = koSeLoguje(korisnickoImeUnos);
			cout << "Dobrodosli " << korisnickoImeUnos << " nazad!" << endl;
			k->prikaziMeni();
			delete(k);
			break;
		}
	}
	return true;
}


int pocetniMeni() {
	std::cout << "====================================\n";
	std::cout << "Softver za registraciju vozila\n";
	std::cout << "Opcije:\n";
	std::cout << "1: Registracija\n";
	std::cout << "2: Log in\n";
	std::cout << "3: Kraj rada\n";
	int opcija;
	std::cin >> opcija;
	return opcija;
}

string unesi_sifru(){
    string novaSifra;
	char ch;
	ch = getChar();
	std::cout << std::flush;
#ifdef _WIN32
	while (ch!=13) {  // Provjeri za ENTER key ASCII 13
#else
	while (ch!='\n') {
#endif
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

int main()
{
    /*
     while (true) {
        int tipKorisnika = odrediTipKorisnika();

        if (tipKorisnika == 0) {
            cout << "Izlaz iz programa." << endl;
            break;
        }

        if (tipKorisnika < 1 || tipKorisnika > 5) {
            cout << "Neispravan unos! Molimo pokusajte ponovo." << endl;
            continue;
        }

        if (!potvrdaIzbora(tipKorisnika)) {
            cout << "Pogresan unos, molimo unesite ponovo." << endl;
            continue;
        }

        AdminTehnicki adminT;
        AdminRegistracija adminR;

        Korisnik* korisnik = autentifikacija(tipKorisnika, adminR, adminT);
        if (korisnik) {
            korisnik->prikaziMeni();
            if (tipKorisnika != 3) {
                delete korisnik;
            }
        }

        cout << "Da li zelite da nastavite? (da/ne): ";
        string odgovor;
        cin >> odgovor;
        if (odgovor != "da") {
            break;
        }
    }*/
    
    /*string korisnickoIme;
    string sifra;
   
    cout << "Unesite korisnicko ime: ";
    cin >> korisnickoIme;
    cout << "Unesite sifru: ";
    sifra = unesi_sifru();
 
    Korisnik* prijavljeniKorisnik = nullptr;
   
    Korisnik* adminRegistracija = new AdminRegistracija();
    prijavljeniKorisnik = adminRegistracija->provjeri(korisnickoIme, sifra);
    if (prijavljeniKorisnik) {
        prijavljeniKorisnik->prikaziMeni();
        delete prijavljeniKorisnik;
    }
    delete adminRegistracija;

    // Provjeri admina za tehnicki pregled
    Korisnik* adminTehnicki = new AdminTehnicki();
    prijavljeniKorisnik = adminTehnicki->provjeri(korisnickoIme, sifra);
    if (prijavljeniKorisnik) {
        prijavljeniKorisnik->prikaziMeni();
        delete prijavljeniKorisnik;
    }
    delete adminTehnicki;

    // Provjeri radnika za registraciju
    Korisnik* radnikRegistracija = new RadnikR();
    prijavljeniKorisnik = radnikRegistracija->provjeri(korisnickoIme, sifra);
    if (prijavljeniKorisnik) {
        prijavljeniKorisnik->prikaziMeni();
        delete prijavljeniKorisnik;
    }
    delete radnikRegistracija;

    // Provjeri radnika za tehnicki pregled
    Korisnik* radnikTehnicki = new RadnikT();
    prijavljeniKorisnik = radnikTehnicki->provjeri(korisnickoIme, sifra);
    if (prijavljeniKorisnik) {
        prijavljeniKorisnik->prikaziMeni();
        delete prijavljeniKorisnik;
    }
    delete radnikTehnicki;

    // Provjeri klijenta
    Korisnik* klijent = new Klijent();
    prijavljeniKorisnik = klijent->provjeri(korisnickoIme, sifra);
    if (prijavljeniKorisnik) {
        prijavljeniKorisnik->prikaziMeni();
        delete prijavljeniKorisnik;
    }
    delete klijent;

    // Ako nijedan nije prijavljen
    if (!prijavljeniKorisnik) {
        cout << "Niste prijavljeni. Provjerite korisnicko ime i sifru." << endl;
        return 0;
    }
    return 0;*/


	while(true) {
		int opcija = pocetniMeni();
		if(opcija == 1) {
			Klijent k(false);
			k.novaRegistracija();	
		}
		if(opcija == 2)
			ulogujSe();
		if(opcija == 3){
			return 0;
		}
	}
}

