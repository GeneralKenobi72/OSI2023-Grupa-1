#pragma once
#include <iostream>
#include "User.h"
#include <string>
#include <fstream>
using namespace std;

class Radnik : public User {
protected:
	bool registered = true;
	string birthDate;
	string position;
public:
	Radnik() noexcept : User() {}
};