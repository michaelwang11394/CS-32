#undef _GLIBCXX_DEBUG
#undef _GLIBCXX_DEBUG_PEDANTIC
#undef _GLIBCXX_FULLY_DYNAMIC_STRING
#define _GLIBCXX_FULLY_DYNAMIC_STRING 1

#include "Items.h"

Objects::Objects()
{
}

Objects::Objects(int r, int c)
:i_row(r), i_col(c)
{
    
}

//for scrolls
Objects::Objects(int a, int r, int c, char sym, string name, char type)
:i_add(a), i_row(r), i_col(c), i_name(name), i_symbol(sym), i_type(type)
{
}

//for weapons
Objects::Objects(int a, int b, int r, int c, char sym, string name, string act)
:i_dmg(a), i_dex(b), i_row(r), i_col(c), i_add(0), i_name(name), i_symbol(sym),
i_action(act)
{
}
Mace::Mace()
{}

Mace::Mace(int r, int c)
:Objects(2, 0, r, c, ')', "mace", "swings")
{}

ShortSword::ShortSword()
:Objects(2, 0, 0, 0, ')', "short sword", "slashes")
{
}

ShortSword::ShortSword(int r, int c)
:Objects(2, 0, r, c, ')', "short sword", "slashes")
{
}

LongSword::LongSword()
{
}

LongSword::LongSword(int r, int c)
:Objects(4, 2, r, c, ')', "long sword", "slashes")
{
}

Axe::Axe()
{
}

Axe::Axe(int r, int c)
:Objects(5, 5, r, c, ')', "magic axe", "swings")
{
}

Fangs::Fangs()
{
}

Fangs::Fangs(int r, int c)
:Objects(2, 3, r, c, ')', "magic fangs of sleep", "strikes")
{
}



//scrolls
Tele::Tele()
{
}


//scrolls
Tele::Tele(int r, int c)
:Objects(0, r, c, '?', "scroll of teleportation", 't')
{
}


Armor::Armor()
{
}

Armor::Armor(int r, int c)
:Objects(1+randInt(3), r, c, '?', "scroll of enhanced armor", 'a')
{
}

Str::Str()
{
}

Str::Str(int r, int c)
:Objects(1+randInt(3), r, c, '?', "scroll of strength", 's')
{
}

Health::Health()
{
}

Health::Health(int r, int c)
:Objects(3+randInt(6), r, c, '?', "scroll of health", 'h')
{
}

Dex::Dex()
{
}

Dex::Dex(int r, int c)
:Objects(1, r, c, '?', "scroll of dexterity", 'd')
{
}