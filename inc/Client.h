#pragma once
#include <iostream>
#include "User.h"
#include <string>
#include <fstream>
#include <conio.h> 
using namespace std;

class Client : public User {
private:
	//funkcija koja za ispis iz datoteke ignorise naziv do pojave : 
	// tj. "Username:","Password:" itd.
	//funckija za unos sifre, gdje se pri unosom umjesto sifre prikazuje *
public:
	Client() noexcept : User() {}

	Client(const string C_firstName, const string C_lastName, 
		const string C_username,const string C_password, const string c_email)
		: User()
	{
		first_name = C_firstName;
		last_name = C_lastName;
		password = C_password;
		email = c_email;
		userName = C_username;
	}
	
	void writeToFile(string username) 
	{
		ofstream file(username + ".txt",ios::app);
		try {
			if (!file.is_open())
			{
				throw FileNotOpen();
			}
		}
		catch (const FileNotOpen& e)
		{
			cout << e.what() << endl;
		}
		file << "Username:" << username << "\n";
		file << "Password:" << password << "\n";
		file << "First Name:" << first_name << "\n";
		file << "Last Name:" << last_name << "\n";
		file << "Email:" << email << "\n";
	}
	void printFromFile(string username)
	{
		//ovdje provjerava da li je klijent u bazi podataka
		try {
			if (!isUserNameTaken(username))
			{
				throw UserNameNotFound();
			}
		}
		catch (const UserNameNotFound& e)
		{
			cout << e.what() << endl;
		}
		
		ifstream out(username + ".txt");
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
		string Username, Password, FirstName, LastName, Email;
		getline(out, Username);
		cout << "Username from file: "; ignore_colon(Username);
		getline(out, Password);
		cout << "Password from file: "; ignore_colon(Password);
		getline(out,FirstName);
		cout << "First Name from file: "; ignore_colon(FirstName);
		getline(out, LastName);
		cout << "Last Name from file: "; ignore_colon(LastName);
		getline(out, Email);
		cout << "Email from file: ";  ignore_colon( Email);
	}
	void NewRegistration()
	{
		string C_firstName;
		string C_lastName;
		string C_password;
		string C_username;
		string c_email;
		cout << "First Name" << endl;
		while (1)
		{
			cin >> C_firstName;
			try {
				if (!ValidFirstName(C_firstName))
				{
					throw InvalidFName();
				}
				else {
					first_name = C_firstName;
					break;
				}
			}
			catch (InvalidFName& e)
			{
				cout<<e.what()<<endl;
			}
		}
		cout << "Last Name" << endl;
		while (1)
		{
			cin >> C_lastName;
			try {
				if (!ValidLastName(C_lastName))
				{
					throw InvalidLName();
				}
				else {
					last_name = C_lastName;
					break;
				}
			}
			catch (InvalidLName& e)
			{
				cout<<e.what() << endl;
			}
		}
		cout << "Email" << endl;
		while (1) {
			cin >> c_email;
			try {
				if (ValidEmail(c_email))
				{
					email = c_email;
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
		cout << "Username" << endl;
		cin >> C_username;
		string result = check_Username(C_username);
		userName = result;
		cout << "Password" << endl;
		int i = 0;
		do {
			C_password = Enter_password();
			i++;
		} while (i < 10 && !ValidPassword(C_password));
		password = C_password;
		writeToFile(userName);

	}
	void LogIn()
	{
		string C_username, C_password,result,
			username_result, password_result;
		cout << "Enter your username" << endl;
		cin >> C_username;

			ifstream file(C_username + ".txt");
			try {
				if (!file.is_open())
				{
					throw FileNotOpen();
				}
				else
				{
					getline(file, username_result);
					getline(file, password_result);
					result=return_ignore_colon(password_result);
				}
			}
			catch (const FileNotOpen& e)
			{
				cout << e.what() << endl;
			}
			cout << "Enter your password" << endl;
			C_password=Enter_password();
			while (1)
			{
				if (C_password != result)
				{
					cout << "Incorrect password. Please enter again." << endl;
					C_password=Enter_password();
				}
				else
				{
					cout << "Welcome " << username_result << " back!" << endl;
					break;
				}
			}	
	}
};