#undef _GLIBCXX_DEBUG
#undef _GLIBCXX_DEBUG_PEDANTIC
#undef _GLIBCXX_FULLY_DYNAMIC_STRING
#define _GLIBCXX_FULLY_DYNAMIC_STRING 1

#ifndef Objects_INCLUDED
#define Objects_INCLUDED

#include "utilities.h"

class Objects
{
public:
    // Constructors
    Objects();
    Objects(int r, int c); // this is for idol which is special
    
    Objects(int a, int r, int c, char sym, string name, char type); // for scrolls
    Objects(int a, int b, int r, int c, char sym, string name, string action); // for weapons
    
    // Accessors
    int rows() { return i__row; }
    int cols() { return i__col; }
    int dmg() { return i__dmg; }
    int dex() { return i__dex; }
    int add() { return i__add; }
    char sym() { return i__symbol; }
    char type() { return i__type; }
    string name() { return i__name; }
    string action() { return i__action; }
    
    // Mutators
    
private:
    int i__row, i__col; // position of Objects
    int i__dmg, i__dex, i__add; // what the Objects do
    char i__symbol;
    char i__type;
    string i__name;
    string i__action;
};

class Mace: public Objects
{
public:
    Mace();
    Mace(int r, int c);
};

class ShortSword: public Objects
{
public:
    ShortSword();
    ShortSword(int r, int c);
};

class LongSword: public Objects
{
public:
    LongSword();
    LongSword(int r, int c);
};

class Axe: public Objects
{
public:
    Axe();
    Axe(int r, int c);
};

class Fangs: public Objects
{
public:
    Fangs();
    Fangs(int r, int c);
};

class Tele: public Objects
{
public:
    Tele();
    Tele(int r, int c);
};

class Armor: public Objects
{
public:
    Armor();
    Armor(int r, int c);
};

class Str: public Objects
{
public:
    Str();
    Str(int r, int c);
};

class Health: public Objects
{
public:
    Health();
    Health(int r, int c);
};

class Dex: public Objects
{
public:
    Dex();
    Dex(int r, int c);
};
#endif