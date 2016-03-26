#undef _GLIBCXX_DEBUG
#undef _GLIBCXX_DEBUG_PEDANTIC
#undef _GLIBCXX_FULLY_DYNAMIC_STRING
#define _GLIBCXX_FULLY_DYNAMIC_STRING 1

#include "Actor.h"

Actor::Actor(Levels *ap, int r, int c, int hp, int str, int dex, int arm,
             Objects* equip, string name, char sym)
:mLevels(ap), m_dead(false), m_row(r), m_col(c), m_hp(hp), m_arm(arm),
m_str(str), m_dex(dex), max_health(20), m_dmg(0), a_arm(0), a_str(0), a_dex(0),
m_equipped(equip), w_dmg(0), w_dex(0), m_name(name), m_sym(sym), m_maxSleep(0)
{
}

//mutators
void Actor::changeSleep(int a)
{
    //we use this to change the sleep counter
    mSleep += a;
    //can't sleep more than the max sleep time
    if (mSleep > m_maxSleep)
        mSleep = m_maxSleep;
}
void Actor::set_equip(Objects* a)
{
    m_equipped = a;
}

void Actor::attack(int r, int c, string &act)
{
    bool hit; // if hit, then true
    if (level()->player()->row() == r && level()->player()->col() == c)
    {
        //player now has a pointer to it
        Actor* ah = level()->player();
        
        //dex and defense
        int aP = dex();
        int dP = ah->dex() + ah->arm();
        
        //how likely the hit will be take
        if (randInt(aP) >= randInt(dP))
        {
            hit = true;
            
            //how to calculate dmg of the person
            ah->changeHp(-1*(randInt(str()+dmg())));
            
            //magic fangs
            if (getEquipped()->name() == "magic fangs of sleep")
            {
                // there is a 1-5 chance of how likely the person will fall asleep
                if (randInt(5) == 0)
                {
                    // if not sleeping, then set the sleep max
                    if (!ah->is_sleep())
                    {
                        int a = 2+randInt(5);
                        ah->changeMaxSleep(a);
                        ah->changeSleep(a);
                    }
                    else
                        //we can also add to the amount that th person is sleeping w/o going over
                        ah->changeSleep(2+randInt(5));
                }
            }
        }
        
        
        if (hit)
        {
            if (ah->is_dead())
                act += (name() + " " + getEquipped()->action() + " " + getEquipped()->name()
                        + " at " + ah->name() + ", dealing the final blow." + '\n');
            else if (ah->is_sleep())
                act += (name() + " " + getEquipped()->action() + " " + getEquipped()->name()
                        + " at " + ah->name() + " and hits, putting " + ah->name() + " to sleep." + '\n');
            else
                act += (name() + " " + getEquipped()->action() + " " + getEquipped()->name()
                        + " at " + ah->name() + " and hits." + '\n');
        }
        else
            act += (name() + " " + getEquipped()->action() + " " + getEquipped()->name()
                    + " at " + ah->name() + " and misses." + '\n');
    }
    
}

//checking whether we are moving by attacking or not
bool Actor::move(char dir, string &str)
{
    
    if (dir == 'p')
    {
        //distance formula
        dir = movementdirection(level()->player()->row(), level()->player()->col());
    }
    switch (dir)
    {
        case ARROW_UP:
            //check if it's a valid move, then move
            if (row() > 0 && level()->okay_move(row()-1, col()))
            {
                change_spot(row()-1, col());
                return false;
            }
            attack(row()-1, col(), str);
            return true;
            break;
        case ARROW_DOWN:
            //check if it's a valid move, then move
            if (row() < level()->rows()-1  && level()->okay_move(row()+1, col()))
            {
                change_spot(row()+1, col());
                return false;
            }
            attack(row()+1, col(), str);
            return true;
            break;
        case ARROW_LEFT:
            //check if it's a valid move, then move
            if (col() > 0 && level()->okay_move(row(), col()-1))
            {
                change_spot(row(), col()-1);
                return false;
            }
            
            attack(row(), col()-1, str);
            return true;
            break;
        case ARROW_RIGHT:
            //check if it's a valid move, then move
            if (col() < level()->cols()-1  && level()->okay_move(row(), col()+1))
            {
                change_spot(row(), col()+1);
                return false;
            }
           
            attack(row(), col()+1, str);
            return true;
            break;
    }
    return false;
}
bool Actor::is_sleep() const
{
    if (mSleep > 0)
        return true;
    return false;
}

void Actor::newSpot(Levels *ap, int r, int c)
{
    mLevels = ap;
    m_row = r;
    m_col = c;
}

bool Actor::checkEquipped()
{
    if (m_equipped != NULL)
    {
        w_dmg = m_equipped->dmg();
        w_dex = m_equipped->dex();
        return true;
    }
    else
    {
        w_dex = 0;
        w_dmg = 0;
    }
    return false;
}

void Actor::heal()
{
    if (hp() < maxhp())
    {
        if (randInt(10) == 0)
            changeHp(1);
    }
}

int Actor::rDiff()
{
    //row difference
    int x = mLevels->player()->row() - m_row;
    if (x < 0)
        return -1*x;
    return x;
}

int Actor::cDiff()
{
    // column difference
    int x = mLevels->player()->col() - m_col;
    if (x < 0)
        return -1*x;
    return x;
}

bool Actor::checkPlayer(int r, int c) const
{

    if (r == mLevels->player()->row() &&
        c == mLevels->player()->col())
        return true;
    return false;
}


Player::Player(Levels* ap, int r, int c)
:Actor(ap, r, c, 20, 2, 2, 2, NULL, "Player", '@')
{
    hold_objects(new ShortSword());
    set_equip(m_invent[0]);
}

void Player::cheat()
{
    //lol only way to beat this game....
    cheatMax(50);
    changeHp(50);
    changeStr(9-str());
}

bool Player::showInvent(char type, string &str)
{
    clearScreen();
    
    //show the inventory
    cout << "Inventory: " << endl;
    int a;
    for (a = 0; a < m_invent.size(); a++)
    {
        char b = a + 'a';
        cout << " " << b << ". " << m_invent[a]->name() << endl;
    }
    
    //getting character
    char e = getCharacter();
    
    
    if (type == 'w')
        
        if (e < (a + 'a'))
         
            if (e >= 'a' && e <= 'z')
             
                if (m_invent[e-'a']->sym() == ')')
                {
                 
                    set_equip(m_invent[e-'a']);
                    str = "You equipped " + m_invent[e-'a']->name();
                }
    
  
    if (type == 'r')
      
        if (e < (a + 'a'))
            
            if (e >= 'a' && e <= 'z')
         
                if (m_invent[e-'a']->sym() == '?')
                {
                    //addding messages
                    str = "You used a " + m_invent[e-'a']->name() + ".";
                    switch (m_invent[e-'a']->type())
                    {
                        case 't':
                            str += " You have been teleported.";
                            break;
                        case 'a':
                            str += " Your armor has been enhanced.";
                            break;
                        case 's':
                            str += " Your strength increases.";
                            break;
                        case 'h':
                            str += " Your maximum health has increased.";
                            break;
                        case 'd':
                            str += " Your dexterity increases.";
                            break;
                        default:
                            break;
                    }
                    
                    //we are going to use a scroll and delete it
                    scroll(m_invent[e-'a']);
                    vector<class Objects*>::iterator p = (m_invent.begin()+e-'a');
                    p = m_invent.erase(p);
                }
    return true;
}

void Player::attack(int r, int c, string &act)
{
    bool hit; // if hit, true
    char a = level()->next_spot(r,c);
    switch (a) {
        case 'S':
        case 'G':
        case 'D':
        case 'B':
        {
           
            Actor* ah = level()->get_monster(r,c);
            
            //we are getting the dex and damage
            int aP = dex();
            int dP = ah->dex() + ah->arm();
            
            
            if (randInt(aP) >= randInt(dP))
            {
                hit = true;
                
                
                ah->changeHp(-1*(randInt(str()+dmg())));
                
                
                if (getEquipped()->name() == "magic fangs of sleep")
                {
                    if (randInt(5) == 0)
                    {
                        if (!ah->is_sleep())
                            ah->changeMaxSleep(2+randInt(5));
                        ah->changeSleep(randInt(2+randInt(5)));
                        
                    }
                }
                
            }
            
            //if there was a hit, add to the string
            if (hit)
            {
                if (ah->is_dead())
                    act += (name() + " " + getEquipped()->action() + " " + getEquipped()->name()
                            + " at " + ah->name() + " and hits, dealing the final blow." + '\n');
                else if (ah->is_sleep())
                    act += (name() + " " + getEquipped()->action() + " " + getEquipped()->name()
                            + " at " + ah->name() + " and hits, putting " + ah->name() + " to sleep." + '\n');
                else
                    act += (name() + " " + getEquipped()->action() + " " + getEquipped()->name()
                            + " at " + ah->name() + " and hits." + '\n');
            }
            else
                act += (name() + " " + getEquipped()->action() + " " + getEquipped()->name()
                        + " at " + ah->name() + " and misses." + '\n');
        }
            break;
        default:
            break;
    }
    
}

void Player::scroll(class Objects* a)
{
    
    switch (a->type())
    {
        case 't':
        {
        
            int x=0, y=0;
            level()->random_spot(x, y);
            change_spot(x,y);
            break;
        }
        case 'a':
            changeArm(a->add());
            break;
        case 's':
            changeStr(a->add());
            break;
        case 'h':
            changeMax(a->add());
            break;
        case 'd':
            changeDex(a->add());
            break;
        default:
            break;
    }
}




//equipping the monsters now
Bogeyman::Bogeyman(Levels* ap, int r, int c)
:Actor(ap, r, c, (5+randInt(6)), (2+randInt(2)), (2+randInt(2)), 2,
       new ShortSword(r,c), "the Bogeyman", 'B')
{
}
Bogeyman::~Bogeyman()
{
}
void Bogeyman::drop(int r, int c)
{
    if (randInt(10) == 0)
        if(level()->check_object(r, c))
            level()->add_item(r, c, 9);
}
bool Bogeyman::checkdistance()
{
    if (rDiff() + cDiff() <= 5)
        return true;
    return false;
}
char Bogeyman::movementdirection(int r, int c)
{
    int sc = col(), sr = row();
    
    //true if within distance
    if (!checkdistance())
        return ' ';
    
    //if it is, then check all the other directions
    else if (sr - r < 0 && !level()->check_wall(sr+1, sc) &&
             (level()->okay_move(sr+1, sc) || checkPlayer(sr+1, sc)))
        return ARROW_DOWN;
    else if (sr - r > 0 && !level()->check_wall(sr-1, sc) &&
             (level()->okay_move(sr-1, sc) || checkPlayer(sr-1, sc)))
        return ARROW_UP;
    else if (sc - c < 0 && !level()->check_wall(sr, sc+1) &&
             (level()->okay_move(sr, sc+1) || checkPlayer(sr, sc+1)))
        return ARROW_RIGHT;
    else if (sc - c > 0 && !level()->check_wall(sr, sc-1) &&
             (level()->okay_move(sr, sc-1) || checkPlayer(sr, sc-1)))
        return ARROW_LEFT;
    else
        return ' ';
}



Snakewomen::Snakewomen(Levels* ap, int r, int c)
:Actor(ap, r, c, (3+randInt(4)), 2, 3, 3,
       new Fangs(r,c), "the Snakewomen", 'S')
{
}
Snakewomen::~Snakewomen()
{
}

void Snakewomen::drop(int r, int c)
{
    if (randInt(3) == 0)
        if(level()->check_object(r, c))
            level()->add_item(r, c, 8);
}
bool Snakewomen::checkdistance()
{
    //distance of 3
    if (rDiff() + cDiff() <= 3)
        return true;
    return false;
}
char Snakewomen::movementdirection(int r, int c)
{
    int sc = col(), sr = row();
    
    //if it's not within distance, don't do anything
    if (!checkdistance())
        return ' ';
    
    //if it is, then check all the other directions
    else if (sr - r < 0 && !level()->check_wall(sr+1, sc) && 
             (level()->okay_move(sr+1, sc) || checkPlayer(sr+1, sc)))
        return ARROW_DOWN;
    else if (sr - r > 0 && !level()->check_wall(sr-1, sc) && 
             (level()->okay_move(sr-1, sc) ||checkPlayer(sr-1, sc)))
        return ARROW_UP;
    else if (sc - c < 0 && !level()->check_wall(sr, sc+1) && 
             (level()->okay_move(sr, sc+1) ||checkPlayer(sr, sc+1)))
        return ARROW_RIGHT;
    else if (sc - c > 0 && !level()->check_wall(sr, sc-1) && 
             (level()->okay_move(sr, sc-1) ||checkPlayer(sr, sc-1)))
        return ARROW_LEFT;
    else
        return ' ';
}


Dragon::Dragon(Levels* ap, int r, int c)
:Actor(ap, r, c, (20+randInt(6)), 4, 4, 4, 
       new LongSword(r,c), "the Dragon", 'D')
{
}
Dragon::~Dragon()
{
}
void Dragon::drop(int r, int c)
{
    if(level()->check_object(r, c))
        level()->add_item(r, c, 3+randInt(5));
}
bool Dragon::checkdistance()
{
   
    if (rDiff() + cDiff() <= 1)
        return true;
    return false;
}
char Dragon::movementdirection(int r, int c)
{
    int sc = col(), sr = row();
    
    
    if (!checkdistance())
        return ' ';
    
  
    else if (sr - r < 0 && !level()->check_wall(sr+1, sc) && 
             (level()->okay_move(sr+1, sc) || checkPlayer(sr+1, sc)))
        return ARROW_DOWN;
    else if (sr - r > 0 && !level()->check_wall(sr-1, sc) && 
             (level()->okay_move(sr-1, sc) ||checkPlayer(sr-1, sc)))
        return ARROW_UP;
    else if (sc - c < 0 && !level()->check_wall(sr, sc+1) && 
             (level()->okay_move(sr, sc+1) ||checkPlayer(sr, sc+1)))
        return ARROW_RIGHT;
    else if (sc - c > 0 && !level()->check_wall(sr, sc-1) && 
             (level()->okay_move(sr, sc-1) ||checkPlayer(sr, sc-1)))
        return ARROW_LEFT;
    else
        return ' ';
}

Goblin::Goblin(Levels* ap, int r, int c)
:Actor(ap, r, c, (15+randInt(6)), 3, 1, 1, 
       new ShortSword(r,c), "the Goblin", 'G')
{
}
Goblin::~Goblin()
{
}
void Goblin::drop(int r, int c)
{
    
    if (randInt(3) == 0)
        if(level()->check_object(r, c))
            level()->add_item(r, c, 8+randInt(2));
}
bool Goblin::checkdistance()
{
        if (rDiff() + cDiff() <= 15)
        return true;
    return false;
    
}
char Goblin::movementdirection(int r, int c)
{
    int sc = col(), sr = row();
    

    if (!checkdistance())
        return ' ';
    
    else if (sr - r < 0 && !level()->check_wall(sr+1, sc) && 
             (level()->okay_move(sr+1, sc) || checkPlayer(sr+1, sc)))
        return ARROW_DOWN;
    else if (sr - r > 0 && !level()->check_wall(sr-1, sc) && 
             (level()->okay_move(sr-1, sc) ||checkPlayer(sr-1, sc)))
        return ARROW_UP;
    else if (sc - c < 0 && !level()->check_wall(sr, sc+1) && 
             (level()->okay_move(sr, sc+1) ||checkPlayer(sr, sc+1)))
        return ARROW_RIGHT;
    else if (sc - c > 0 && !level()->check_wall(sr, sc-1) && 
             (level()->okay_move(sr, sc-1) ||checkPlayer(sr, sc-1)))
        return ARROW_LEFT;
    else
        return ' ';
}
