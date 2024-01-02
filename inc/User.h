#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "Exceptions.h"
#include <conio.h>
using namespace std;

class User {
public:
	User() noexcept {}
	User(const string user_name,const string password) noexcept : userName(user_name), password(password) {}

	// ove dvije funkcije(ValidFirtName i ValidLastName) su istog pona�anja
	//  moze se koristiti samo jedna za provjeru prvog i zadnjeg imena
	// ali zbog preglednosti su definisane zasebno
	bool ValidFirstName(string firstName)
	{
			int i = 1;
			int length = size(firstName);
			if (!isupper(firstName[0]) || length==0)
			{
				return false;
			}
			else
			{
				while (i < length)
				{
					if (!islower(firstName[i]))
						return false;
					i++;
				}
			}
			//cout << "First name is valid." << endl;
			return true;
	}
	bool ValidLastName(string lastName)
	{
		int i = 1;
		int length = size(lastName);
		if (!isupper(lastName[0]) || length==0)
		{
			return false;
		}
		else
		{
			while (i < length)
			{
				if (!islower(lastName[i]))
					return false;
				i++;
			}
		}
		//cout << "Last name is valid." << endl;
		return true;
	}
	//TODO
	bool ValidEmail(string email)
	{ 
			if (!isalpha(email[0]))
			{
				//cout << "Invalid email input." << endl;
				//throw InvalidEmail();
				return false;
			}
			int at = -1, dot = -1;
			int counter_at = 0, counter_dot = 0;
			for (int i = 0; i < email.size(); i++)
			{
				if (isspace(email[i]))
				{
					//throw InvalidEmail();
					return false;
				}
				else if (email[i] == '@')
				{
					at = i;
					counter_at++;
				}
				else if (email[i] == '.')
				{
					dot = i;
					counter_dot++;
				}
			}
			if (at == -1 || dot == -1)
			{
				//cout << "Invalid email input." << endl;
				return false;
				//throw InvalidEmail();
			}
			if (counter_at >= dot)
			{
				//throw InvalidEmail();
				return false;
			}
			if (counter_dot > 1 || counter_at > 1)
			{
				//throw InvalidEmail();
				return false;
			}
	
			return true;
	}
	//TODO:
	bool ValidPassword(string password)
	{
		int digit = 0, uppercase = 0, lowercase = 0, specialchar = 0;
		try {
			if (password.size() <= 4 && password.size() >= 15)
			{
				throw InvalidPassword();
			}
			else
			{
				if (password.find(" ") == -1)
				{
					for (int i = 0; i < password.length(); i++)
					{
						if (password[i] >= '0' && password[i] <= '9')
						{
							++digit;
						}
						else if (password[i] >= 'a' && password[i] <= 'z')
						{
							++lowercase;
						}
						else if (password[i] >= 'A' && password[i] <= 'Z')
						{
							++uppercase;
						}
						else if (password[i] == '@' || password[i] == '*' || password[i] == '_')
						{
							++specialchar;
						}

					}
					if (digit == 0 || lowercase == 0 || uppercase == 0)
					{
						throw InvalidPassword();
					}
					else
					{
						return true;
					}
				}
				else if (password.find(" ") != -1)
				{
					throw InvalidPassword();
				}
			}
			return true;
		}
		catch (const InvalidPassword& e)
		{
			cout << e.what() << endl;
			return false;
		}

	}
	//f-ja provjerava preko imena fajla da li je username zauzeto 
	//ako datoteka postoji vraca true, ina�e false
	bool isUserNameTaken(const string username)
	{
		ifstream file(username + ".txt");
		return file.good();
	}
	//f-ja koju ce dijeliti svi ucesnici za unos sifre
	//Unosom se svaki put pojavljuje *
	//npr. Enter password:******
	string Enter_password()
	{
		string password;
		char ch;
		ch = _getch();
		while (ch != 13) {  // Provjeri za ENTER key ASCII 13
			if (ch != 8) {   // Provjeri za backspace ASCII 8
				password.push_back(ch);
				cout << '*';
			}
			else if (!password.empty()) {
				password.pop_back();
				cout << "\b \b";  // Obrisi zadnju * (asterisk)
			}
			ch = _getch();
		}
		cout << endl;
		return password;
	}
	string check_Username(string username)
	{
		while (isUserNameTaken(username))
		{
			cout << "Username taken! " << endl;
			cin >> username;
		}
		return username;
	}
	string getFirstName() { return first_name; }
	string getLasttName() { return last_name; }
	string getPassword() { return password; }
	string getUserName() { return userName; }
	string getEmail() { return email; }
	
protected:
	//f-ja koja ignorise string do pojave ':'
	//Prilikom ispisa iz datoteke-> Username:
	//                              Password:
	// itd. ce ignorisati te ispisati samo username, password...
	void ignore_colon(string nameFile)
	{
		size_t colonPos = nameFile.find(':');
		if (colonPos != string::npos)
		{
			string result = nameFile.substr(colonPos + 1);
			cout << result << endl;
		}
	}
	//ima istu logiku kao i gornja funkcija, s tim �to sada vraca rezultat
	string return_ignore_colon(string nameFile)
	{
		size_t colonPos = nameFile.find(':');
		if (colonPos != string::npos)
		{
			string result = nameFile.substr(colonPos + 1);
			return result;
		}
		else
		{
			return NULL;
		}
	}
	//int userID;
	string userName="";
	string first_name="", last_name="";
	string email="";
	string password="";
	//opciono string userEmail;
};

