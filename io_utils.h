#ifndef _IO_UTILS_H_
#define _IO_UTILS_H_
// you must have a config file, both for windows and for compiling on Linux (MAMA)
// BUT, you need to change the content of the config!
#include "config.h"
#include "Enum.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <cmath>

void gotoxy(int x, int y);
void setTextColor(Color);
void hideCursor();
void clear_screen();

#ifndef WINDOWS	
int _getch(void);
int _kbhit(void);
void Sleep(unsigned long);
#else
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

using namespace std;

#endif

#endif