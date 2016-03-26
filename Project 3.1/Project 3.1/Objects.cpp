#undef _GLIBCXX_DEBUG
#undef _GLIBCXX_DEBUG_PEDANTIC
#undef _GLIBCXX_FULLY_DYNAMIC_STRING
#define _GLIBCXX_FULLY_DYNAMIC_STRING 1

#include "Objects.h"

Objects::Objects()
{
}

//this is for  general objects
Objects::  Objects(int r, int c)
:i__row(r), i__col(c)
{}

// this is for scrolls
Objects::Objects(int a, int r, int c, char sym, string name, char type)
:i__add(a), i__row(r), i__col(c), i__name(name), i__symbol(sym), i__type(type)
{}

//this is for weapons
Objects::Objects(int a, int b, int r, int c, char sym, string name, string act)
:i__dmg(a), i__dex(b), i__row(r), i__col(c), i__add(0), i__name(name), i__symbol(sym),
i__action(act)
{
}
Mace::Mace()
{}

Mace::Mace(int r, int c)
:Objects(2, 0, r, c, ')', "mace", "swings")
{}

ShortSword::ShortSword()
:Objects(2, 0, 0, 0, ')', "short sword", "slashes")
{}

ShortSword::ShortSword(int r, int c)
:Objects(2, 0, r, c, ')', "short sword", "slashes")
{}

LongSword::LongSword()
{}

LongSword::LongSword(int r, int c)
:Objects(4, 2, r, c, ')', "long sword", "slashes")
{}

Axe::Axe()
{}

Axe::Axe(int r, int c)
:Objects(5, 5, r, c, ')', "magic axe", "swings")
{}

Fangs::Fangs()
{}

Fangs::Fangs(int r, int c)
:Objects(2, 3, r, c, ')', "magic fangs of sleep", "strikes")
{}



//scrolls
Tele::Tele()
{}


//scrolls as general reference
Tele::Tele(int r, int c)
:Objects(0, r, c, '?', "scroll of teleportation", 't')
{}


Armor::Armor()
{}

Armor::Armor(int r, int c)
:Objects(1+randInt(3), r, c, '?', "scroll of enhanced armor", 'a')
{}

Str::Str()
{}

Str::Str(int r, int c)
:Objects(1+randInt(3), r, c, '?', "scroll of strength", 's')
{}

Health::Health()
{}

Health::Health(int r, int c)
:Objects(3+randInt(6), r, c, '?', "scroll of health", 'h')
{}

Dex::Dex()
{}

Dex::Dex(int r, int c)
:Objects(1, r, c, '?', "scroll of dexterity", 'd')
{}