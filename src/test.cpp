#ifndef GETCH_H
#define GETCH_H

#include "RadnikRegistracija.h"
#include "RadnikTehnicki.h"
#include "Radnik.h"
#include "Klijent.h"
#include "AdminTehnicki.h"
using namespace std;
#include <string>

int main()
{
	RadnikT radnikT;
	string username;
	RadnikR radnikR;
	cout << "Provjera da li radnik za registraciju postoji?" << endl;
	cin >> username;
	radnikR.ispisFajla(username);
	AdminTehnicki adminT;
	cout << "Pregeld radnika tehnickog:" << endl;
	adminT.PregledNalogaRadnika();
	return 0;
}

#endif
