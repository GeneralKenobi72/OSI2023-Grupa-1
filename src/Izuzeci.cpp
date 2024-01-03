#include <iostream>
#include <exception>
#include "Izuzeci.h"
using namespace std;

inline const char* FajlNijeOtvoren::what() const noexcept
{
	return "Error! Fajl nije moguæe otvoriti.";
}

inline const char* InvalidEmail::what() const noexcept
{
	return "Invalidan email.";
}

inline const char* InvalidIme::what() const noexcept
{
	return "Ime nije validno.";
}

inline const char* InvalidPrezime::what() const noexcept
{
	return "Prezime nije validno. ";
}

inline const char* InvalidSifra::what() const noexcept
{
	return "Sifra nije validna. Molim unesite ponovo. ";
}

inline const char* KorisnickoImeNijePronadjeno::what() const noexcept
{
	return "Korisnicko ime nije pronadjeno. ";
}
