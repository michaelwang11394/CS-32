#undef _GLIBCXX_DEBUG
#undef _GLIBCXX_DEBUG_PEDANTIC
#undef _GLIBCXX_FULLY_DYNAMIC_STRING
#define _GLIBCXX_FULLY_DYNAMIC_STRING 1

#include "Game.h"

int main()
{
    // Initialize the random number generator
    srand(static_cast<unsigned int>(time(0)));
    
    // Create a game
    // Use this instead to create a mini-game:
    Game g;
    //Game g(15, 18, 100);
    
    // Play the game
    g.play();
    
}