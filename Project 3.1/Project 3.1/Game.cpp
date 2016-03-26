#undef _GLIBCXX_DEBUG
#undef _GLIBCXX_DEBUG_PEDANTIC
#undef _GLIBCXX_FULLY_DYNAMIC_STRING
#define _GLIBCXX_FULLY_DYNAMIC_STRING 1

#include "Game.h"

Game::Game()
:currentlvl(0)
{
    // here we create the level
    mLevels[0] = new Levels();
    // adding player
    mLevels[0]->add_player();
}

Game::~Game()
{
    for (int a = 0; a < 5 && mLevels[a]!=NULL; a++)
        delete mLevels[a];
}

void Game::play()
{
    Player* p = mLevels[0]->player();
    if (p == NULL)
    {
        mLevels[0]->display();
        return;
    }
    string msg;
    bool message, compmessage;
    do
    {
        
        p->heal();
        
        mLevels[currentlvl]->check_dead_monsters();
        
        
        clearScreen();
        mLevels[currentlvl]->display();
        
        
        if (message)
        {
            cout << msg << endl;
            message = false;
        } else if (compmessage)
        {
            cout << msg << endl;
            compmessage = false;
        }
        msg = "";
        
        char move = getCharacter();
        if (!p->is_sleep())
        {
            switch (move) {
                    
                case 'c': //cheat
                    p->cheat();
                    break;
                case 'g': //pick up items
                    message = mLevels[currentlvl]->pick_up(msg);
                    break;
                case 'w': //view use weapons
                    message = p->showInvent('w', msg);
                    break;
                case 'r': //view scrolls
                    message = p->showInvent('r', msg);
                    break;
                case 'i': //view inventory
                    message = p->showInvent('i', msg);
                    break;
                case ARROW_LEFT:
                case ARROW_RIGHT:
                case ARROW_UP:
                case ARROW_DOWN:
                    message = p->move(move, msg);
                    break;
                case '>':
                    if(mLevels[currentlvl]->next_level())
                    {
                        currentlvl++;
                        mLevels[currentlvl] = new Levels(currentlvl, p);
                        mLevels[currentlvl]->add_player();
                    }
                    break;
                case 'q':
                    exit(1);
                default:
                    break;
            }
        }
        p->changeSleep(-1);
        
        
        compmessage = mLevels[currentlvl]->move_monsters(msg);
    } 
    while (!mLevels[currentlvl]->player()->is_dead());
    
 
    clearScreen();
    mLevels[currentlvl]->display();
    cout << msg;
    cout << "Press q to exit game. " << endl;
    char a;
    
    while (a != 'q') {
        a = getCharacter();
        if (a == 'q')
            exit(1);
    } 
}