#pragma once
#include "User.h"
#include "Admin.h"
#include <iostream>
#include <fstream>
#include <string>
#include "RadnikRegistracija.h"
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;

class AdminRegistracija : public Admin
{
private:
	RadnikR radnikRegistracija;
public:
	AdminRegistracija() noexcept : Admin() {}

	void Prijava()
	{
		string AT_username, AT_password, result,
			username_result, password_result;
		cout << "Unesite korisnicko ime." << endl;
		cin >> AT_username;

		while (!isUserNameTakenA(AT_username)) {
			cout << "Korisnicko ime nije pronadjeno! Molim unesite ponovo." << endl;
			cin >> AT_username;
		}
		ifstream file(AT_username + "_administratorRegistracija.txt");
		try {
			if (!file.is_open())
			{
				throw FileNotOpen();
			}
			else
			{
				getline(file, username_result);
				getline(file, password_result);
				result = return_ignore_colon(password_result);
			}
		}
		catch (const FileNotOpen& e)
		{
			cout << e.what() << endl;
		}
		cout << "Unesite sifru." << endl;
		AT_password = Enter_password();
		while (1)
		{
			if (AT_password != result)
			{
				cout << "Netacna sifra! Unesite ponovo." << endl;
				AT_password = Enter_password();
			}
			else
			{
				cout << "Dobrodosli " << username_result << " nazad!" << endl;
				break;
			}
		}
	}

	void obrisiRadnikaTehnicki()
	{
		string KorisnickoImeRadnikaR;

		if (!isUserNameTakenA(KorisnickoImeRadnikaR + "_radnikRegistracija"))
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
	void PregledNalogaRadnika()
	{
		for (const auto& entry : fs::directory_iterator("./")) { //Ovo je trenutni direktorijum 
			string filename = entry.path().filename().string();

			if (filename.find("_radnikRegistracija.txt") != string::npos) {
				cout << "Radnik: " << filename.substr(0, filename.find("_radnikRegistracija.txt")) << endl;
			}
		}
	}
	void ispisInfoRadnika(string userNameRadnikR)
	{
		radnikRegistracija.printFromFile(userNameRadnikR);
	}
private:

	bool isUserNameTakenA(const string username)
	{
		ifstream file(username + "_administratorRegistracija.txt");
		return file.good();
	}

};