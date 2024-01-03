#pragma once
#include <iostream>
#include "Korisnik.h"
#include <string>
#include <fstream>
using namespace std;

class Radnik : public Korisnik {
protected:
	bool registrovan = true;
	string datumRodjenja;
	string pozicija;
public:
	Radnik() noexcept : Korisnik() {}
};