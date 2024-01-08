#include "RadnikRegistracija.h"
#include "RadnikTehnicki.h"
#include "Radnik.h"
#include "Klijent.h"
#include "AdminTehnicki.h"
#include "AdminRegistracija.h"
#include <filesystem>
#include <functional>
namespace fs = std::filesystem;
using namespace std;
#include <string>
Korisnik* autentifikacija(int tipKorisnika, AdminRegistracija& adminR, AdminTehnicki& adminT) {
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
}
int main()
{
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
    }

    return 0;

}
