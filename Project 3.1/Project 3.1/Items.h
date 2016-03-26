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
    // Constructor/destructor
    Objects();
    Objects(int r, int c); // only for idol
    
    Objects(int a, int r, int c, char sym, string name, char type); // for scrolls
    Objects(int a, int b, int r, int c, char sym, string name, string action); // for weapons
    
    // Accessors
    int rows() { return i_row; }
    int cols() { return i_col; }
    int dmg() { return i_dmg; }
    int dex() { return i_dex; }
    int add() { return i_add; }
    char sym() { return i_symbol; }
    char type() { return i_type; }
    string name() { return i_name; }
    string action() { return i_action; }
    
    // Mutators
    
private:
    int i_row, i_col; // position of Objects
    int i_dmg, i_dex, i_add; // what the Objects do
    char i_symbol;
    char i_type;
    string i_name;
    string i_action;
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