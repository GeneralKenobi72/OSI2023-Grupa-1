#pragma once
#include "User.h"
#include "Admin.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Exceptions.h"
#include <filesystem>
#include "RadnikTehnièki.h"
namespace fs = std::filesystem;
using namespace std;

class AdminTehnicki : public Admin
{
private:
	RadnikT radnikTehnicki;

public:
	AdminTehnicki() noexcept : Admin() {}

	void Prijava()
	{
		string AT_username, AT_password, result,
			username_result, password_result;
		cout << "Enter your username" << endl;
		cin >> AT_username;

		while (!isUserNameTakenA(AT_username)) {
			cout << "Korisnicko ime nije pronadjeno! Molim unesite ponovo." << endl;
			cin >> AT_username;
		}

		ifstream file(AT_username + "_administratorTehnicki.txt");
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
		cout << "Enter your password" << endl;
		AT_password = Enter_password();
		while (1)
		{
			if (AT_password != result)
			{
				cout << "Incorrect password. Please enter again." << endl;
				AT_password = Enter_password();
			}
			else
			{
				cout << "Welcome " << username_result << " back!" << endl;
				break;
			}
		}
	}

	void dodajRadnikaTehnicki()
	{
		string KorisnickoImeRadnikaT, LozinkaRadnikaT,
			ImeRadnikaT, PrezimeRadnikT, LozinkaRadnikaT, EmailRadnikaT;
		cout << "Unesite korisnicko ime." << endl;
		cin >> KorisnickoImeRadnikaT;
		cout << "Unesite Ime." << endl;
		while (1)
		{
			cin >> ImeRadnikaT;
			try {
				if (!ValidFirstName(ImeRadnikaT))
				{
					throw InvalidFName();
				}
				else {
					first_name = ImeRadnikaT;
					break;
				}
			}
			catch (InvalidFName& e)
			{
				cout << e.what() << endl;
			}
		}
		cout << "Unesite Prezime." << endl;
		while (1)
		{
			cin >> PrezimeRadnikT;
			try {
				if (!ValidFirstName(PrezimeRadnikT))
				{
					throw InvalidFName();
				}
				else {
					last_name = PrezimeRadnikT;
					break;
				}
			}
			catch (InvalidFName& e)
			{
				cout << e.what() << endl;
			}
		}
		cout << "Unesite Email." << endl;


		ofstream file(KorisnickoImeRadnikaT + "_radnikTehnicki.txt");
		try {
			if (!file.is_open())
			{
				throw FileNotOpen();
			}
			else
			{
				file << "Korisnicko ime:" << KorisnickoImeRadnikaT << "\n";
			}
		}
		catch (FileNotOpen& e)
		{
			cout << e.what() << endl;
		}
		//TODO: implementirati ostalo

	}
	void obrisiRadnikaTehnicki()
	{
		string KorisnickoImeRadnikaT;

		if (!isUserNameTakenA(KorisnickoImeRadnikaT + "_radnikTehnicki"))
		{
			cout << "Nalog nije pronadjen." << endl;
		}
		else
		{
			if (remove((KorisnickoImeRadnikaT + "_radnikTehnicki.txt").c_str()) == 0) {
				cout << "Nalog radnika tehnièkog pregleda uspješno obrisan." << endl;
			}
			else {
				cout << "Greška prilikom brisanja naloga." << endl;
			}
		}
	}
	//Funkcija za pregled svih radnika za tehnicki pregled gdje se ispisuju korisnicka imena
	//dodatno mozemo imati funckiju gdje na osnovu tih imena pristupamo datoteci za jos detaljnije informacija 
	//kao sto su email, ime, prezime itd. sto se radi u f-ji isipiInfoRadnika
	void PregledNalogaRadnika()
	{
		for (const auto& entry : fs::directory_iterator("./")) { //Ovo je trenutni direktorijum 
			string filename = entry.path().filename().string();

			if (filename.find("_radnikTehnicki.txt") != string::npos) {
				cout << "Radnik: " << filename.substr(0, filename.find("_radnikTehnicki.txt")) << endl;
			}
		}
	}
	void ispisInfoRadnika(string userNameRadnikT)
	{
		radnikTehnicki.printFromFile(userNameRadnikT);
	}
private:

	bool isUserNameTakenA(const string username)
	{
		ifstream file(username + "_administratorTehnicki.txt");
		return file.good();
	}
};