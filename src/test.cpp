#include "RadnikRegistracija.h"
#include "RadnikTehnicki.h"
#include "Radnik.h"
#include "Klijent.h"
#include "AdminTehnicki.h"
#include "AdminRegistracija.h"
using namespace std;
#include <string>

int main()
{
	Klijent klijent1;
	AdminRegistracija admin;
	klijent1.novaRegistracija();
	klijent1.Ulogovanje();
	cout << "Radnik ulogovanje" << endl;
	RadnikT radnik1;
	radnik1.Ulogovanje();

	cout << "Ulogovanje admina tehnicki" << endl;
	AdminTehnicki admin1;
	admin1.Prijava();

	cout << "Ulogovanje admina registracija" << endl;
	admin.Prijava();

	cout << "Pregeld radnika tehnickog" << endl;
	admin1.PregledNalogaRadnika();
	cout << "Pregled radnika registracije" << endl;
	admin.PregledNalogaRadnika();
	cout << "Za detaljniju info unesite radnika tehinckog" << endl;
	string username;
	cin >> username;
	admin1.ispisInfoRadnika(username);
	return 0;
}
