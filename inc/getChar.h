#pragma once
#ifdef _WIN32
#include<conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif 
#include <stdio.h>

char getChar();
