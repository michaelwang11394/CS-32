#undef _GLIBCXX_DEBUG
#undef _GLIBCXX_DEBUG_PEDANTIC
#undef _GLIBCXX_FULLY_DYNAMIC_STRING
#define _GLIBCXX_FULLY_DYNAMIC_STRING 1

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "utilities.h"
#include "Levels.h"
#include "Actor.h"

class Game
{
public:
    // Constructor/destructor
    Game();
    ~Game();
    
    // Mutators
    void play();
    
private:
    Levels* mLevels[5];
    int currentlvl;
    
    int decodeDirection(char dir) const;
};

#endif //GAME_INCLUDED