#include "RadnikRegistracija.h"
#include "RadnikTehnicki.h"
#include "Radnik.h"
#include "Klijent.h"
#include "AdminTehnicki.h"
using namespace std;
#include <string>

int main()
{
	Klijent klijent1;
	klijent1.Ulogovanje();
	cout << "Radnik ulogovanje" << endl;
	RadnikT radnik1;
	radnik1.Ulogovanje();

	cout << "Ulogovanje admina tehnicki" << endl;
	AdminTehnicki admin1;
	admin1.Prijava();

	cout << "Pregeld radnika tehnickog" << endl;
	admin1.PregledNalogaRadnika();

	cout << "Za detaljniju info unesite radnika tehinckoh" << endl;
	string username;
	cin >> username;
	admin1.ispisInfoRadnika(username);
	return 0;
}
