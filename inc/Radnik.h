#pragma once
#include <iostream>
#include "User.h"
#include <string>
#include <fstream>
using namespace std;

class Radnik : public User {
public:
	Radnik() noexcept : User() {}
};