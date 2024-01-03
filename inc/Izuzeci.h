#pragma once
#include <iostream>
#include <exception>
using namespace std;
class FajlNijeOtvoren : public exception {
public:
	virtual const char* what() const noexcept override final;
};
class InvalidEmail : public exception {
public:
	virtual const char* what() const noexcept override final;
};
class InvalidIme : public exception {
public:
	virtual const char* what() const noexcept override final;
};
class InvalidPrezime : public exception {
public:
	virtual const char* what() const noexcept override final;
};
class InvalidSifra : public exception {
public:
	virtual const char* what() const noexcept override final;
};
class KorisnickoImeNijePronadjeno : public exception {
public:
	virtual const char* what() const noexcept override final;
};