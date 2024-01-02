//#include "test.h"
#include "../inc/test.h"
#include "../inc/User.h"
#include "../inc/Client.h"
#include <iostream>
using namespace std;

int main() {
	Client client1;
	string user;
	client1.NewRegistration();
	cout << "Enter username: ";
	cin >> user;
	client1.printFromFile(user);
	return 0;
}
