//
//  Objects.h
//  Project 3
//
//  Created by Michael Wang on 5/23/15.
//  Copyright (c) 2015 Michael Wang. All rights reserved.
//

#ifndef __Project_3__Objects__
#define __Project_3__Objects__

#include <stdio.h>
#include "utilities.h"
#include <string>

class Objects
{
public:
    Objects();              //constructor/destructor
    Objects(int r, int c);  //designed for the idol
    Objects(int a, int r, int c, char sym, std::string name, char type); //scrolls.. also be careful with the string class
    Objects(int a, int b, int r, int c, char sym, std::string name, std::string action); //for weapons
    
    // Accessors
    int rows() { return i_row; }
    int cols() { return i_col; }
    int dmg() { return i_dmg; }
    int dex() { return i_dex; }
    int add() { return i_add; }
    char sym() { return i_symbol; }
    char type() { return i_type; }
    std::string name() { return i_name; }
    std::string action() { return i_action; }
    
private:
    int i_row, i_col; // position of items
    int i_dmg, i_dex, i_add; // what the items do
    char i_symbol;
    char i_type;
    std::string i_name;
    std::string i_action;
    
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
};
#endif /* defined(__Project_3__Objects__) */
