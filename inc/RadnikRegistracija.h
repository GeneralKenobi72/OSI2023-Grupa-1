#pragma once
#pragma once
#include <iostream>
#include "User.h"
#include "Radnik.h"
#include <string>
#include <fstream>
using namespace std;

class RadnikR : public Radnik {
private:
	// Vraæa podstring od poèetka do pozicije underscore-a
	string fileUsernameRadnikT(const string filename) {
		size_t underscorePos = filename.find('_');
		if (underscorePos != string::npos) {

			string R_username = filename.substr(0, underscorePos);
			return R_username;
		}
		else {
			return NULL;
		}
	}
	bool isUserNameTakenR(const string username)
	{
		ifstream file(username + "_radnikRegistracija.txt");
		return file.good();
	}
public:
	RadnikR() noexcept : Radnik() {}

	//Ovjde se pohranjuju info. o nekom radniku za tehnièki pregled iz postojece datoteke
	void setInfo(string username)
	{
		try {
			if (!isUserNameTakenR(username))
			{
				throw UserNameNotFound();
			}
		}
		catch (const UserNameNotFound& e)
		{
			cout << e.what() << endl;
		}

		ifstream out(username + "_radnikRegistracija.txt");
		try {
			if (!out.is_open())
			{
				throw FileNotOpen();
			}
		}
		catch (const FileNotOpen& e)
		{
			cout << e.what() << endl;
		}
		string R_Username, R_Password, R_FirstName, R_LastName, R_Email, R_birthDate, R_position;
		getline(out, R_Username); ignore_colon(R_Username);
		username = R_Username;
		getline(out, R_Password); ignore_colon(R_Password);
		password = R_Password;
		getline(out, R_FirstName);  ignore_colon(R_FirstName);
		first_name = R_FirstName;
		getline(out, R_LastName);  ignore_colon(R_LastName);
		last_name = R_LastName;
		getline(out, R_Email); ignore_colon(R_Email);
		email = R_Email;
		getline(out, R_birthDate); ignore_colon(R_birthDate);
		birthDate = R_birthDate;
		getline(out, R_position); ignore_colon(R_position);
		position = R_position;
	}

	void printFromFile(string username)
	{
		try {
			if (!isUserNameTakenR(username))
			{
				throw UserNameNotFound();
			}
		}
		catch (const UserNameNotFound& e)
		{
			cout << e.what() << endl;
		}
		ifstream out(username + "_radnikRegistracija.txt");
		try {
			if (!out.is_open())
			{
				throw FileNotOpen();
			}
		}
		catch (const FileNotOpen& e)
		{
			cout << e.what() << endl;
		}
		string R_Username, R_Password, R_FirstName, R_LastName, R_Email, R_birthDate, R_position;
		getline(out, R_Username);
		cout << "Username from file: "; ignore_colon(R_Username);
		getline(out, R_Password);
		cout << "Password from file: "; ignore_colon(R_Password);
		getline(out, R_FirstName);
		cout << "First Name from file: "; ignore_colon(R_FirstName);
		getline(out, R_LastName);
		cout << "Last Name from file: "; ignore_colon(R_LastName);
		getline(out, R_Email);
		cout << "Email from file: ";  ignore_colon(R_Email);
		getline(out, R_birthDate);
		cout << "BirthDate from file: "; ignore_colon(R_birthDate);
		getline(out, R_position);
		cout << "Position from file: "; ignore_colon(R_position);
	}

	void LogIn()
	{
		string R_username, R_password, result,
			username_result, password_result;
		cout << "Enter your username" << endl;
		cin >> R_username;

		while (!isUserNameTakenR(R_username)) {
			cout << "Korisnicko ime nije pronadjeno! Molim unesite ponovo." << endl;
			cin >> R_username;
		}

		ifstream file(R_username + "_radnikRegistracija.txt");
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
		R_password = Enter_password();
		while (1)
		{
			if (R_password != result)
			{
				cout << "Incorrect password. Please enter again." << endl;
				R_password = Enter_password();
			}
			else
			{
				cout << "Welcome " << username_result << " back!" << endl;
				break;
			}
		}
	}

};