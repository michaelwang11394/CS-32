#undef _GLIBCXX_DEBUG
#undef _GLIBCXX_DEBUG_PEDANTIC
#undef _GLIBCXX_FULLY_DYNAMIC_STRING
#define _GLIBCXX_FULLY_DYNAMIC_STRING 1

#ifndef UTILITIES_INCLUDED
#define UTILITIES_INCLUDED

#include <string>
#include <iostream>
#include <list>
using namespace std;

const int MAXROWS = 20;             // max number of rows in the Levels
const int MAXCOLS = 100;             // max number of columns in the Levels
const int MAXObjects = 25;
const char ARROW_LEFT  = 'h';
const char ARROW_RIGHT = 'l';
const char ARROW_UP    = 'k';
const char ARROW_DOWN  = 'j';

char getCharacter();
void clearScreen();
int randInt(int limit);             // random int from 0 to limit-1
bool trueWithProbability(double p); // return true with probability p

#endif // UTILITIES_INCLUDED