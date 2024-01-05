#pragma once
#include <iostream>
#include <exception>
using namespace std;
class FajlNijeOtvoren : public exception {
public:
	virtual const char* what() const noexcept override final
	{
		return "Error! Fajl nije moguce otvoriti.";
	}
};
class InvalidEmail : public exception {
public:
	virtual const char* what() const noexcept override final
	{
		return "Invalidan email.";
	}
};
class InvalidIme : public exception {
public:
	virtual const char* what() const noexcept override final
	{
		return "Ime nije validno.";
	}
};
class InvalidPrezime : public exception {
public:
	virtual const char* what() const noexcept override final
	{
		return "Prezime nije validno. ";
	}
};
class InvalidSifra : public exception {
public:
	virtual const char* what() const noexcept override final
	{
		return "Sifra nije validna. Molim unesite ponovo. ";
	}
};
class KorisnickoImeNijePronadjeno : public exception {
public:
	virtual const char* what() const noexcept override final
	{
		return "Korisnicko ime nije pronadjeno. ";
	}
};
